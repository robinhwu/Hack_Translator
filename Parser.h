//
// Created by robin on 2022/1/29.
//

#ifndef HACK_TRANSLATOR_PARSER_H
#define HACK_TRANSLATOR_PARSER_H

#include <string>
#include "fstream"

using namespace std;

// VM commands
enum VMCommand { C_ARITHMETIC, C_PUSH, C_POP, C_LABEL, C_IF, C_GOTO, C_FUNCTION, C_RETURN, C_CALL, C_NULL };

class Parser {
public:

    explicit Parser(string filename);

    ~Parser();

    bool hasMoreCommands();

    void advance();

    VMCommand commandType();

    string arg1();

    int arg2() const;

    ifstream fin;

    string command;

};


#endif //HACK_TRANSLATOR_PARSER_H
