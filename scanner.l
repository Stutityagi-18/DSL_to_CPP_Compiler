%{

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include "parser.tab.h"

using namespace std;

%}

%option noyywrap

DIGIT           [0-9]
LETTER          [a-zA-Z]
ID              {LETTER}({LETTER}|{DIGIT}|_)*
NUMBER          {DIGIT}+
ADDR_LITERAL    0x[a-fA-F0-9]{40}

%%

"contract"              { return CONTRACT; }
"function"              { return FUNCTION; }
"public"                { return PUBLIC; }
"returns"               { return RETURNS; }

"return"                { return RETURN; }
"if"                    { return IF; }
"else"                  { return ELSE; }

"uint"                  { return UINT; }
"int"                   { return INT; }
"bool"                  { return BOOL; }
"address"               { return ADDRESS; }

"true"                  { return TRUE; }
"false"                 { return FALSE; }

{ADDR_LITERAL} {
    yylval.text = strdup(yytext);
    return ADDRESS_LITERAL;
}
{NUMBER} {
    yylval.number = atoi(yytext);
    return NUMBER;
}

{ID} {
    yylval.text = strdup(yytext);
    return IDENTIFIER;
}

"=="                    { return EQ; }
"!="                    { return NEQ; }
">="                    { return GE; }
"<="                    { return LE; }
">"                     { return GT; }
"<"                     { return LT; }

"&&"                    { return AND; }
"||"                    { return OR; }
"!"                     { return NOT; }

"+"                     { return PLUS; }
"-"                     { return MINUS; }
"*"                     { return MUL; }
"/"                     { return DIV; }
"%"                     { return MOD; }

"="                     { return ASSIGN; }

"("                     { return LPAREN; }
")"                     { return RPAREN; }

"{"                     { return LBRACE; }
"}"                     { return RBRACE; }

","                     { return COMMA; }
";"                     { return SEMICOLON; }

[ \t\r\n]+    ;

. {
    printf("Unknown character: %s\n", yytext);
}

%%