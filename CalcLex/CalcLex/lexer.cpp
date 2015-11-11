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
        
        calcTextAppend(currentChar);
        if(followingChars(":="))
        {
            return assignSym;
        }
        if(followingChars("read"))
        {
            return readSym;
        }
        if(followingChars("write"))
        {
            return writeSym;
        }
        if( (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
        {
            //messy line, but gets new char and checks between capital letters and lowercase letters on the ascii table
            while(((currentChar = filestream.get()) >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
            {
                calcTextAppend(currentChar);
            }
            
            filestream.unget();
            return identifier;
        }
        if(currentChar == '+' || currentChar == '-')
        {
            return addOp;
        }
        if(currentChar == '*' || currentChar == '/')
        {
            return multOp;
        }
        if(currentChar == '(')
        {
            return leftParen;
        }
        if(currentChar == ')')
        {
            return rightParen;
        }
        if(currentChar >= '0' && currentChar <= '9')
        {
            while( (currentChar = filestream.get()) >= '0' && currentChar <= '9')
            {
                calcTextAppend(currentChar);
            }
            
            filestream.unget();
            return numConst;
        }
        
        return currentChar; //scanner doesn't know what this is, throw it away
    }
    
    return endOfFileSym; //this should never be returned from here
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

