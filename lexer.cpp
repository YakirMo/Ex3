//
// Created by yakir on 12/18/19.
//

#include "lexer.h"
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

lexer::lexer() {
    string tok = "";
    vector<string> tokens;
}

lexer::~lexer() {
    tokens.clear();
}

bool lexer::isNumber(string s) {
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == 0)
            return false;

    return true;
}

vector<string> lexer::lex(string fileName) {
    char ch;
    streampos funcBegin;
    int i, flag = 0, skipSpace = 0, countFuncArgs = 0;
    string line;
    string coma = ", ";
    ifstream simData(fileName, ios::in);
    if (!simData) {
        throw "Couldn't open File";
    }
    while (!simData.eof()) {
        getline(simData, line);
        for (i = 0; i < line.length(); i++) {
            ch = line[i];
            if (isalpha(ch)) {
                tok += ch;
                skipSpace = 0; // last addition
                continue;
            } else if (isdigit(ch)) {
                tok += ch;
                skipSpace = 0; // last addition
                continue;
            } else {
                switch (ch) {
                    case '(':
                        tokens.push_back(tok);
                        tokens.push_back(coma);
                        tok = "";
                        if (line[ i + 1] != '"'){
                            while(line[i+1] != ')') {
                                tok += line[i +1];
                                i++;
                            }
                            continue;
                        }
                        if (line.find_first_of(',')) {
                            flag = 1;
                        }
                        skipSpace = 0; // last addition
                        continue;
                    case ')':
                        tokens.push_back(tok);
                        tokens.push_back(coma);
                        tok = "";
                        skipSpace = 1; // last addition
                        continue;
                    case '"':
                        if (line[i - 1] == '(') {
                            while (line[i + 1] != '"') {
                                tok += line[i + 1];
                                i++;
                            }
                            //tok += line[i];
                            i++;
                            continue;
                        }
                        continue;
                    case '.':
                        tok += ch;
                        skipSpace = 0; // last addition
                        continue;
                    case ',':
                        tokens.push_back(tok);
                        tokens.push_back(coma);
                        tok = "";
                        skipSpace = 1; // last addition
                        continue;
                    case '/':
                        tok += ch;
                        skipSpace = 0; // last addition
                        continue;
                    case '>':
                        if (line[i - 1] == '-' || line[i + 1] == '=') {
                            tok += ch;
                            tokens.push_back(tok);
                            tokens.push_back(coma);
                            tok = "";
                            skipSpace = 1;

                        }
                        continue;
                    case '<':
                        if (line[i + 1] == '-' || line[i + 1] == '=') {
                            tok += ch;
                            skipSpace = 0; // last addition
                        } else {
                            tok += ch;
                            tokens.push_back(tok);
                            tokens.push_back(coma);
                            tok = "";
                            skipSpace = 1; // last addition
                        }
                        continue;
                    case '-':
                        if (line[i - 1] == '<') {
                            tok += ch;
                            skipSpace = 0; // last addition
                            continue;
                        } else if (line[i + 1] == '>') {
                            tok += ch;
                            skipSpace = 0; // last addition
                            continue;
                        } else {
                            while (line[i] != ')' && line[i] != '"') {
                                //ch = line[i];
                                tok += line[i];
                                i++;
                            }
                        }
                        continue;
                    case '=':
                        if (line[i - 1] != '<' && line[i - 1] != '>') {
                            i++;
                            while (i < line.length()) {
                                if (line[i] != ' ') {
                                    tok += line[i];
                                }
                                i++;
                            }
                        }
                        if (!isNumber(tokens.back())) {
                            if (line[i - 1] == '<' || line[i - 1] == '>') {
                                tok += ch;
                            }
                            tokens.push_back(tok);
                            tokens.push_back(coma);
                            tok = "";
                            skipSpace = 1; // last addition
                        }
                        continue;
                    case '{':
                        funcBegin = simData.tellg();  // stores the position
                        while (ch != '}') {
                            getline(simData, line);
                            ch = line[0];
                            countFuncArgs += 1;
                        }
                        simData.seekg(funcBegin);   // get back to the position
                        tokens.push_back(to_string(countFuncArgs - 1));
                        tokens.push_back(coma);
                        tok = "";
                        skipSpace = 1; // last addition
                        continue;
                    case '}':
                        continue;
                    case ' ':
                        if (skipSpace != 1) {
                            tokens.push_back(tok);
                            tokens.push_back(coma);
                            tok = "";
                        }
                        continue;
                }
            }
        }
        flag = 0;
        skipSpace = 0;
        countFuncArgs = 0;
    }

    simData.close();

    return
            tokens;
}

