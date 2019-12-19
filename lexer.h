//
// Created by yakir on 12/18/19.
//

#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include <cstring>
#include <vector>
#include <fstream>
#include <vector>

using namespace std;


class lexer {
private:
    string tok;
    vector<string> tokens;
public:
    lexer();
    ~lexer();
    vector<string> lex(string fileName);
    bool isNumber(string s);
};


#endif //EX3_LEXER_H
