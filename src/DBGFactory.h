//
// Created by Andreas Denger on 12.06.17.
//

#ifndef ASSEMBLE_DBGFACTORY_H
#define ASSEMBLE_DBGFACTORY_H

#include <string>
#include <vector>

class DBG;

class DBGFactory {
public:
    /**
     * Generates all kmers of given size from reads and puts them into De Bruijn graph
     * @param dbg The DBG to which kmers are added
     * @param reads Set of reads from which kmers are generated
     * @param kmer_size Length of kmers
     */
    void add_read_kmers(DBG &dbg, const std::vector<std::string> &reads, const std::size_t kmer_size) const;
};


#endif //ASSEMBLE_DBGFACTORY_H
