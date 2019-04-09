//
// Created by Andreas Denger on 11.06.2017.
//

#include <iostream>
#include "ErrorCorrector.h"
#include "AssemblerException.h"


namespace {
    /**
     * Switches DNA base chars in a cycle
     * @param base DNA base char
     * @return Next DNA base in the cycle
     */
    char get_next_nucleotide(char base) {
        switch (base) {
            case 'A':
                return 'C';
            case 'C':
                return 'G';
            case 'G':
                return 'T';
            case 'T':
                return 'A';
            default:
                throw AssemblerException("ErrorCorrector: Illegal Char " + base);
        }
    }

    /**
     * Returns iterator position of kmer with edit distance 1
     * to the kmer at position dbg_iter that has a higher coverage
     * If it does not exist it returns dbg_iter
     * @param dbg_iter The position of a potential error kmer
     * @param dbg The De Bruijn Graph
     * @return The best candidate for error correction
     */
    DBG::const_iterator get_best_correction(DBG::const_iterator dbg_iter, DBG &dbg) {
        //local copy to avoid invalidating hash
        DNA dna = dbg_iter->first;
        auto best_candidate = dbg_iter;
        int i = 0;
        DBG::const_iterator pos;
        //iterate over every character in dna
        for (auto &&base: dna) {
            //try every base that is not the original base
            for (i = 0; i < 3; ++i) {
                base = get_next_nucleotide(base);
                //if the changed dna exists and has better coverage: save it
                if ((pos = dbg.find(dna)) != dbg.end() && best_candidate->second < pos->second) {
                    best_candidate = pos;
                }
            }
            //switch base bach to original
            base = get_next_nucleotide(base);
        }
        return best_candidate;
    }
}

bool ErrorCorrector::spectral_alignment(DBG &dbg, unsigned cutoff) const {
    //map of better kmers and by how much they are increased because of the corrections
    std::unordered_map<DNA, unsigned> increases;
    DBG::const_iterator correct_kmer;
    //iterate over all kmers in DBG
    for (auto &&iter = dbg.begin(); iter != dbg.end();) {
        if (iter->second < cutoff && (correct_kmer = get_best_correction(iter, dbg)) != iter) {
            //kmer coverage was less than cutoff and a kmer with edit distance 1 and higher cov. was found
            //increase coverage of better kmer by that of error kmer
            increases[correct_kmer->first] += iter->second;
            //erase error kmer
            iter = dbg.erase(iter);
        } else {
            //kmer not classified as error or no better candidate was found
            ++iter;
        }
    }
    //apply the increases afterward to avoid errors being corrected differently because of other corrections
    for (auto &&entry: increases) {
        dbg.increase(entry.first, entry.second);
    }
    return !increases.empty();
}
