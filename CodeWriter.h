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
    explicit CodeWriter(string filename);

    ~CodeWriter();

    void setFileName(string filename);

    void writeArithmetic(const string& command);

    void writePushPop(VMCommand pushOrPop, const string& arg1, int arg2);

    void writePush(const string& arg1, int arg2);

    void writePop(const string& arg1, int arg2);

    void writeLabel(const string& arg1);

    void writeIf(const string& arg1);

    void writeGoto(const string& arg1);

    void writeInit();

    void writeCall(string functionName, int numArgs);

    void writeFunction(string functionName, int numArgs);

    void writeReturn();

    void sampleZero();

    void sampleOne();

    void sampleTwo();

    void sampleThree();

    void sampleFour();

    void sampleFive();

    void sampleSix(int arg2);

    void sampleSeven(int arg2);

    void sampleEight();

    void incSP();

    void decSP();

    void close();

    ofstream fout;

    int symbolCount;

    int labelCount;

    string functionName;
};


#endif //HACK_TRANSLATOR_CODEWRITER_H
