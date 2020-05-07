# Pascal's Triangle
## Mini coding challenge - 07 May 2020

Pascal's Triangle is a triangular array containing the binomial coefficients.

Here's the first 9 rows:

                    1
                  1   1
                1   2   1
              1   3   3   1
            1   4   6   4   1
          1   5  10  10   5   1
        1   6  15  20  15   6   1
      1   7  21  35  35  21   7   1
    1   8  28  56  70  56  28   8   1

To construct a new row, compute each entry by taking the sum of the two values
immediately above it in the previous row (i.e. above left and above right). At
the left and right hand ends where there is only one number directly above, we
place a 1.

## Your task

1. Make sure you can build the project.
  ```bash
  mkdir pascals_triangle
  cd pascals_triangle

  git clone https://github.com/aharrison24/pascals_triangle.git src

  mkdir build
  cd build
  cmake ../src

  make
  ```

2. Run the tests
  ```bash
  ./pascals_triangle_tests
  ```
  You should see a series of test failures.
  
3. Update the source files `pascals_triangle.h` and `pascals_triangle.cpp`
   however you please in order to get the tests to pass.
   
## Questions you may have

#### Q: What C++ standard can I use
The project is set up to allow C++17. Please stick to that.

#### Q: Can I use any third-party libraries?
You may use anything in the C++ standard library. If you wish, you may also use
the [Range v3 library](https://ericniebler.github.io/range-v3/) and the
[fmt](https://fmt.dev/latest/) library, both of which are included in the
third-party directory. Though they are *certainly not necessary* to solve the
challenge. The CMake project is set up to allow you to use both libraries
straight away in your source files.

Please do not use any other third-party libraries.

#### Q: What's the deal with that weird `SOLUTION_NAMESPACE` macro?
Sorry about that. I need to be able to take all the submitted solutions and drop
them into my master project for testing. I need each solution to go into its own
namespace to avoid violations of the One Definition Rule. The macro lets me
replace the namespace programmatically. Please do not modify the line that
contains:
```c++
namespace SOLUTION_NAMESPACE {
```
  
#### Q: Can I modify the test file?
If it helps you to comment out some of the tests while you work on your solution
then sure. But your submitted result needs to pass with all of the tests
unmodified.
  
#### Q: Can I change the function signature of `generate_rows`?
Uh. If you like. You just have to get the tests to pass unmodified.
