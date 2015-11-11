#include "calcLex.h"

char calcText[CALCTEXT_MAX]; //global token char buffer (?)
static int calcTextPos; //static keyword keeps var around, no re-initialization with each call of the lexer

//this function opens the "filestream" var and returns true or false for success
ifstream filestream;
bool calcLexOpen(const char filename[])
{
    filestream.open(filename, ios_base::in); //I don't know what ios_base does
    return filestream.is_open();
}

//this function resets the position of the scanner in the file
void calcLexClear()
{
    calcTextPos = 0;
    calcText[calcTextPos] = 0;
}

//this function
void calcTextAppend(int currentChar)
{
    if(calcTextPos >= (CALCTEXT_MAX - 1) )
    {
        return; //ignore the char
    }
    calcText[calcTextPos++] = (char)currentChar;
    calcText[calcTextPos] = 0;
}

int calcLex()
{
    int currentChar;
    
    while(1) //infinite loop, breaks through a return statement
    {
        calcLexClear();
        currentChar = filestream.get(); //get the next char!
        //used to ignore whitespace as a token
        while( currentChar == ' ' || currentChar == '\t');
        
        if(currentChar == EOF || currentChar == '\n')
        {
            return endOfFileSym; //using newline as end of file symbol, may need to change
        }
        string hi = "hi";
        
        calcTextAppend(currentChar);
        if(followingChars(hi))
        {
            return assignSym;
        }
    }
}


//function that finds if the chars following match a target symbol
bool followingChars(string target)
{
    char currentChar = filestream.get();
    for( int x = 0; x < target.length(); x++)
    {
        if(currentChar == target[x])
        {
            currentChar = filestream.get();
        }
        else
        {
            return false;
        }
    }
    
    return true;
}

