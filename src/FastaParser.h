//
// Created by Andreas Denger on 10.06.2017.
//

#ifndef ASSEMBLE_FASTAPARSER_H
#define ASSEMBLE_FASTAPARSER_H

#include <vector>
#include <string>

class FastaParser {
public:
    /**
     * Reads all sequences in fasta file ignoring headers
     * @param reads The vector in which the sequences are written
     * @param fileName Name of fasta file
     */
    void readFile(std::vector<std::string> &reads, const std::string &fileName) const;

    /**
     * Writes sequences to fasta file. Headers are generated automatically
     * @param out_file_name The name of the fasta file that is created
     * @param sequences Sequences that are written to the file
     */
    void writeFile(const std::string &out_file_name, const std::vector<std::string> &sequences) const;
};


#endif //ASSEMBLE_FASTAPARSER_H
