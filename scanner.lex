%{
#include "tokens.hpp"
#include "output.hpp"

extern int yylineno;
%}

%option noyywrap
%option yylineno

whitespace  ([\t\n\r ])
RELOP   (==|!=|>=|<=|>|<)
BINOP   ([\+|\-|\*|/])
letter  [a-zA-Z]
digit   [0-9]
letteranddigit      ([a-zA-Z0-9])
anyCharec [!#-\[\]-~]
hexa [0-9A-Fa-f]
esc [\\ntr"0]|(x([0-7]){hexa})
stringchar ({anyCharec}|\t|(\\{esc})|[ ])
%x STRING_S

%%

{whitespace}                        /* skip */;

"void"                     { return VOID; }
"int"                      {  return INT; }
"byte"                     {return BYTE; }
"bool"                     { return BOOL; }
"and"                      { return AND; }
"or"                       { return OR; }
"not"                      {  return NOT; }
"true"                     {  return TRUE; }
"false"                    {  return FALSE; }
"return"                   {  return RETURN; }
"if"                       {  return IF; }
"else"                     {  return ELSE; }
"while"                    {  return WHILE; }
"break"                    {  return BREAK; }
"continue"                 {  return CONTINUE; }

";"                        {  return SC; }
","                        { return COMMA; }
"("                        {  return LPAREN; }
")"                        {  return RPAREN; }
\{                        {  return LBRACE; }
\}                        {  return RBRACE; }
"["                        {  return LBRACK; }
"]"                        {  return RBRACK; }
"="                        {  return ASSIGN; }

{RELOP}                    {  return RELOP; }
{BINOP}                    {  return BINOP; }

"//"[^\r\n]*               {return COMMENT; }

{letter}({letteranddigit})* {  return ID; }
0|[1-9][0-9]*               {  return NUM; }
(0|[1-9][0-9]*)b            {  return NUM_B; }
\"{stringchar}*\"            { return STRING;} 
\"{stringchar}*\\[^ntr\"\\0x]{stringchar}*\"    { return UNDEF_ESCAPE; }     
\"{stringchar}+               {return UNCLOSED_STRING;}



.                          { return UNKNOWN_CHAR; }

%%
