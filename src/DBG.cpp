//
// Created by Andreas Denger on 11.06.2017.
//

#include <algorithm>
#include <cassert>

#include "DBG.h"


DBG::const_iterator DBG::previous_kmer(DBG::const_iterator kmer_pos, const char prefix) const {
    if (kmer_pos != end()) {
        //given iterator position points to element, generate previous kmer
        DNA prev_kmer(kmer_pos->first.begin(), kmer_pos->first.end() - 1);
        prev_kmer.insert(prev_kmer.begin(), prefix);
        //find either returns position of previous kmer or end()
        kmer_pos = this->find(prev_kmer);
    }
    return kmer_pos;
}

DBG::const_iterator DBG::next_kmer(DBG::const_iterator kmer_pos, const char suffix) const {
    if (kmer_pos != end()) {
        //given iterator position points to element, generate next kmer
        DNA next_kmer(kmer_pos->first.begin() + 1, kmer_pos->first.end());
        next_kmer.insert(next_kmer.end(), suffix);
        //find either returns position of next kmer or end()
        kmer_pos = this->find(next_kmer);
    }
    return kmer_pos;
}

std::vector<DBG::const_iterator> DBG::previous_kmers(DBG::const_iterator kmer_pos) const {
    std::vector<DBG::const_iterator> prev;
    //get positions of all potential previous kmers
    for (auto &&prev_it: {previous_kmer(kmer_pos, 'A'),
                          previous_kmer(kmer_pos, 'C'),
                          previous_kmer(kmer_pos, 'G'),
                          previous_kmer(kmer_pos, 'T')}) {
        if (prev_it != end()) {
            //prev kmer exists, return it
            prev.push_back(prev_it);
        }
    }
    return prev;
}

std::vector<DBG::const_iterator> DBG::next_kmers(DBG::const_iterator kmer_pos) const {
    std::vector<DBG::const_iterator> next;
    //get positions of all potential next kmers
    for (auto &&next_it : {next_kmer(kmer_pos, 'A'),
                           next_kmer(kmer_pos, 'C'),
                           next_kmer(kmer_pos, 'G'),
                           next_kmer(kmer_pos, 'T')}) {
        if (next_it != end()) {
            //next kmer exists, return it
            next.push_back(next_it);
        }
    }
    return next;
}

const size_t DBG::in_degree(DBG::const_iterator kmer_pos) const {
    return previous_kmers(kmer_pos).size();
}

const size_t DBG::out_degree(DBG::const_iterator kmer_pos) const {
    return next_kmers(kmer_pos).size();
}

DBG::DBG() {}


void DBG::increase(const DNA &kmer, unsigned count) {
    assert(count);
    //count should be !=0 since otherwise map contains (kmer, 0)
    map[kmer] += count;
}

void DBG::increment(const DNA &kmer) {
    ++map[kmer];
}

/**
 * Methods passed through from map
 */

const size_t DBG::size() const {
    return map.size();
}

DBG::iterator DBG::begin() {
    return map.begin();
}

DBG::const_iterator DBG::begin() const {
    return map.begin();
}

DBG::iterator DBG::end() {
    return map.end();
}

DBG::const_iterator DBG::end() const {
    return map.end();
}

DBG::iterator DBG::erase(const_iterator pos) {
    return map.erase(pos);
}

DBG::iterator DBG::find(const DNA &dna) {
    return map.find(dna);
}

DBG::const_iterator DBG::find(const DNA &dna) const {
    return map.find(dna);
}

bool DBG::empty() const {
    return map.empty();
}





