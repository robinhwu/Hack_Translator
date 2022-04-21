#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser(argv[1]);
    CodeWriter codeWriter(argv[2]);
    codeWriter.writeInit();
    while (parser.hasMoreCommands()) {
        parser.advance();
        VMCommand type = parser.commandType();
        if(type != C_NULL) {
            if (type == C_PUSH || type == C_POP || type == C_FUNCTION || type == C_CALL) {
                if (type == C_PUSH || type == C_POP) {
                    codeWriter.writePushPop(type, parser.arg1(), parser.arg2());
                } else if (type == C_FUNCTION) {
                    codeWriter.writeFunction(parser.arg1(), parser.arg2());
                } else {
                    codeWriter.writeCall(parser.arg1(), parser.arg2());
                }
            } else if (type == C_ARITHMETIC) {
                codeWriter.writeArithmetic(parser.command);
            } else if (type == C_LABEL) {
                codeWriter.writeLabel(parser.arg1());
            } else if (type == C_IF) {
                codeWriter.writeIf(parser.arg1());
            } else if (type == C_GOTO) {
                codeWriter.writeGoto(parser.arg1());
            } else {
                codeWriter.writeReturn();
            }
        }
    }
    return 0;
}
