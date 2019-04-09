//
// Created by Andreas Denger on 11.06.2017.
//

#ifndef ASSEMBLE_ASSEMBLER_H
#define ASSEMBLE_ASSEMBLER_H

#include "DBG.h"
#include <vector>

class DNA;

class Assembler {
public:
    /**
     * Find all linear stretches in dbg with average coverage >= cutoff
     * @param dbg A de Bruijn graph containing kmers
     * @param coverage_cutoff The lowest possible avg. coverage that any returned contig is allowed to have
     * @param sequences The assembled and valid contigs are written here
     */
    void assemble(const DBG &dbg, const unsigned coverage_cutoff, std::vector<std::string> &sequences) const;
};


#endif //ASSEMBLE_ASSEMBLER_H
