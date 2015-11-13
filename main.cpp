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
    while( token <= 9 )
    {
        cout << "Token(" << token << ", " << translation(token) << "): " << calcText << endl;
        token = calcLex();
        if(token == endOfFileSym)
        {
          break;
        }
    }
    if(token > 9)
    {
      cout << "Unidentified Token! Sorry, I can't continue compiling. I was passed a token with value: " << token << endl;
    }


    return 0;
}

string translation(int identifier)
{
  switch (identifier) {
    case 0: return "End of File Symbol";
    case 1: return "Assignment Symbol";
    case 2: return "Read Symbol";
    case 3: return "Write Symbol";
    case 4: return "Identifier";
    case 5: return "Add Operation";
    case 6: return "Multiplication Operation";
    case 7: return "Left Parenthesis";
    case 8: return "Right Parenthesis";
    case 9: return "Numeric Constant";
    default: return "Unknown";
  }
}
