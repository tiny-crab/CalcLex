#include "calcLex.h"

char calcText[CALCTEXT_MAX]; //this holds the token name
static int calcTextPos; //static keyword keeps var around, no re-initialization with each call of the lexer

//this function opens the "filestream" var and returns true or false for success
ifstream filestream;
bool calcLexOpen(const char filename[])
{
    filestream.open(filename, ios_base::in);
    //returning true or false if the filestream is open
    return filestream.is_open();
}

//this function resets the token's info
void calcTextClear()
{
    calcTextPos = 0;
    calcText[calcTextPos] = 0;
}

//this function pushes chars onto the token's info cstring
void calcTextAppend(int currentChar)
{
    if(calcTextPos >= (CALCTEXT_MAX - 1) )
    {
        return; //ignore the char
    }
    calcText[calcTextPos++] = (char)currentChar;
    calcText[calcTextPos] = 0;
}

//this function finds the next token and outputs it
int calcLex()
{
    char currentChar;

    while(1) //infinite loop, breaks through a return statement
    {
        //clear out the token info from last time
        calcTextClear();
        //get the next char!
        currentChar = filestream.get();

        //used to ignore whitespace as a token
        while( currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
        {
          currentChar = filestream.get();
        };

        //if the current char is the end of a file, it returns the end of file symbol
        if(currentChar == EOF)
        {
            return endOfFileSym;
        }

        //this is the comment logic: if the next chars are /*...
        if(followingChars("/*", currentChar))
        {
            //then while it isn't ending the line, or finding the end of comment sentinel...
            while(currentChar != '\n' && !followingChars("*/", currentChar))
            {
              //move onto the next character
              currentChar = filestream.get();
            }
            //move to the next character after the comment or line has ended
            currentChar = filestream.get();
            //hop back up to the top of the while loop
            continue;
        }
        //if the chars ":=" are found, return the assignment symbol
        if(followingChars(":=", currentChar))
        {
            return assignSym;
        }
        //if the chars "read" are found, return the read symbol
        if(followingChars("read", currentChar))
        {
            return readSym;
        }
        //if the chars "write" are found, return the write symbol
        if(followingChars("write", currentChar))
        {
            return writeSym;
        }

        //this line must go below the followingChars checking, because otherwise you get double chars in your token info
        calcTextAppend(currentChar);

        //checks for identifier strings, must only use letters
        if( (currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
        {
            //messy line, but gets new char and checks between capital letters and lowercase letters on the ascii table
            while(((currentChar = filestream.get()) >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'))
            {
                calcTextAppend(currentChar);
            }

            //once the currentChar falls off the end of the identifier string, it must hop back to read the next one
            filestream.unget();
            //returns the identifier int
            return identifier;
        }

        //numeric constant must start with a digit, never with a decimal
        //if the current char is a number, or float starting with a decimal...
        if((currentChar >= '1' && currentChar <= '9') || currentChar == '.')
        {
            cout << "I found a numeric constant" << endl;
            //this makes sure it does not have more than one decimal, and it starts with a decimal
            if(currentChar == '.')
            {
              cout << "It had a decimal at the front." << endl;
              while( (currentChar = filestream.get()) >= '0' && currentChar <= '9')
              {
                  cout << "It had these numbers following the decimal:" << currentChar;
                  calcTextAppend(currentChar);
              }
            }
            //this makes sure that it can have any number of digits before a decimal, but only one decimal
            else
            {
              cout << "It didn't start with a decimal." << endl;
              //this can see an unlimited number of digits before a decimal...
              while( ((currentChar = filestream.get()) >= '0' && currentChar <= '9') || currentChar == '.')
              {
                  cout << "It had these numbers before the decimal: " << currentChar;
                  calcTextAppend(currentChar);
                  //but once it finds a decimal...
                  if(currentChar == '.')
                  {
                    cout << "I found a decimal here";
                    //get the next char
                    currentChar = filestream.get();
                    //if it isn't a digit, throw an exception (10 works because of the way main.cpp handles proper tokens)
                    if(!(currentChar >= '0' && currentChar <= '9'))
                    {
                      cout << "I got a number after the decimal";
                      return currentChar;
                    }
                    //infinite loop to check for remaining numbers
                    while(1)
                    {
                      currentChar = filestream.get();
                      if(currentChar >= '0' && currentChar <= '9')
                      {
                        calcTextAppend(currentChar);
                      }
                      if(currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
                      {
                        return numConst;
                      }
                      else
                      {
                        return currentChar;
                      }
                    }
                  }
              }
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
