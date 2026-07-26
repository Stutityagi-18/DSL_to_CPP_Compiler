%{

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "ast.h"

using namespace std;

extern int yylex();
extern FILE *yyin;

void yyerror(const char *s);

ContractNode *root = nullptr;

%}

%code requires
{
    #include "ast.h"
    #include <vector>
    #include <string>

    using namespace std;
}
%union
{
    int number;
    bool boolean;
    char *text;

    ExpressionNode *expr;
    StatementNode *stmt;
    FunctionNode *func;
    ContractNode *contract;

    vector<StatementNode*> *stmtList;
    vector<FunctionNode*> *funcList;

    vector<pair<string,string>> *paramList;
    pair<string,string> *param;
}
%token CONTRACT
%token FUNCTION
%token PUBLIC
%token RETURNS

%token RETURN
%token IF
%token ELSE

%token UINT
%token INT
%token BOOL
%token ADDRESS

%token TRUE
%token FALSE

%token <number> NUMBER
%token <text> IDENTIFIER
%token <text> ADDRESS_LITERAL

%token PLUS
%token MINUS
%token MUL
%token DIV
%token MOD

%token ASSIGN

%token EQ
%token NEQ
%token GT
%token LT
%token GE
%token LE

%token AND
%token OR
%token NOT

%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE

%token COMMA
%token SEMICOLON

%left OR
%left AND
%left EQ NEQ
%left GT LT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%right UMINUS

%type <contract> program contract
%type <func> function
%type <funcList> function_list

%type <stmt> statement
%type <stmtList> statement_list block

%type <expr> expression literal

%type <text> type

%type <param> parameter
%type <paramList> parameter_list optional_parameters

%%

program
    : contract
    {
        root = $1;
    }
    ;

contract
    : CONTRACT IDENTIFIER LBRACE function_list RBRACE
    {
        $$ = new ContractNode();
        $$->contractName = $2;
        $$->functions = *$4;
        delete $4;
    }
    ;

function_list
    : function
    {
        $$ = new vector<FunctionNode*>();
        $$->push_back($1);
    }
    | function_list function
    {
        $1->push_back($2);
        $$ = $1;
    }
    ;

function
    : FUNCTION IDENTIFIER LPAREN optional_parameters RPAREN
      PUBLIC
      RETURNS LPAREN type RPAREN
      block
    {
        $$ = new FunctionNode();

        $$->name = $2;
        $$->returnType = $9;
        $$->parameters = *$4;
        $$->statements = *$11;

        delete $4;
        delete $11;
    }
    ;

optional_parameters
    :
    {
        $$ = new vector<pair<string,string>>();
    }
    | parameter_list
    {
        $$ = $1;
    }
    ;

parameter_list
    : parameter
    {
        $$ = new vector<pair<string,string>>();
        $$->push_back(*$1);
        delete $1;
    }
    | parameter_list COMMA parameter
    {
        $1->push_back(*$3);
        delete $3;
        $$ = $1;
    }
    ;

parameter
    : type IDENTIFIER
    {
        $$ = new pair<string,string>($1,$2);
    }
    ;

type
    : UINT
    {
        $$ = strdup("uint");
    }
    | INT
    {
        $$ = strdup("int");
    }
    | BOOL
    {
        $$ = strdup("bool");
    }
    | ADDRESS
    {
        $$ = strdup("address");
    }
    ;

block
    : LBRACE statement_list RBRACE
    {
        $$ = $2;
    }
    ;
statement_list
    :
    {
        $$ = new vector<StatementNode*>();
    }
    | statement_list statement
    {
        if($2 != nullptr)
            $1->push_back($2);
        $$ = $1;
    }
    ;

statement
    : type IDENTIFIER SEMICOLON
    {
        $$ = new VariableDeclarationNode($1, $2, nullptr);
    }

    | type IDENTIFIER ASSIGN expression SEMICOLON
    {
        $$ = new VariableDeclarationNode($1, $2, $4);
    }

    | IDENTIFIER ASSIGN expression SEMICOLON
    {
        $$ = new AssignmentNode($1, $3);
    }

    | RETURN expression SEMICOLON
    {
        $$ = new ReturnNode($2);
    }

    | IF LPAREN expression RPAREN block
    {
        IfNode *node = new IfNode($3);
        node->thenStatements = *$5;
        delete $5;
        $$ = node;
    }

    | IF LPAREN expression RPAREN block
      ELSE block
    {
        IfNode *node = new IfNode($3);
        node->thenStatements = *$5;
        node->elseStatements = *$7;

        delete $5;
        delete $7;

        $$ = node;
    }

    | expression SEMICOLON
    {
        $$ = new ExpressionStatementNode($1);
    }
    ;
literal
    : NUMBER
    {
        $$ = new NumberNode($1);
    }

    | TRUE
    {
        $$ = new BooleanNode(true);
    }

    | FALSE
    {
        $$ = new BooleanNode(false);
    }

    | ADDRESS_LITERAL
    {
        $$ = new AddressNode($1);
    }
    ;

expression
    : literal
    {
        $$ = $1;
    }

    | IDENTIFIER
    {
        $$ = new IdentifierNode($1);
    }

    | LPAREN expression RPAREN
    {
        $$ = $2;
    }

    | NOT expression
    {
        $$ = new UnaryExpressionNode("!", $2);
    }

    | MINUS expression %prec UMINUS
    {
        $$ = new UnaryExpressionNode("-", $2);
    }

    | expression PLUS expression
    {
        $$ = new BinaryExpressionNode($1, "+", $3);
    }

    | expression MINUS expression
    {
        $$ = new BinaryExpressionNode($1, "-", $3);
    }

    | expression MUL expression
    {
        $$ = new BinaryExpressionNode($1, "*", $3);
    }

    | expression DIV expression
    {
        $$ = new BinaryExpressionNode($1, "/", $3);
    }

    | expression MOD expression
    {
        $$ = new BinaryExpressionNode($1, "%", $3);
    }

    | expression EQ expression
    {
        $$ = new BinaryExpressionNode($1, "==", $3);
    }

    | expression NEQ expression
    {
        $$ = new BinaryExpressionNode($1, "!=", $3);
    }

    | expression GT expression
    {
        $$ = new BinaryExpressionNode($1, ">", $3);
    }

    | expression LT expression
    {
        $$ = new BinaryExpressionNode($1, "<", $3);
    }

    | expression GE expression
    {
        $$ = new BinaryExpressionNode($1, ">=", $3);
    }

    | expression LE expression
    {
        $$ = new BinaryExpressionNode($1, "<=", $3);
    }

    | expression AND expression
    {
        $$ = new BinaryExpressionNode($1, "&&", $3);
    }

    | expression OR expression
    {
        $$ = new BinaryExpressionNode($1, "||", $3);
    }
    ;

%%

void yyerror(const char *msg)
{
    cerr << "Parser Error: " << msg << endl;
}