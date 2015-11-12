#include "calcLex.h"

char calcText[CALCTEXT_MAX]; //this holds the token name
static int calcTextPos; //static keyword keeps var around, no re-initialization with each call of the lexer

//this function opens the "filestream" var and returns true or false for success
ifstream filestream;
bool calcLexOpen(const char filename[])
{
    filestream.open(filename, ios_base::in);
    return filestream.is_open();
}

//this function resets the position of the scanner in the file
void calcTextClear()
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
    char currentChar;

    while(1) //infinite loop, breaks through a return statement
    {
        calcTextClear();
        currentChar = filestream.get(); //get the next char!

        //used to ignore whitespace as a token
        while( currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
        {
          currentChar = filestream.get();
        };

        if(currentChar == EOF)
        {
            return endOfFileSym;
        }

        if(followingChars("/*", currentChar))
        {
            while(currentChar != '\n' && !followingChars("*/", currentChar))
            {
              currentChar = filestream.get();
            }
            currentChar = filestream.get();
            calcTextClear();
        }
        if(followingChars(":=", currentChar))
        {
            return assignSym;
        }
        if(followingChars("read", currentChar))
        {
            return readSym;
        }
        if(followingChars("write", currentChar))
        {
            return writeSym;
        }
        calcTextAppend(currentChar);
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
        if(currentChar >= '0' && currentChar <= '9')
        {
            while( (currentChar = filestream.get()) >= '0' && currentChar <= '9')
            {
                calcTextAppend(currentChar);
            }

            filestream.unget();
            return numConst;
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

        return currentChar; //scanner doesn't know what this char is, throw it away
    }

    return endOfFileSym; //this should never be returned from here
}


//function that finds if the chars following match a target symbol
bool followingChars(string target, char currentChar)
{
    for(int x = 0; x < target.length(); x++)
    {
        if(currentChar == target[x])
        {
            calcTextAppend(currentChar);
            currentChar = filestream.get();
        }
        else
        {
            calcTextClear();
            while(x != 0)
            {
              filestream.unget();
              x--;
            }
            return false;
        }
    }
    filestream.unget();
    return true;
}
