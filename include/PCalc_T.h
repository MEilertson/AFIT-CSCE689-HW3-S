#ifndef PCALC_T_H
#define PCALC_T_H

#include <mutex>
#include <thread>

#include "PCalc.h"



class PCalc_T : public PCalc {
    public:
        PCalc_T(unsigned int array_size, unsigned int num_threads);
        void markNonPrimes() override;
        void workerFunction();
        unsigned int getNextIndex();

    private:

        unsigned int asize;
        unsigned int nthreads;
        unsigned int nindex;
        std::mutex index_mutex;

};

#endif

