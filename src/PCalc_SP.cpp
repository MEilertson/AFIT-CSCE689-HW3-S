
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cmath>

#include "PCalc_SP.h"

/************************************************************************************************
 * PCalc_SP (constructor) - Calls PCalc Constructor to build array and set them to true.
 * 
 ************************************************************************************************/

PCalc_SP::PCalc_SP(unsigned int array_size) : PCalc(array_size) {
    asize = PCalc::array_size();

}

/************************************************************************************************
 * markNonPrimes - Runs the algorithm to mark non primes.
 *
 *
 ************************************************************************************************/

void PCalc_SP::markNonPrimes() {
    unsigned int prime_index = 2;
    unsigned int loop_index = 0;

    PCalc::at(0) = false;
    PCalc::at(1) = false;

    while (prime_index < sqrt(asize))
    {
        if(PCalc::at(prime_index)){
            unsigned int prime_index_squared = pow(prime_index,2);
            unsigned int composite;
            while ((composite = prime_index_squared + prime_index*loop_index) < PCalc_SP::asize)
            {
                PCalc::at(composite) = false;
                loop_index++;
            }
        }
        loop_index = 0;
        prime_index++;
    }
}