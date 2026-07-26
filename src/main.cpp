#include <iostream>
#include <fstream>
#include <string>

#include "ast.h"
#include "../generator/generator.h"

using namespace std;

extern FILE *yyin;
extern int yyparse();

extern ContractNode *root;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input.dsl>" << endl;
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if(yyin == nullptr)
    {
        cout << "Unable to open input file." << endl;
        return 1;
    }

    if(yyparse() != 0)
    {
        cout << "Parsing failed." << endl;
        fclose(yyin);
        return 1;
    }

    fclose(yyin);

    string code = generateCode(root);

    // Generate output file name from input file
    string inputFile = argv[1];

    size_t dotPos = inputFile.find_last_of('.');
    string outputFile;

    if(dotPos != string::npos)
        outputFile = inputFile.substr(0, dotPos) + ".cpp";
    else
        outputFile = inputFile + ".cpp";

    ofstream out(outputFile);

    if(!out)
    {
        cout << "Unable to create output file." << endl;
        return 1;
    }

    out << code;
    out.close();

    cout << "Parsing successful." << endl;
    cout << "Generated " << outputFile << endl;

    return 0;
}