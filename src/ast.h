#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

using namespace std;

//========================
// Base Nodes
//========================

struct ASTNode
{
    virtual ~ASTNode() {}
};

struct ExpressionNode : ASTNode
{
    virtual ~ExpressionNode() {}
};

struct StatementNode : ASTNode
{
    virtual ~StatementNode() {}
};

//========================
// Expressions
//========================

struct NumberNode : ExpressionNode
{
    int value;

    NumberNode(int v)
    {
        value = v;
    }
};

struct BooleanNode : ExpressionNode
{
    bool value;

    BooleanNode(bool v)
    {
        value = v;
    }
};

struct AddressNode : ExpressionNode
{
    string value;

    AddressNode(const string &v)
    {
        value = v;
    }
};

struct IdentifierNode : ExpressionNode
{
    string name;

    IdentifierNode(const string &n)
    {
        name = n;
    }
};

struct UnaryExpressionNode : ExpressionNode
{
    string op;
    ExpressionNode *expr;

    UnaryExpressionNode(const string &o,
                        ExpressionNode *e)
    {
        op = o;
        expr = e;
    }
};

struct BinaryExpressionNode : ExpressionNode
{
    string op;

    ExpressionNode *left;
    ExpressionNode *right;

    BinaryExpressionNode(
        ExpressionNode *l,
        const string &o,
        ExpressionNode *r)
    {
        left = l;
        op = o;
        right = r;
    }
};

//========================
// Statements
//========================

struct VariableDeclarationNode : StatementNode
{
    string type;
    string name;

    ExpressionNode *value;

    VariableDeclarationNode(
        const string &t,
        const string &n,
        ExpressionNode *v)
    {
        type = t;
        name = n;
        value = v;
    }
};

struct AssignmentNode : StatementNode
{
    string name;
    ExpressionNode *value;

    AssignmentNode(
        const string &n,
        ExpressionNode *v)
    {
        name = n;
        value = v;
    }
};

struct ReturnNode : StatementNode
{
    ExpressionNode *value;

    ReturnNode(ExpressionNode *v)
    {
        value = v;
    }
};

struct ExpressionStatementNode : StatementNode
{
    ExpressionNode *expr;

    ExpressionStatementNode(ExpressionNode *e)
    {
        expr = e;
    }
};

struct IfNode : StatementNode
{
    ExpressionNode *condition;

    vector<StatementNode *> thenStatements;
    vector<StatementNode *> elseStatements;

    IfNode(ExpressionNode *c)
    {
        condition = c;
    }
};

//========================
// Function
//========================

struct FunctionNode : ASTNode
{
    string name;
    string returnType;

    vector<pair<string, string>> parameters;
    vector<StatementNode *> statements;
};

//========================
// Contract
//========================

struct ContractNode : ASTNode
{
    string contractName;

    vector<FunctionNode *> functions;
};

#endif