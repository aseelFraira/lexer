%{
#include "tokens.hpp"
#include "output.hpp"

extern int yylineno;
%}

%option noyywrap
%option yylineno

whitespace  ([\t\n\r ])
RELOP   (==|!=|>=|<=|>|<)
BINOP   (\+|\-|\*|/)
letter  [a-zA-Z]
digit   [0-9]
anyCharec [!#-\[\]-~]
hexa [0-9A-Fa-f]
esc [\\ntr"0]|(x([0-7]){hexa}{2})
stringchar ({anyCharec}|\t|(\\{esc})|[ ])
%x STRING_S

%%

{WS}                        /* skip */;

"void"                     { printToken(yylineno, VOID, yytext); return VOID; }
"int"                      { printToken(yylineno, INT, yytext); return INT; }
"byte"                     { printToken(yylineno, BYTE, yytext); return BYTE; }
"bool"                     { printToken(yylineno, BOOL, yytext); return BOOL; }
"and"                      { printToken(yylineno, AND, yytext); return AND; }
"or"                       { printToken(yylineno, OR, yytext); return OR; }
"not"                      { printToken(yylineno, NOT, yytext); return NOT; }
"true"                     { printToken(yylineno, TRUE, yytext); return TRUE; }
"false"                    { printToken(yylineno, FALSE, yytext); return FALSE; }
"return"                   { printToken(yylineno, RETURN, yytext); return RETURN; }
"if"                       { printToken(yylineno, IF, yytext); return IF; }
"else"                     { printToken(yylineno, ELSE, yytext); return ELSE; }
"while"                    { printToken(yylineno, WHILE, yytext); return WHILE; }
"break"                    { printToken(yylineno, BREAK, yytext); return BREAK; }
"continue"                 { printToken(yylineno, CONTINUE, yytext); return CONTINUE; }

";"                        { printToken(yylineno, SC, yytext); return SC; }
","                        { printToken(yylineno, COMMA, yytext); return COMMA; }
"("                        { printToken(yylineno, LPAREN, yytext); return LPAREN; }
")"                        { printToken(yylineno, RPAREN, yytext); return RPAREN; }
"{"                        { printToken(yylineno, LBRACE, yytext); return LBRACE; }
"}"                        { printToken(yylineno, RBRACE, yytext); return RBRACE; }
"["                        { printToken(yylineno, LBRACK, yytext); return LBRACK; }
"]"                        { printToken(yylineno, RBRACK, yytext); return RBRACK; }
"="                        { printToken(yylineno, ASSIGN, yytext); return ASSIGN; }

{RELOP}                    { printToken(yylineno, RELOP, yytext); return RELOP; }
{BINOP}                    { printToken(yylineno, BINOP, yytext); return BINOP; }

"//"[^\r\n]*               { printToken(yylineno, COMMENT, yytext); return COMMENT; }

{letter}({letter}|{digit})* { printToken(yylineno, ID, yytext); return ID; }
0|[1-9][0-9]*               { printToken(yylineno, NUM, yytext); return NUM; }
(0|[1-9][0-9]*)b            { printToken(yylineno, NUM_B, yytext); return NUM_B; }
\"{stringchar}*\"            {printToken(yylineno,STRING_S,yytext); return STRING;}    
\"{stringchar}+               {return UNCLOSED_STRING;}
\"(stringchar)*\\[^\\ntr\"0]  {return UNDEF_ESCAPE;}


.                          { return UNKNOWN_CHAR; }

%%
