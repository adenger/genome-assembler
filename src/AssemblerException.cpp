//
// Created by Andreas Denger on 12.06.17.
//

#include "AssemblerException.h"

AssemblerException::AssemblerException(const std::string &message) : runtime_error(message) {}
