//
// Created by Andreas Denger on 11.06.2017.
//

#ifndef ASSEMBLE_ERRORCORRECTOR_H
#define ASSEMBLE_ERRORCORRECTOR_H

#include "DBG.h"

class ErrorCorrector {
public:
    /**
     * Spectral Alignment algorithm. If kmer has low coverage, it finds another kmer with higher coverage
     * and edit distance 1. The low coverage kmer is replaced with the higher coverage kmer.
     * @param dbg The De Bruijn Graph to be error corrected
     * @param cutoff Coverage cutoff for Kmers (below this is low coverage)
     * @return True iff any errors in dbg were corrected
     */
    bool spectral_alignment(DBG &dbg, unsigned cutoff) const;

private:
};


#endif //ASSEMBLE_ERRORCORRECTOR_H
