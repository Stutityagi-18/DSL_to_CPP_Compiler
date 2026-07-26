#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>

#include "../src/ast.h"

using namespace std;

// Generates the complete C++ source code from the AST.
string generateCode(ContractNode *contract);

#endif