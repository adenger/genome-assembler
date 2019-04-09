//
// Created by Andreas Denger on 12.06.17.
//

#include "DBGFactory.h"
#include "AssemblerException.h"
#include "DNA.h"
#include "DBG.h"
#include <algorithm>
#include <numeric>


void DBGFactory::add_read_kmers(DBG &dbg, const std::vector<std::string> &reads, const std::size_t kmer_size) const {
    if (kmer_size < 2) {
        throw AssemblerException("DBGFactory: kmer_size is too small ");
    }
    //iterate over all reads longer than kmer_size, put all kmers into dbg
    for (auto &&read : reads) {
        if (read.size() < kmer_size)
            continue;
        for (auto &&pos = read.begin(); pos != read.end() - kmer_size + 1; ++pos) {
            dbg.increment(DNA(pos, pos + kmer_size));
        }
    }
}
