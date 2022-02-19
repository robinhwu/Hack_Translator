//
// Created by robin on 2022/2/5.
//

#ifndef HACK_TRANSLATOR_CODEWRITER_H
#define HACK_TRANSLATOR_CODEWRITER_H

#include <string>
#include <fstream>
#include "Parser.h"

using namespace std;

class CodeWriter {
public:
    CodeWriter(string filename);

    ~CodeWriter();

    void setFileName(string filename);

    void writeArithmetic(string command);

    void writePushPop(VMCommand pushOrPop, string arg1, int arg2);

    void writePush(string arg1, int arg2);

    void writePop(string arg1, int arg2);

    void incSP();

    void decSP();

    void close();

    ofstream fout;

    int symbolCount;
};


#endif //HACK_TRANSLATOR_CODEWRITER_H
