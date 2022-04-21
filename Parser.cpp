//
// Created by robin on 2022/1/29.
//

#include "Parser.h"
#include <string>
#include <iostream>

using namespace std;

Parser::Parser(string filename) {
    filename += ".vm";
    fin.open(filename);
    if (!fin.is_open())
        cerr << "Error: Could not open " << filename << ".\n";
}

Parser::~Parser() {
    if(fin.is_open()) {
        fin.close();
    }
}

bool Parser::hasMoreCommands() {
    return !fin.eof();
}

void Parser::advance() {
    getline(fin, command);
}

VMCommand Parser::commandType() {
    if(command.empty() || command[0] =='/') {
        return C_NULL;
    } else {
        if (command.find("push") != string::npos) {
            return C_PUSH;
        } else if (command.find("pop") != string::npos) {
            return C_POP;
        } else if (command.find("label") != string::npos) {
            return C_LABEL;
        } else if (command.find("if") != string::npos) {
            return C_IF;
        } else if (command.find("goto") != string::npos) {
            return C_GOTO;
        } else if (command.find("function") != string::npos) {
            return C_FUNCTION;
        } else if (command.find("return") != string::npos) {
            return C_RETURN;
        } else if (command.find("call") != string::npos) {
            return C_CALL;
        } else {
            return C_ARITHMETIC;
        }
    }
}

string Parser::arg1() {
    VMCommand type = commandType();
    string arg;
    if (type != C_RETURN) {
        int firstIndex = command.find(' ', 0);
        int secondIndex = command.find(' ', firstIndex+1);
        arg = command.substr(firstIndex+1, secondIndex-firstIndex-1);
    }
    return arg;
}

int Parser::arg2() const {
    int secondIndex = 0, slashIndex = 0;
    for (int i = 0; i < 2; ++i){
        secondIndex = (command.find(' ', secondIndex)) + 1;
    }
    string arg = command.substr(secondIndex);
    if (command.find("//") != string::npos) {
        slashIndex = arg.find("//", slashIndex);
        arg = arg.substr(0, slashIndex);
    }
    return stoi(arg);
}
