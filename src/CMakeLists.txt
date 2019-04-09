cmake_minimum_required(VERSION 3.7)
project(assemble)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp FastaParser.cpp FastaParser.h DBG.h ErrorCorrector.h Assembler.h DBG.cpp DNA.cpp DNA.h Assembler.cpp ErrorCorrector.cpp AssemblerException.cpp AssemblerException.h DBGFactory.cpp DBGFactory.h)
add_executable(assemble ${SOURCE_FILES})