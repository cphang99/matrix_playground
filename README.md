# Matrix Playground

A experimental library for the manipulation of 2D matrices. The aim is to re-implement
key matlab functions in C to ease matlab to C conversions.

Use at your own risk! Assume that functionality is either missing or incomplete
at this time.

Fixed point arithmetic is provided by using the libfixmath library
(https://en.wikipedia.org/wiki/Libfixmath).

##Installation

To build, follow the below commands, all generated binaries are in the bin folder.

At the present time, a static library is created and placed in `./lib`. The headers
for the library are all contained within `./include` and their use detailed in
the Library overview section.

Elements default to 32 bit int `int32_t`. Elements are set by passing the `TYPE`
variable to make, which can either be:
- Integer `int32_t` (The default, nothing needs to be set)
- floating point `float` (Set `TYPE="FLOAT"`)
- Fixed-point (Q16.16) (Set `TYPE="FIXED"`)

```shell
#In your working directory:

git clone https://github.com/cphang99/matrix_playground.git --recursive
cd matrix_playground

#if you want to use a specfic element type, set the TYPE variable
make all TYPE="FIXED"

#and to remove...
make clean
```

Binaries at the present time contain tests for the library. To run these tests
for all `TYPE=`, there is a script `test_playground.sh` that runs all tests for
all types and also runs (valgrind) memory checks for each test.

The results of tests are written to a file `log.out`

##Library overview
- Matrix Transformations: `2D_matrix_ops.h`
    * for matrix creation and destruction.
    * get and set individual matrix elements.
    * tranpose (`A'`) and concatenate (`[A B]`)  matrices
    * Slice matrices (`:` operator in matlab)
    * Create vectors (`j:i:k` operator in matlab)
    * Diagonal matrices from vectors (`diag(v)` operator in matlab) 
    * Get minimum and maximum elements in a matrix
      (`min(A)` and `max(A)` in matlab)

- Matrix wide arithmetic: `2D_matrix_arithmetic.h`
    * matrix addition, subtraction and multiplication.
    * Elementary row operations:
        - Row (and column) interchange
        - Row addition
    * LU decomposition (`lu(A)` in matlab).
        + Note that LU decomposition only works properly if floating
          point elements are used.
    * Determinant calculations (`det(A)` in matlab)
    * Solving linear equations (`x=A\b` in matlab)
    * Determining inverses (`inv(A)` in matlab)

- Element wise arithmetic: `2D_element_arithmetic.h`
    * Current element wise operators (A .(op) n)
        + pow
        + sqroot
        + multiply
        + divide
    * Fill matrix with single element
    * Sum matrix in either dimension (`sum(A,dim)` in matlab)
    * Elements can be updated per matrix or per row/column


##Limitations

- Currently limited to treatment of 2D matrices only.

- Note that all matrix elements created need to be destroyed as the array storing
  the elements are on the heap via `malloc`
 
- Element wise operations  will apply floor arithmetic if integer elements are used
(notably `sqroot` and `divide` operations).

- nth root operations are not supported for fixed point elements, and will default
  to a square root operation with a warning.

- The matrix arithmetic implementations are all naive ones at the present time.
Therefore note that matrix multiplication is `O(n^3)`. We'll be looking to
implement or incorporate BLAS routines in later releases.

- QR and cholesky decompositions are not implemented here at this time.
