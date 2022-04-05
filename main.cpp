#include <iostream>
#include <cassert>
#include "Test.h"

void runTests()
{
  // Test cases for the fibonacci function.
  IndexIsZeroBaseCaseTest zero;
  IndexIsOneBaseCaseTest one;
  IndexMAXIndexTest max_index;
  OutOfBoundsIndexTest invalid_index;
  
  bool result_of_fib_fn = zero.runTest() && 
    one.runTest() && 
    max_index.runTest() && 
    invalid_index.runTest();
  
  // File procesing test cases.
  ReadFibIndexFromFileTest read_index_test;
  DetectMalformedFileInputTest read_malformed;
  EmptyInputFileTest empty_file;

  bool result_of_file_ops = read_index_test.runTest() && 
    read_malformed.runTest() && 
    empty_file.runTest();

  // Test case of the feature api.
  FibFeatureTest fib_feature_test;

  bool result_of_program = result_of_fib_fn && 
    result_of_file_ops && 
    fib_feature_test.runTest();
  
  assert(result_of_program);
  
}

int main() {
  
  // Check this compiler's max ullong value
  // std::cout << std::numeric_limits<unsigned long long>::max() << std::endl; 
  
  runTests();
  
  return 0;
}