
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

#include "PCalc_T.h"

/************************************************************************************************
 * PCalc_T (constructor) - Calls PCalc Constructor to build array and set them to true.
 * 
 ************************************************************************************************/

PCalc_T::PCalc_T(unsigned int array_size, unsigned int num_threads) : PCalc(array_size) {
    asize = array_size;
    nthreads = num_threads;
    nindex = 2;
}

/************************************************************************************************
 * markNonPrimes - in the threaded version, this function will now just spin up threads and join them.
 * The real work is done in WorkerFunction().
 *
 ************************************************************************************************/

void PCalc_T::markNonPrimes() {
    at(0) = false;
    at(1) = false;
    std::vector<std::thread> threads;
    //spin up threads
    for(int i = 0; i < nthreads; i++){
        threads.push_back(std::thread(&PCalc_T::workerFunction, this));
    }

    //join threads
    for(int i = 0; i < nthreads; i++){
        threads[i].join();
    }
}

/************************************************************************************************
 * workerFunction - This is a very slightly modified version of markNonPrimes from PCalc_SP.
 * The main difference is using a function called getNextIndex() to synchronize the threads incrementing
 * their prime_index.
 *
 ************************************************************************************************/

void PCalc_T::workerFunction() {
    unsigned int prime_index = getNextIndex();
    unsigned int loop_index = 0;

    while(prime_index < sqrt(asize)){
        if(at(prime_index)){
            unsigned int prime_index_squared = pow(prime_index,2);
            unsigned int composite;
            while((composite = prime_index_squared + prime_index*loop_index) < asize){
                at(composite) = false;
                loop_index++;
            }
        }
        loop_index = 0;
        prime_index = getNextIndex();
    }
}

/************************************************************************************************
 * getNextIndex - Synchronizes threads using a Mutex. The PCalc_T class's private nindex represents
 * the next index that needs to be used to find composites. A mutex locks the index down for access and 
 * incrementing before the thread releases it back to the pool.
 * 
 * After turning this in... I realized I could have moved line 55 (WorkerFunction) into this function.
 * I should check if the nindex is prime or not before assigning it to a thread... This is inefficient.
 * As it is written, a thread may select 10, or 16 and then loop through WorkerFunction doing nothing....
 *
 ************************************************************************************************/

unsigned int PCalc_T::getNextIndex() {
    unsigned int next_index;
    index_mutex.lock();
    next_index = nindex;
    nindex++;
    index_mutex.unlock();
    return next_index;
}