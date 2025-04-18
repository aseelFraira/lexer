#ifndef TOKENS_HPP
#define TOKENS_HPP
#define STRSIZE 1024
enum tokentype {
    VOID = 1,
    INT,
    BYTE,
    BOOL,
    AND,
    OR,
    NOT,
    TRUE,
    FALSE,
    RETURN,
    IF,
    ELSE,
    WHILE,
    BREAK,
    CONTINUE,
    SC,
    COMMA,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    LBRACK,
    RBRACK,
    ASSIGN,
    RELOP,
    BINOP,
    COMMENT,
    ID,
    NUM,
    NUM_B,
    STRING,
    UNCLOSED_STRING,
    UNKNOWN_CHAR,
    UNDEF_ESCAPE
};

extern int yylineno;
extern char *yytext;
extern int yyleng;

extern int yylex();
  extern char *command_line[STRSIZE];
#endif //TOKENS_HPP
