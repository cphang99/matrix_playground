#!/usr/bin/env bash
set -e
export TYPES="INT FLOAT FIXED"
export BIN_FOLDER="bin"

for t in $TYPES
do
    if [ -f log ]
    then
        rm log
    fi
    make clean >> log 2>&1
    make all TYPE="$t" >> log 2>&1
    echo "Type = $t"
    if [ -d "$BIN_FOLDER" ]
    then
        for f in "$BIN_FOLDER"/*
        do
            printf "running $f\n"
            if [ -x "$f" ]
            then
                ./"$f" >> log 2>&1
                valgrind ./"$f" >> log 2>&1
            fi
        done
    fi
done
