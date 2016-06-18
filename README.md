# Algorithm Exercises
#### Currently implemented algorithms
- C++
  - Heapsort
    - Heapify-down implemented as non-recursive
  - Quicksort
    - Uses the Hoare partition scheme
    - Uses median-of-three pivot selection (considering implementing the ninther for larger lists)
  - Insertion sort
  - Introsort
    - Using C++ STL implementation
    - Quicksort is performed to a maximum depth given by 2×log2(n), then heapsort is done on any list longer than 16, finally an insertion sort pass
  - Bogosort
