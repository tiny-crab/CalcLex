#include "calcLex.h"

int main(int argc, const char *argv[])
{
    //get the file name from the command line input
    if(argc > 1 && (!calcLexOpen( argv[1]) ) )
    {
        cout << "Sorry, I can't find/open that file!" << argv[1] << endl;
        exit(1);
    }

    int token = calcLex();
    while( token != endOfFileSym )
    {
        cout << "Token(" << token << "): " << calcText << endl;
        token = calcLex();
    }

    return 0;
}
