//
// Created by Andreas Denger on 12.06.17.
//

#ifndef ASSEMBLE_ASSEMBLEREXCEPTION_H
#define ASSEMBLE_ASSEMBLEREXCEPTION_H


#include <string>
#include <stdexcept>

class AssemblerException : public std::runtime_error {
public:
    /**
     * This exception class is used to distinguish between known and unknown errors, see end of main()
     * @param message The reason for throwing the exception
     */
    explicit AssemblerException(const std::string &message);
};


#endif //ASSEMBLE_ASSEMBLEREXCEPTION_H
