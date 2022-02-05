#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    Parser parser(argv[1]);
    while (parser.hasMoreCommands()) {
        parser.advance();
        VMCommand type = parser.commandType();
        if(type != C_NULL) {
            cout << parser.command << endl;
            cout << "type = " << type << endl;
            cout << "arg1 = " << parser.arg1() << endl;
            if (type == C_PUSH || type == C_POP || type == C_FUNCTION || type == C_CALL) {
                cout << "arg2 = " << parser.arg2() << endl;
            }
        }
    }
    return 0;
}
