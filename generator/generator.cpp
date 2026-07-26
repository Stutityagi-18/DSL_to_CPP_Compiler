#include "generator.h"

#include <sstream>

using namespace std;

static string mapType(const string &type)
{
    if(type == "uint") return "unsigned long long";
    if(type == "int") return "long long";
    if(type == "bool") return "bool";
    if(type == "address") return "string";

    return "auto";
}

static void generateExpression(ExpressionNode *expr, ostringstream &out)
{
    if(!expr)
        return;

    if(auto *num = dynamic_cast<NumberNode*>(expr))
    {
        out << num->value;
    }
    else if(auto *id = dynamic_cast<IdentifierNode*>(expr))
    {
        out << id->name;
    }
    else if(auto *b = dynamic_cast<BooleanNode*>(expr))
    {
        out << (b->value ? "true" : "false");
    }
    else if(auto *addr = dynamic_cast<AddressNode*>(expr))
    {
        out << "\"" << addr->value << "\"";
    }
    else if(auto *unary = dynamic_cast<UnaryExpressionNode*>(expr))
    {
        out << "(" << unary->op;
        generateExpression(unary->expr, out);
        out << ")";
    }
    else if(auto *bin = dynamic_cast<BinaryExpressionNode*>(expr))
    {
        out << "(";
        generateExpression(bin->left, out);
        out << " " << bin->op << " ";
        generateExpression(bin->right, out);
        out << ")";
    }
}

static void generateStatements(
    const vector<StatementNode*> &stmts,
    ostringstream &out,
    int indent);

static void generateStatement(
    StatementNode *stmt,
    ostringstream &out,
    int indent)
{
    string pad(indent, ' ');

    if(auto *var = dynamic_cast<VariableDeclarationNode*>(stmt))
    {
        out << pad
            << mapType(var->type)
            << " "
            << var->name;

        if(var->value)
        {
            out << " = ";
            generateExpression(var->value, out);
        }

        out << ";\n";
    }
    else if(auto *assign = dynamic_cast<AssignmentNode*>(stmt))
    {
        out << pad
            << assign->name
            << " = ";

        generateExpression(assign->value, out);

        out << ";\n";
    }
    else if(auto *ret = dynamic_cast<ReturnNode*>(stmt))
    {
        out << pad << "return ";

        generateExpression(ret->value, out);

        out << ";\n";
    }
    else if(auto *expr = dynamic_cast<ExpressionStatementNode*>(stmt))
    {
        out << pad;
        generateExpression(expr->expr, out);
        out << ";\n";
    }
    else if(auto *node = dynamic_cast<IfNode*>(stmt))
    {
        out << pad << "if(";
        generateExpression(node->condition, out);
        out << ")\n";

        out << pad << "{\n";
        generateStatements(node->thenStatements, out, indent + 4);
        out << pad << "}";

        if(!node->elseStatements.empty())
        {
            out << " else\n";
            out << pad << "{\n";
            generateStatements(node->elseStatements, out, indent + 4);
            out << pad << "}";
        }

        out << "\n";
    }
}

static void generateStatements(
    const vector<StatementNode*> &stmts,
    ostringstream &out,
    int indent)
{
    for(auto *stmt : stmts)
    {
        generateStatement(stmt, out, indent);
    }
}

static void generateFunction(
    FunctionNode *func,
    ostringstream &out)
{
    out << "    "
        << mapType(func->returnType)
        << " "
        << func->name
        << "(";

    for(size_t i = 0; i < func->parameters.size(); i++)
    {
        if(i > 0)
            out << ", ";

        out << mapType(func->parameters[i].first)
            << " "
            << func->parameters[i].second;
    }

    out << ")\n";
    out << "    {\n";

    generateStatements(func->statements, out, 8);

    out << "    }\n\n";
}

string generateCode(ContractNode *contract)
{
    ostringstream out;

    out << "#include <string>\n\n";

    out << "using namespace std;\n\n";

    out << "class "
        << contract->contractName
        << "\n{\n";

    out << "public:\n\n";

    for(auto *func : contract->functions)
    {
        generateFunction(func, out);
    }

    out << "};\n\n";

    out << "int main()\n";
    out << "{\n";
    out << "    "
        << contract->contractName
        << " contract;\n";
    out << "    return 0;\n";
    out << "}\n";

    return out.str();
}