#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Assembler.h"
#include "ErrorCorrector.h"
#include "AssemblerException.h"
#include "DBGFactory.h"
#include "FastaParser.h"

//variables for error correction
const unsigned spectral_alignment_cutoff = 5;
const unsigned spectral_alignment_iterations = 3;
const unsigned contig_coverage_cutoff = 5; //10 works too but this is safer

using namespace std;

/**
 * Takes range containing DNA reads and transforms them into their reverse complements in-place.
 * @tparam InputIterator Container iterator type
 * @param first Start of range
 * @param last End of range
 */
template<class InputIterator>
void reverse_complement(InputIterator first, InputIterator last) {
    for (; first != last; ++first) {
        std::reverse(first->begin(), first->end());
        for (auto &&c : *first) {
            switch (c) {
                case 'A':
                    c = 'T';
                    break;
                case 'C':
                    c = 'G';
                    break;
                case 'G':
                    c = 'C';
                    break;
                case 'T':
                    c = 'A';
                    break;
                default:
                    throw AssemblerException("Found illegal character in read: " + c);
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 5) {
        cerr << "wrong number of arguments (5 required)" << endl;
        return 1;
    }
    //read parameters
    string inFileName = argv[1];
    string outFileName = argv[2];
    istringstream iss(argv[3]);
    std::size_t kmer_size;
    if (!(iss >> kmer_size)) {
        cerr << "failed to parse kmer size: " << kmer_size << endl;
        return 1;
    }

    try {
        //get reads from file
        FastaParser parser;
        vector<string> reads;
        parser.readFile(reads, inFileName);

        //add all kmers from file into de Bruijn Graph
        DBGFactory factory;
        DBG dbg;
        factory.add_read_kmers(dbg, reads, kmer_size);
        //also add all kmers from the reverse complements of reads
        reverse_complement(reads.begin(), reads.end());
        factory.add_read_kmers(dbg, reads, kmer_size);
        reads.clear();

        //apply spectral alignment to kmers for given amount of iterations or until all kmers are solid
        ErrorCorrector errorCorrector;
        for (unsigned i = 0; i < spectral_alignment_iterations; ++i) {
            if (!errorCorrector.spectral_alignment(dbg, spectral_alignment_cutoff)) {
                break;
            }
        }

        //find all linear stretches in DBG, remove those with an average coverage lower than a cutoff
        Assembler assembler;
        vector<string> sequences;
        assembler.assemble(dbg, contig_coverage_cutoff, sequences);

        //write contigs to fasta file
        parser.writeFile(outFileName, sequences);

    } catch (const AssemblerException &e) {
        cerr << "AssemblerException: " << e.what() << endl;
        return 1;
    } catch (const std::exception &e) {
        cerr << "Unexpected Exception: " << e.what() << endl;
        return 1;
    }
    return 0;
}
