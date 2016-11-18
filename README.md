# Matrix Playground

A experimental library for the manipulation of 2D matrices. The aim is to re-implement
key matlab functions in C to ease matlab to C conversions.

##Installation

To build, follow the below commands, all generated binaries are in the bin folder.

At the present time, a static library is created and placed in `./lib`. The headers
for the library are all contained within `./include` and their use detailed in
the Library overview section.

```shell
make all

#and to remove...
make clean
```
Binaries at the present time contain tests for the library.

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
    * LU decomposition (`lu(A)` in matlab)  and determinant calculation.
        + Note that LU decomposition only works properly if floating
          point elements are used.

- Element wise arithmetic: `2D_element_arithmetic.h`
    * Current element wise operators (A .(op) n)
        + pow
        + sqroot
        + multiply
        + divide
    * Fill matrix with single element
    * Sum matrix in either dimension (`sum(A,dim)` in matlab)
    * Elements can be updated per matrix or per row/column

Elements default to 32 bit int `int32_t`. To enable floating point elements
add `#define FLOAT` before the declaration of the `elem` type in
 `2D_matrix_ops.h`.

##Limitations

- Currently limited to treatment of 2D matrices only.

- Note that all matrix elements created need to be destroyed as the array storing
  the elements are on the heap via `malloc`
 
- Element wise operations  will apply floor arithmetic if integer elements are used
(notably `sqroot` and `divide` operations).

- The matrix arithmetic implementations are all naive ones at the present time.
Therefore note that matrix multiplication is `O(n^3)`. We'll be looking to
implement or incorporate BLAS routines in later releases.



