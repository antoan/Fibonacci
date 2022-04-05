#ifndef INTERVIEW_TEST_TEST_H
#define INTERVIEW_TEST_TEST_H

#include "Fibonacci.h"

class Test
{
 public:
  virtual bool runTest() = 0;
};

class ExampleTest : public Test
{
 public:
  bool runTest() override {
    return false;
  }
};

class IndexIsZeroBaseCaseTest : public Test
{
 public:
  bool runTest() override {
    
    return (fib_maybe(0).first == 0);
  }
};

class IndexIsOneBaseCaseTest: public Test
{
 public:
  bool runTest() override {
    return fib_maybe(1).first == 1;
  }
};

class IndexMAXIndexTest: public Test
{
 public:
  
  bool runTest() override {                
    
    return fib_maybe(93).first == 12200160415121876738ULL;
  }

};


class OutOfBoundsIndexTest: public Test
{
 public:
  
  bool runTest() override {
  
    return fib_maybe(100).second == false;
  }

};

// FEATURE TESTS  - (Testing functionality of reading index from file then writing ouput to another file)

// TODO use  std::tmpfile and the POSIX function mkstemp for unique test file names.
// https://en.cppreference.com/w/cpp/io/c/tmpnam

// Helper to write index to file.
void writeToTestFile_helper(const std::string path, const std::string value) {
  
  std::ofstream testfile;
  testfile.open(path);
  testfile << value;
}

// Helper to read computed fibonacci number from output file.
unsigned int readFromOutputFile_helper(const std::string output_file_path){
  std::ifstream outfile(output_file_path);  
  unsigned int fibNumber;
  outfile >> fibNumber;
  return fibNumber;
}

class ReadFibIndexFromFileTest: public Test
{
 public:
  
  bool runTest() override {
    
    std::string  path = "/tmp/infile.txt";
    writeToTestFile_helper("/tmp/infile.txt", "3");
    return fib_readIndexFromFile(path) == 3;
  }
};

// Expects an exception to be thrown for an invalid index value.
class DetectMalformedFileInputTest: public Test
{
 public:
  
  bool runTest() override {
    
    std::string  path = "/tmp/infile.txt";
    writeToTestFile_helper("/tmp/infile.txt", "8ee");

    try {
      fib_readIndexFromFile(path); 
    
    }catch(MalformedFileException& e) {
      return true;
    }
    return false;
  }
};

class EmptyInputFileTest: public Test
{
 public:
  
  bool runTest() override {
    
    std::string  path = "/tmp/infile.txt";
    writeToTestFile_helper("/tmp/infile.txt", "");
    
    try {
      fib_readIndexFromFile(path); 
    
    }catch(MalformedFileException& e) {
      
      return true;
    }
    return false;
  }
};

class ProcessFibTest: public Test
{
 public:
  
  bool runTest() override {
        
    std::string  in_file_path = "/tmp/infile.txt";
    std::string output_file_path = "/tmp/outfile.txt";

    writeToTestFile_helper(in_file_path, "3");
    
    fib_feature(in_file_path, output_file_path);
    
    return readFromOutputFile_helper(output_file_path) == 2;
  }
};

#endif //INTERVIEW_TEST_TEST_H
