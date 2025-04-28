%{
#include "tokens.hpp"
#include "output.hpp"
#include <string>
    void dupString(const char* s);

std::string str_buffer;
%}

%option yylineno
%option noyywrap

%x string

whitespace     [\t\r\n ]
letter         [a-zA-Z]
digit          [0-9]
id             {letter}({letter}|{digit})*
num            0|[1-9]{digit}*
RELOP          (==|!=|>=|<=|>|<)
BINOP          (\+|\-|\*|/)
word           ([ !#-\[\]-~])

esc            (\\[\\nrt0\"]|\\x[2-6][0-9a-fA-F]|\\x7[0-9a-eA-E]|\\x0[AD9])
undefEsc        \\x[^\n\r\t\"]{1,2}


%%

"void"         { return VOID; }
"int"          { return INT; }
"byte"         { return BYTE; }
"bool"         { return BOOL; }
"and"          { return AND; }
"or"           { return OR; }
"not"          { return NOT; }
"true"         { return TRUE; }
"false"        { return FALSE; }
"return"       { return RETURN; }
"if"           { return IF; }
"else"         { return ELSE; }
"while"        { return WHILE; }
"break"        { return BREAK; }
"continue"     { return CONTINUE; }

";"            { return SC; }
","            { return COMMA; }
"("            { return LPAREN; }
")"            { return RPAREN; }
"{"            { return LBRACE; }
"}"            { return RBRACE; }
"["            { return LBRACK; }
"]"            { return RBRACK; }
"="            { return ASSIGN; }



{RELOP}        { return RELOP; }
(\+|-|\*|\/)   { return BINOP; }

"//"[^\r\n]*   { return COMMENT; }

{id}           { return ID; }
{num}b         { return NUM_B; }
{num}          { return NUM; }

\"                     { BEGIN(string); }

<string>{word}*        { dupString(yytext); }
<string>{[\t]}*         { dupString(yytext); }
<string>{esc}          { dupString(yytext);}
<string>{undefEsc}     { output::errorUndefinedEscape(yytext + 1); }
<string>\\.            { output::errorUndefinedEscape(yytext + 1); }
<string>\"             { BEGIN(INITIAL); return STRING;}
<string>[\n\r]         { output::errorUnclosedString(); BEGIN(INITIAL); }
<string><<EOF>>        { output::errorUnclosedString(); BEGIN(INITIAL); }

{whitespace}           ;
.                      { output::errorUnknownChar(*yytext); }

%%
