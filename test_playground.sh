#!/usr/bin/env bash
export TYPES="INT FLOAT FIXED"
export BIN_FOLDER="bin"
export OUTCOME=0
export LOG_NAME="log.out"
if [ -f "$LOG_NAME" ]
then
    rm "$LOG_NAME"
fi
for t in $TYPES
do
    printf "Type = $t Build..."
    make clean >> "$LOG_NAME" 2>&1
    make all TYPE="$t" >> "$LOG_NAME" 2>&1
    if [ $? -eq 0 ]
    then
        printf "Successful\n"
    else
        printf "Failed, abort\n"
        exit 1
    fi
    if [ -d "$BIN_FOLDER" ]
    then
        for f in "$BIN_FOLDER"/*
        do
            printf "running $f"
            if [ -x "$f" ]
            then
                ./"$f" >> "$LOG_NAME" 2>&1
                if [ $? -eq 0 ]
                then
                    printf "...SUCCESS"
                else
                    printf "...FAIL"
                    OUTCOME=1
                fi
                printf " Memory check..."
                valgrind  --error-exitcode=2 --leak-check=full ./"$f" >> "$LOG_NAME" 2>&1
                if [ $? -eq 2 ]
                then
                    printf "...FAIL\n"
                    OUTCOME=1
                else
                    printf "...SUCCESS\n"
                fi
            fi
        done
    fi
done
echo "Full results written to "$LOG_NAME""
exit $OUTCOME
