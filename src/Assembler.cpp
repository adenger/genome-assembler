//
// Created by Andreas Denger on 11.06.2017.
//

#include <memory>
#include <unordered_set>
#include <set>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <stack>
#include <queue>
#include <ctime>
#include "Assembler.h"


typedef DBG::const_iterator KmerIt;


namespace {
    /**
     * Returns all multi nodes
     * @param dbg De Bruijn Graph to be assembled
     * @param multi_nodes
     */
    void get_multi_nodes(const DBG &dbg,
                         std::unordered_set<KmerIt> &multi_nodes) {
        //iterate over all kmers
        for (auto &&kmer_pos = dbg.begin(); kmer_pos != dbg.end(); ++kmer_pos) {
            //if their in and out degrees match that of multi nodes: save them
            if (dbg.in_degree(kmer_pos) == 1) {
                if (dbg.out_degree(kmer_pos) > 1) {
                    multi_nodes.insert(kmer_pos);
                }
            } else {
                multi_nodes.insert(kmer_pos);
            }
        }
    }

    /**
     * Given a linear stretch, the kmers are assembled into a sequence by emptying the queue.
     * The resulting sequence is saved into vector
     * @param queue A linear stretch in the DBG
     * @param coverage_cutoff The minimum average coverage a contig is allowed to have
     * @param sequences The container to which the finished sequence is saved
     */
    void save_sequence(std::queue<KmerIt> &queue,
                       const unsigned coverage_cutoff,
                       std::vector<std::string> &sequences) {
        if (queue.size() > 1) {
            //queue contains valid linear stretch
            std::ostringstream sequence_stream;
            //save first kmer to sequence
            sequence_stream << queue.front()->first;
            unsigned coverage_count = queue.front()->second;
            unsigned total = queue.size();
            queue.pop();
            //append the last characters of following kmers
            while (!queue.empty()) {
                sequence_stream << queue.front()->first.back();
                coverage_count += queue.front()->second;
                queue.pop();
            }
            //if coverage is too low: discard
            if (coverage_count / total >= coverage_cutoff) {
                sequences.push_back(sequence_stream.str());
            }
        } else if (queue.size() == 1) {
            //make sure queue is empty
            queue.pop();
        }
    }
}

void Assembler::assemble(const DBG &dbg,
                         const unsigned coverage_cutoff,
                         std::vector<std::string> &sequences) const {
    //get multi nodes from which linear stretches can start
    std::unordered_set<KmerIt> multi_nodes;
    get_multi_nodes(dbg, multi_nodes);

    std::queue<KmerIt> queue;
    std::stack<KmerIt> stack;
    KmerIt current_kmer;
    std::vector<KmerIt> next_kmers;
    //iterate over all non-linear nodes and find all linear stretches that start from there or from a child node
    for (auto &&multi_node : multi_nodes) {
        //initialize stack with children of multi_node
        next_kmers = dbg.next_kmers(multi_node);
        if (next_kmers.size() == 1) {
            //if multi node has out_degree 1 it is part of the linear stretch
            queue.push(multi_node);
        }
        for (KmerIt next_kmer : next_kmers) {
            stack.push(next_kmer);
        }
        //iterative depth-first-search
        while (!stack.empty()) {
            //get next current child node
            current_kmer = stack.top();
            stack.pop();
            //process child nodes of current node
            next_kmers = dbg.next_kmers(current_kmer);
            if (multi_nodes.find(current_kmer) != multi_nodes.end()) {
                //current node is multi node
                //save linear stretch that was assembled and empty queue
                save_sequence(queue, coverage_cutoff, sequences);
            } else if (next_kmers.empty()) {
                //current node is linear node with out-degree 0 and therefore part of queue
                queue.push(current_kmer);
                //save linear stretch that was assembled and empty queue
                save_sequence(queue, coverage_cutoff, sequences);
            } else {
                //current node is linear node with children. Save current kmer and process child nodes
                queue.push(current_kmer);
                for (KmerIt next_kmer : next_kmers) {
                    stack.push(next_kmer);
                }
            }
        }
        //make sure queue is empty
        save_sequence(queue, coverage_cutoff, sequences);
    }
}

