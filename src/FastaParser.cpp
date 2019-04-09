//
// Created by Andreas Denger on 10.06.2017.
//

#include <fstream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iostream>
#include "FastaParser.h"
#include "AssemblerException.h"


void FastaParser::readFile(std::vector<std::string> &reads, const std::string &fileName) const {
    std::ostringstream current_sequence;
    bool has_sequence = false;
    std::ifstream infile(fileName);
    if (!infile.good()) {
        throw AssemblerException("FastaParser: could not open file " + fileName);
    }
    //read file line by line
    std::string line;
    while (std::getline(infile, line)) {
        if (line.empty())
            continue;
        if (line[0] == '>') {
            //header found
            if (has_sequence) {
                //sequence from previous fasta entry exists, save it
                reads.push_back(current_sequence.str());
                current_sequence.str("");
                has_sequence = false;
            }
        } else {
            //DNA line, append it to current sequence
            current_sequence << line;
            has_sequence = true;
        }
    }
    //save last entry
    if (has_sequence)
        reads.push_back(current_sequence.str());
}

void FastaParser::writeFile(const std::string &out_file_name, const std::vector<std::string> &sequences) const {
    std::ofstream out_stream;
    out_stream.open(out_file_name);
    if (!out_stream.good()) {
        throw AssemblerException("FastaParser: could not write to file " + out_file_name);
    }
    //write file with headers >1, >2 ...
    size_t counter = 0;
    for (auto &&sequence : sequences) {
        out_stream << '>' << ++counter << std::endl << sequence << std::endl;
    }
    out_stream.close();
}
