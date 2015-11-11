#ifndef calcLex_h
#define calcLex_h

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

enum calcGrammarTokens { endOfFileSym = 0, assignSym, readSym, writeSym, identifier, addOp, multOp, leftParen, rightParen, numConst};

#define CALCTEXT_MAX 100
extern char calcText[CALCTEXT_MAX]; // Global token text buffer

bool calcLexOpen(const char filename[]);
void calcTextOpen();
void calcTextAppend(int currentChar); //what does c mean?
int calcLex();
int followingChars(string target, int returnSymbol);
#endif /* calcLex_h */
