#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser(argv[1]);
    CodeWriter codeWriter(argv[2]);
    while (parser.hasMoreCommands()) {
        parser.advance();
        VMCommand type = parser.commandType();
        if(type != C_NULL) {
//            cout << parser.command << endl;
//            cout << "type = " << type << endl;
//            cout << "arg1 = " << parser.arg1() << endl;
            if (type == C_PUSH || type == C_POP || type == C_FUNCTION || type == C_CALL) {
//                cout << "arg2 = " << parser.arg2() << endl;
                if (type == C_PUSH || type == C_POP) {
                    codeWriter.writePushPop(type, parser.arg1(), parser.arg2());
                } else {

                }
            } else if (type == C_ARITHMETIC) {
                codeWriter.writeArithmetic(parser.command);
            }
        }
    }
    return 0;
}
