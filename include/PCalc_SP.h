#ifndef PCALC_SP_H
#define PCALC_SP_H

#include "PCalc.h"

class PCalc_SP : public PCalc {
    public:
        PCalc_SP(unsigned int array_size);
        void markNonPrimes() override;

    private:
        unsigned int asize;

};

#endif
