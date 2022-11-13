# Portable C++ Linear Algebra Library


Usage Example
```C++
  int a[16] = {1, 0, 2, -1, 3, 0, 0, 5, 2, 1, 4, -3, 1, 0, 5, 0};
  int b[16] = {1, 0, 4, -2, 5, 1, 2, 5, 23, 12, 4, -3, 11, 4, 56, 0};
  zMatrix<int> m1(4,4, a);
  zMatrix<int> m2(4,4, b);
  zMatrix<int> result = m1 * m2
 ```
