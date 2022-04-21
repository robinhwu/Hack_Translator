//
// Created by robin on 2022/2/5.
//

#include "CodeWriter.h"
#include <string>
#include <iostream>

using namespace std;

CodeWriter::CodeWriter(string filename) {
    setFileName(std::move(filename));
}

CodeWriter::~CodeWriter() {
    close();
}

void CodeWriter::writeInit() {

}

void CodeWriter::setFileName(string filename) {
    symbolCount = 0;
    labelCount = 0;
    filename += ".asm";
    fout.open(filename);
    if (!fout.is_open())
        cerr << "Error: Could not open " << filename << ".\n";
}

void CodeWriter::close() {
    if (fout.is_open())
        fout.close();
}

void CodeWriter::sampleZero() {
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "D=M" << endl;
}

void CodeWriter::sampleOne() {
    decSP();
    sampleZero();
    decSP();
    fout << "A=M" << endl;
    fout << "A=M" << endl;
}

void CodeWriter::sampleTwo() {
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
}

void CodeWriter::sampleThree() {
    decSP();
    sampleZero();
    decSP();
    fout << "A=M" << endl;
    fout << "D=M-D" << endl;
    fout << "@TRUE" << to_string(symbolCount) << endl;
}

void CodeWriter::sampleFour() {
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=0" << endl;
    fout << "@CONTINUE" << to_string(symbolCount) << endl;
    fout << "0;JMP" << endl;
    fout << "(TRUE"<< to_string(symbolCount) << ")" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "M=-1" << endl;
    fout << "(CONTINUE"<< to_string(symbolCount) << ")" << endl;
    incSP();
    symbolCount++;
}

void CodeWriter::writeArithmetic(const string& command) {
    if (command == "add")
    {
        sampleOne();
        fout << "D=D+A" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "sub")
    {
        sampleOne();
        fout << "D=A-D" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "neg")
    {
        decSP();
        fout << "A=M" << endl;
        fout << "D=M" << endl;
        fout << "D=-D" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "not")
    {
        decSP();
        fout << "A=M" << endl;
        fout << "D=M" << endl;
        fout << "D=!D" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "and")
    {
        sampleOne();
        fout << "D=D&A" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "or")
    {
        sampleOne();
        fout << "D=D|A" << endl;
        sampleTwo();
        incSP();
    }
    else if (command == "eq")
    {
        sampleThree();
        fout << "D;JEQ" << endl;
        sampleFour();
    }
    else if (command == "gt")
    {
        sampleThree();
        fout << "D;JGT" << endl;
        sampleFour();
    }
    else if (command == "lt")
    {
        sampleThree();
        fout << "D;JLT" << endl;
        sampleFour();
    }
}

void CodeWriter::writePushPop(VMCommand pushOrPop, const string& arg1, int arg2) {
    if(pushOrPop == C_PUSH) {
        writePush(arg1,arg2);
    } else {
        writePop(arg1, arg2);
    }
}

void CodeWriter::sampleFive() {
    fout << "A=M" << endl;
    fout << "A=D+A" << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
}

void CodeWriter::sampleSix(int arg2) {
    fout << "@" << arg2 << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
}

void CodeWriter::writePush(const string& arg1, int arg2) {
    if (arg1 == "constant")
    {
        fout << "@" << arg2 << endl;
        fout << "D=A" << endl;
        fout << "@SP" << endl;
        fout << "A=M" << endl;
        fout << "M=D" << endl;
        incSP();
    } else if (arg1 == "local") {
        fout << "@" << arg2 << endl;
        fout << "D=A" << endl;
        fout << "@LCL" << endl;
        sampleFive();
    } else if (arg1 == "argument") {
        fout << "@" << arg2 << endl;
        fout << "D=A" << endl;
        fout << "@ARG" << endl;
        sampleFive();
    } else if (arg1 == "this") {
        fout << "@" << arg2 << endl;
        fout << "D=A" << endl;
        fout << "@3" << endl;
        sampleFive();
    } else if (arg1 == "that") {
        fout << "@" << arg2 << endl;
        fout << "D=A" << endl;
        fout << "@4" << endl;
        sampleFive();
    } else if (arg1 == "pointer") {
        arg2 += 3;
        sampleSix(arg2);
    } else if (arg1 == "temp") {
        arg2 += 5;
        sampleSix(arg2);
    } else {
        arg2 += 16;
        sampleSix(arg2);
    }
}

void CodeWriter::sampleSeven(int arg2) {
    decSP();
    fout << "@" << arg2 << endl;
    fout << "D=A" << endl;
}

void CodeWriter::sampleEight() {
    fout << "A=M" << endl;
    fout << "D=D+A" << endl;
    fout << "@13" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "D=M" << endl;
    fout << "@13" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
}

void CodeWriter::writePop(const string& arg1, int arg2) {
    if (arg1 == "local") {
        sampleSeven(arg2);
        fout << "@LCL" << endl;
        sampleEight();
    } else if (arg1 == "argument") {
        sampleSeven(arg2);
        fout << "@ARG" << endl;
        sampleEight();
    } else if (arg1 == "this") {
        sampleSeven(arg2);
        fout << "@3" << endl;
        sampleEight();
    } else if (arg1 == "that") {
        sampleSeven(arg2);
        fout << "@4" << endl;
        sampleEight();
    } else if (arg1 == "pointer") {
        decSP();
        sampleZero();
        arg2 += 3;
        fout << "@" << arg2 << endl;
        fout << "M=D" << endl;
    } else if (arg1 == "temp") {
        decSP();
        sampleZero();
        arg2 += 5;
        fout << "@" << arg2 << endl;
        fout << "M=D" << endl;
    } else {
        decSP();
        sampleZero();
        arg2 += 16;
        fout << "@" << arg2 << endl;
        fout << "M=D" << endl;
    }
}

void CodeWriter::writeLabel(const string& arg1) {
    fout << "(" << arg1 << ")"<< endl;
}

void CodeWriter::writeFunction(string functionName, int numArgs) {
    fout << "(" << functionName << ")" << endl;
    for (int i = 0; i < numArgs; i++) {
        fout << "@0" << endl;
        fout << "D=A" << endl;
        sampleTwo();
        incSP();
    }
}

void CodeWriter::writeCall(string functionName, int numArgs) {
    // PUSH RETURN ADDRESS
    fout << "@LABEL" << labelCount << endl;
    fout << "D=A" << endl;
    sampleTwo();
    incSP();
    // PUSH LCL
    fout << "@LCL" << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
    // PUSH ARG
    fout << "@ARG" << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
    // PUSH THIS
    fout << "@THIS" << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
    // PUSH THAT
    fout << "@THAT" << endl;
    fout << "D=M" << endl;
    sampleTwo();
    incSP();
    // ARG = SP-n-5
    numArgs += 5;
    fout << "@" << numArgs << endl;
    fout << "D=A" << endl;
    fout << "@SP" << endl;
    fout << "D=M-D" << endl;
    fout << "@ARG" << endl;
    fout << "M=D" << endl;
    // LCL = SP
    fout << "@SP" << endl;
    fout << "D=M" << endl;
    fout << "@LCL" << endl;
    fout << "M=D" << endl;
    // GOTO F
    fout << "@" << functionName << endl;
    fout << "0;JMP" << endl;
    // (RETURN ADDRESS)
    fout << "(LABEL" << labelCount << ")" << endl;
    labelCount++;
}

void CodeWriter::writeReturn() {
    //FRAME = LCL
    fout << "@LCL" << endl;
    fout << "D=M" << endl;
    fout << "@13" << endl;
    fout << "M=D" << endl;
    //RET = *(FRAME-5)
    fout << "@5" << endl;
    fout << "A=D-A" << endl;
    fout << "D=M" << endl;
    fout << "@14" << endl;
    fout << "M=D" << endl;
    //*ARG=POP()
    decSP();
    fout << "@ARG" << endl;
    fout << "D=M" << endl;
    fout << "@15" << endl;
    fout << "M=D" << endl;
    fout << "@SP" << endl;
    fout << "A=M" << endl;
    fout << "D=M" << endl;
    fout << "@15" << endl;
    fout << "A=M" << endl;
    fout << "M=D" << endl;
    //SP=ARG+1
    fout << "@ARG" << endl;
    fout << "D=M" << endl;
    fout << "@SP" << endl;
    fout << "M=D+1" << endl;
    //THAT = *(FRAME-1)
    fout << "@13" << endl;
    fout << "D=M" << endl;
    fout << "@1" << endl;
    fout << "A=D-A" << endl;
    fout << "D=M" << endl;
    fout << "@4" << endl;
    fout << "M=D" << endl;
    //THIS = *(FRAME-2)
    fout << "@13" << endl;
    fout << "D=M" << endl;
    fout << "@2" << endl;
    fout << "A=D-A" << endl;
    fout << "D=M" << endl;
    fout << "@3" << endl;
    fout << "M=D" << endl;
    //ARG = *(FRAME-3)
    fout << "@13" << endl;
    fout << "D=M" << endl;
    fout << "@3" << endl;
    fout << "A=D-A" << endl;
    fout << "D=M" << endl;
    fout << "@2" << endl;
    fout << "M=D" << endl;
    //LCL = *(FRAME-4)
    fout << "@13" << endl;
    fout << "D=M" << endl;
    fout << "@4" << endl;
    fout << "A=D-A" << endl;
    fout << "D=M" << endl;
    fout << "@1" << endl;
    fout << "M=D" << endl;
    //goto RET
    fout << "@14" << endl;
    fout << "A=M" << endl;
    fout << "0;JMP" << endl;
}

void CodeWriter::writeIf(const string& arg1) {
    decSP();
    fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
    fout << "@" << arg1 <<  endl;
    fout << "D;JNE" << endl;
}

void CodeWriter::writeGoto(const string& arg1) {
    fout << "@" << arg1 <<  endl;
    fout << "0;JMP" << endl;
}

void CodeWriter::incSP() {
    fout << "@SP" << endl << "M=M+1" << endl;
}

void CodeWriter::decSP() {
    fout << "@SP" << endl << "M=M-1" << endl;
}