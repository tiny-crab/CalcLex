#ifndef calcLex_h
#define calcLex_h

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

enum calcGrammarTokens {
    endOfFileSym = 0, assignSym, readSym, writeSym, identifier,
    addOp, multOp, leftParen, rightParen, numConst};

#define CALCTEXT_MAX 100
extern char calcText[CALCTEXT_MAX];

bool calcLexOpen(const char filename[]);
void calcTextOpen();
void calcTextClear();
void calcTextAppend(int currentChar);
int calcLex();
bool followingChars(string target, char currentChar);
#endif /* calcLex_h */
