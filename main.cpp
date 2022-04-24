#include <iostream>
#include "Parser.h"
#include "CodeWriter.h"
#include <dirent.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 2) {
        struct dirent *d;
        DIR *dr;
        dr = opendir(".");
        if(dr!=NULL)
        {
            string fileName = argv[1];
            fileName = fileName.substr(fileName.find_last_of("/\\") + 1);
            CodeWriter codeWriter(fileName);
            codeWriter.writeInit();
//            cout<<"List of Files & Folders:-\n";
            for(d=readdir(dr); d!=NULL; d=readdir(dr))
            {
                string currentFile = string(d->d_name);
                if (currentFile.size() >= 3 && currentFile.substr(currentFile.size()-3) == ".vm") {
//                    cout << currentFile << endl;
                    currentFile = currentFile.substr(0,currentFile.size()-3);
                    Parser parser(currentFile);
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
                }
//                cout<<d->d_name<<endl;
            }
            closedir(dr);
        }
        else
            cout<<"\nError Occurred!";
        cout<<endl;
    } else {
        Parser parser(argv[1]);
        CodeWriter codeWriter(argv[2]);
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
    }
    return 0;
}
