#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <limits>
#include <fstream>
#include <iostream>
#include <exception>

struct MalformedFileException : public std::exception
{
	const char * what () const throw ()
    {
    	return "Input file is malformed.";
    }
};

const unsigned int max_index = 93;

// TODO: Rewrite as a Fibonacci class or struct.

// NOTE: As the spec did not touch on the input/output range limits of the fibonnaci function, 
// I decided to constrain the input index to 93, which maps the output to the max value of ULLONG type, 
// An index input of 94 exceeds ULLONG_MAX 18446744073709551615 (g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0)

// Implementation is iterative rather than recursive simply because I chose to frame this in a 
// robotics/safety critical context. For performance, and to avoid heavy push-pop of the stack memory.
// https://betterembsw.blogspot.com/2014/07/dont-overflow-stack.html
// While also being aware that there are optimizations for the recursive approach, 
// like memoization, tail recursion and such.

// Algorithmic Complexity: 
// Time: linear - O(n)
// Memory: constant.
std::pair<unsigned long long, bool>  fib_maybe(unsigned int n)
// pre-conditions : 0 >= n <= max_index
// post-condition : returns a std:pair wrapping a result and success/failure flag.
//                  pair.first: a positive value for the corresponding fibonnaci number
//                  pair.second: indicates succes (true) or an error condition, such an index out of bounds.
// 
{   
    
    // Probably shoudn't do this here (although it would be more descriptive to the caller and prevent silent failure)
    // "Do not use throw to indicate a coding error in usage of a function..."
    // https://isocpp.org/wiki/faq/exceptions#why-exceptions
    /* if(n > max_index)
      throw std::invalid_argument("Index input exceeds the maximum range."); */
    
    if(n > max_index)
      return {0,false};

    unsigned long long f1 = 0, f2 = 1;
    
    for(; n > 0; --n)
    {
        f2 += f1;
        f1 = f2 - f1;
    }
    return {f1,true};
}

unsigned int fib_readIndexFromFile(std::string src) {
  
    // is RIAA, destructor will kick in when stack is unwound due to our exceptions
    std::ifstream infile(src);  
    
    if (!infile.good())
    {
        throw std::runtime_error("Opening input file failed - "
            "one of the error flags is true\n");
    }
    
    unsigned int fibIndex;
    
    // parse a single numeric character, after which we should reach EOF in the input stream.
    // assume: any additional characters indicate a malformed input file.
    infile >> fibIndex;
    
    // https://en.cppreference.com/w/cpp/io/ios_base/iostate
    if (infile.bad()) 
    {
        throw std::runtime_error("I/O error while reading - badbit is true\n");  
    }
    else if (infile.fail()) {
        
        // std::cerr << "Non-integer data encountered - failbit is true\n";
        throw MalformedFileException();

    } else if (!infile.eof()) {
        
        throw MalformedFileException();
    } 
    
    return fibIndex;
}

// TODO: Test this.
void fib_writeToFile(std::string dest, unsigned long long fibNumber) {
  
    std::ofstream outfile;
    outfile.open(dest);
    outfile << fibNumber;
}

// Reads the fibonacci function input index from a source file and writes the computed number to a destination file
// TODO: Rewrite src/dest as mockable readers/writer classes for testing.
void fib_feature(std::string src, std::string dest) {
    
    auto result = fib_maybe(fib_readIndexFromFile(src));

    // trying to emulate std::optional (C++17)
    // TODO: would be better to rewrite fib to throw an exception on invalid index input
    bool has_value = result.second; 
    if(!has_value)
        throw std::runtime_error("Failed to process the request.\n"); 
            
    fib_writeToFile(dest, result.first);
}

#endif // FIBONACCI_H