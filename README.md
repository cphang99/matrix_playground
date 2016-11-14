# Matrix Playground

A experimental library for the manipulation of 2D matrices. The aim is to re-implement
key matlab functions in C to ease matlab to C conversions.

##Installation

To build, follow the below commands, all generated binaries are in the bin folder.

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

- Matrix wide arithmetic: `2D_matrix_arithmetic.h`
    * matrix addition, subtraction and multiplication.

- Element wise arithmetic: `2D_element_arithmetic.h`
    * Current element wise operators (A .(op) n)
        + pow
        + sqroot
        + multiply
        + divide
    * Fill matrix with single element
    * Sum matrix in either dimension

Elements default to 32 bit int `int32_t`. This can be changed by changing the 
`elem` typedef in `2D_matrix_ops.h`

##Limitations

- Currently limited to treatment of 2D matrices only.

- Note that all matrix elements created need to be destroyed as the array storing
  the elements are on the heap via `malloc`
 
- Some element wise operations assume integers are present and will apply floor
arithmetic (notably `sqroot` and `divide` operations).

- The matrix arithmetic implementations are all naive ones at the present time.
Therefore note that matrix multiplication is `O(n^3)`. We'll be looking to
implement or incorporate BLAS routines in later releases.



