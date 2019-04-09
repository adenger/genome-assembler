//
// Created by Andreas Denger on 11.06.2017.
//

#ifndef ASSEMBLE_DBG_H
#define ASSEMBLE_DBG_H

#include "DNA.h"

#include <vector>
#include <unordered_map>
#include <functional>

/**
 * Implicit De Bruijn Graph.
 */
class DBG {

    typedef typename std::unordered_map<DNA, unsigned> KmerMap;
public:

    typedef typename KmerMap::iterator iterator;
    typedef typename KmerMap::const_iterator const_iterator;

    DBG();

    /**
     * Gets node before iterator position with given prefix
     * @param kmer_pos Position position in the graph
     * @param prefix The prefix of the previous kmer
     * @return Previous kmer with given prefix if kmer_pos and previous kmer exist, DBG::end() otherwise
     */
    const_iterator previous_kmer(const_iterator kmer_pos, const char prefix) const;

    /**
     * Gets node after iterator position with given suffix
     * @param kmer_pos Position in the graph
     * @param suffix The suffix of the next kmer
     * @return Next kmer with given suffix if kmer_pos and next kmer exist, DBG::end() otherwise
     */
    const_iterator next_kmer(const_iterator kmer_pos, const char suffix) const;

    /**
     * Retrieve previous DNA kmers of iterator position
     * @param kmer_pos Position in the graph
     * @return Positions of previous kmers that exist in the graph, only positions != end()
     */
    std::vector<const_iterator> previous_kmers(const_iterator kmer_pos) const;

    /**
     * Retrieve next DNA kmers of iterator position
     * @param kmer_pos Position in the graph
     * @return Positions of next kmers that exist in the graph, only positions != end()
     */
    std::vector<const_iterator> next_kmers(const_iterator kmer_pos) const;

    /**
     * @param kmer_pos Iterator position
     * @return Number of incoming edges into iterator position kmer_pos
     */
    const size_t in_degree(const_iterator kmer_pos) const;

    /**
     * @param kmer_pos Iterator position
     * @return Number of outgoing edges from iterator position kmer_pos
     */
    const size_t out_degree(const_iterator kmer_pos) const;

    /**
     * Increases the coverage of kmer by one or adds it to the DBG
     * @param kmer The kmer to be incremented
     */
    void increment(const DNA &kmer);

    /**
     * Increases the coverage of a kmer by count or adds the pair to the DBG
     * @param kmer The kmer to be increased
     * @param count Coverage increase. Should be >0
     */
    void increase(const DNA &kmer, unsigned count);

    /**
     * Methods passed through from std::unordered_map
     */

    const size_t size() const;

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    iterator erase(const_iterator pos);

    iterator find(const DNA &dna);

    const_iterator find(const DNA &dna) const;

    bool empty() const;

private:

    KmerMap map;
};
//Creates hash function object for iterator positions to be able to put them into hash-based collections
namespace std {
    template<>
    struct hash<DBG::const_iterator> {
        size_t operator()(const DBG::const_iterator &it) const {
            return std::hash<DNA>{}(it->first);
        }
    };
}


#endif //ASSEMBLE_DBG_H
