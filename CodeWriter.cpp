//
// Created by robin on 2022/2/5.
//

#include "CodeWriter.h"
#include <string>
#include <iostream>
#include "Parser.h"

using namespace std;

CodeWriter::CodeWriter(string filename) {
    setFileName(filename);
}

CodeWriter::~CodeWriter() {
    close();
}

void CodeWriter::setFileName(string filename) {
    symbolCount = 0;
    filename += ".asm";
    fout.open(filename);
    if (!fout.is_open())
        cerr << "Error: Could not open " << filename << ".\n";
}

void CodeWriter::close() {
    if (fout.is_open())
        fout.close();
}

void CodeWriter::writeArithmetic(string command) {
    if (command == "add")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "M=M+D" << endl;
        incSP();
    }
    else if (command == "sub")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "M=M-D" << endl;
        incSP();
    }
    else if (command == "neg")
    {
        decSP();
        fout << "A=M" << endl << "M=-M" << endl;
        incSP();
    }
    else if (command == "not")
    {
        decSP();
        fout << "A=M" << endl << "M=!M" << endl;
        incSP();
    }
    else if (command == "and")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "M=M&D" << endl;
        incSP();
    }
    else if (command == "or")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "M=M|D" << endl;
        incSP();
    }
    else if (command == "eq")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "D=M-D" << endl;
        fout << "@TRUE" << to_string(symbolCount) << endl;
        fout << "D;JEQ" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=0" << endl;
        fout << "@CONTINUE" << to_string(symbolCount) << endl;
        fout << "0;JMP" << endl;
        fout << "(TRUE"<< to_string(symbolCount) << ")" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=-1" << endl;
        fout << "(CONTINUE"<< to_string(symbolCount) << ")" << endl;
        incSP();
        symbolCount++;
    }
    else if (command == "gt")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "D=M-D" << endl;
        fout << "@TRUE" << to_string(symbolCount) << endl;
        fout << "D;JGT" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=0" << endl;
        fout << "@CONTINUE" << to_string(symbolCount) << endl;
        fout << "0;JMP" << endl;
        fout << "(TRUE"<< to_string(symbolCount) << ")" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=-1" << endl;
        fout << "(CONTINUE"<< to_string(symbolCount) << ")" << endl;
        incSP();
        symbolCount++;
    }
    else if (command == "lt")
    {
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl;
        decSP();
        fout << "A=M" << endl << "D=M-D" << endl;
        fout << "@TRUE" << to_string(symbolCount) << endl;
        fout << "D;JLT" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=0" << endl;
        fout << "@CONTINUE" << to_string(symbolCount) << endl;
        fout << "0;JMP" << endl;
        fout << "(TRUE"<< to_string(symbolCount) << ")" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=-1" << endl;
        fout << "(CONTINUE"<< to_string(symbolCount) << ")" << endl;
        incSP();
        symbolCount++;
    }
}

void CodeWriter::writePushPop(VMCommand pushOrPop, string arg1, int arg2) {
    if(pushOrPop == C_PUSH) {
        writePush(arg1,arg2);
    } else {
        writePop(arg1, arg2);
    }
}

void CodeWriter::writePush(string arg1, int arg2) {
    if (arg1 == "constant")
    {
        fout << "@" << arg2 << endl << "D=A" << endl << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "local") {
        fout << "@LCL" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "A=D" << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "argument") {
        fout << "@ARG" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "A=D" << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "this") {
        fout << "@3" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "A=D" << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "that") {
        fout << "@4" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "A=D" << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "pointer") {
        arg2 += 3;
        fout << "@" << to_string(arg2) << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else if (arg1 == "temp") {
        arg2 += 5;
        fout << "@" << to_string(arg2) << endl << "D=M" << endl;
        fout << "@SP" << endl << "A=M" << endl << "M=D" << endl;
        incSP();
    } else {

    }
}

void CodeWriter::writePop(string arg1, int arg2) {
    if (arg1 == "local") {
        fout << "@LCL" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "@13" << endl << "M=D" << endl;
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl << "@13" << endl << "A=M" << endl << "M=D" << endl;
    } else if (arg1 == "argument") {
        fout << "@ARG" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "@13" << endl << "M=D" << endl;
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl << "@13" << endl << "A=M" << endl << "M=D" << endl;
    } else if (arg1 == "this") {
        fout << "@3" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "@13" << endl << "M=D" << endl;
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl << "@13" << endl << "A=M" << endl << "M=D" << endl;
    } else if (arg1 == "that") {
        fout << "@4" << endl << "D=M" << endl << "@" << to_string(arg2) << endl << "D=D+A" << endl;
        fout << "@13" << endl << "M=D" << endl;
        decSP();
        fout << "@SP" << endl << "A=M" << endl << "D=M" << endl << "@13" << endl << "A=M" << endl << "M=D" << endl;
    } else if (arg1 == "pointer") {
        arg2 += 3;
        decSP();
        fout << "@" << to_string(arg2) << endl << "M=D" << endl;
    } else if (arg1 == "temp") {
        arg2 += 5;
        decSP();
        fout << "@" << to_string(arg2) << endl << "M=D" << endl;
    } else {

    }
}

void CodeWriter::incSP() {
    fout << "@SP" << endl << "M=M+1" << endl;
}

void CodeWriter::decSP() {
    fout << "@SP" << endl << "M=M-1" << endl;
}