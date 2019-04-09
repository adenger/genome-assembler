//
// Created by Andreas Denger on 11.06.2017.
//

#include "DNA.h"
#include <algorithm>
#include <iostream>


DNA::DNA() {}

std::size_t DNA::getHash() const {
    //the std::string hash was much faster than two bit DNA encoding
    return std::hash<std::string>{}(sequence);
}

/**
 * Methods passed through from std::string
 */

bool DNA::operator==(const DNA &rhs) const {
    return sequence == rhs.sequence;
}

bool DNA::operator!=(const DNA &rhs) const {
    return !(rhs == *this);
}

DNA::iterator DNA::begin() {
    return sequence.begin();
}

DNA::const_iterator DNA::begin() const {
    return sequence.begin();
}

DNA::iterator DNA::end() {
    return sequence.end();
}

DNA::const_iterator DNA::end() const {
    return sequence.end();
}

char &DNA::back() {
    return sequence.back();
}

const char &DNA::back() const {
    return sequence.back();
}

std::ostream &operator<<(std::ostream &os, const DNA &dna) {
    os << dna.sequence;
    return os;
}

void DNA::insert(DNA::const_iterator p, char c) {
    sequence.insert(p, c);
}

size_t DNA::length() const {
    return sequence.length();
}
