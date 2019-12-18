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

lexer::~lexer() {}

vector<string> lexer::lex(string fileName) {
    char ch;
    int i, flag = 0;
    string line;
    ifstream simData(fileName, ios::in);
    if (!simData) {
        throw "Couldn't open File";
    }
    while (!simData) {
        getline(simData, line);
        for (i = 0; i < line.length(); i++) {
            ch = line[i];
            if (isalpha(ch)) {
                tok += ch;
                continue;
            } else if (isdigit(ch)) {
                tok += ch;
                continue;
            } else {
                switch (ch) {
                    case '(':
                        tokens.push_back(tok);
                        tok = "";
                        if (line.find(',')) {
                            flag = 1;
                        }
                        continue;
                    case ')':
                        continue;
                    case '"':
                        continue;
                    case '.':
                        tok += ch;
                        continue;
                    case ',':
                        continue;
                    case '/':
                        tok += ch;
                        continue;
                    case '>':
                        if (tok[i - 1] == '-') {
                            tok += ch;
                            tokens.push_back(tok);
                            tok = "";
                        }
                        continue;
                    case '<':
                        tok += ch;
                        continue;
                    case '-':
                        if (tok[i - 1] == '<') {
                            tok += ch;
                            tokens.push_back(tok);
                            tok = "";
                        } else if (!flag) {
                            tok += ch;
                            while (ch != ')') {
                                i++;
                                ch = line[i];
                                tok += ch;
                            }
                            tokens.push_back(tok);
                        }
                        continue;
                    case '=':
                        continue;
                    case '{':
                        continue;;
                    case '}':
                        continue;
                    case ' ':
                        tokens.push_back(tok);
                        tok = "";
                        continue;
                }
            }
        }
    }
}