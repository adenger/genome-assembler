//
// Created by Andreas Denger on 11.06.2017.
//

#ifndef ASSEMBLE_DNA_H
#define ASSEMBLE_DNA_H

#include <string>
#include <ostream>

/**
 * std::string wrapper with customizable hash function
 */
class DNA {
public:
    typedef typename std::string::iterator iterator;
    typedef typename std::string::const_iterator const_iterator;

    /**
     * Range constructor
     * @tparam InputIterator Container iterator
     * @param first Beginning of range
     * @param last End of range
     */
    template<class InputIterator>
    DNA(InputIterator first, InputIterator last) : sequence(first, last) {}

    //Default constructor
    DNA();

    /**
     * Get hash value
     * @return The hash value
     */
    std::size_t getHash() const;

    /**
     * Functions passed through from std::string
     */
    bool operator==(const DNA &rhs) const;

    bool operator!=(const DNA &rhs) const;

    void insert(const_iterator p, char c);

    iterator begin();

    const_iterator begin() const;

    iterator end();

    const_iterator end() const;

    char &back();

    const char &back() const;

    friend std::ostream &operator<<(std::ostream &os, const DNA &dna);

    size_t length() const;

private:
    std::string sequence;

};

//Put hash function object into std namespace
namespace std {
    template<>
    struct hash<DNA> {
        size_t operator()(const DNA &dna) const {
            return dna.getHash();
        }
    };
}

#endif //ASSEMBLE_DNA_H
