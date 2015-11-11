#include "calcLex.h"

int main(int argc, const char *argv[])
{
    //get the file name from the command line input
    if(argc > 1 && (!calcLexOpen( argv[1]) ) )
    {
        cout << "Sorry, I can't find/open that file!" << argv[1] << endl;
        exit(1);
    }
    
    int token;
    while( (token = calcLex()) != endOfFileSym )
    {
        cout << "Token(" << token << "): " << endl;
    }
    
    return 0;
}
