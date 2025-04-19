#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;

void checkToken(int token);
void rebuildString();

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        checkToken(token);
    }
    return 0;
}


void checkToken(int token) {
    switch (token) {
        case VOID:
            output::printToken(yylineno,VOID,yytext);
            break;
        case INT:
            output::printToken(yylineno,INT,yytext);
            break;
        case BYTE:
            output::printToken(yylineno,BYTE,yytext);
            break;
        case BOOL:
            output::printToken(yylineno,BOOL,yytext);
            break;
        case AND:
            output::printToken(yylineno,AND,yytext);
            break;
        case OR:
            output::printToken(yylineno,OR,yytext);
            break;
        case NOT:
            output::printToken(yylineno,NOT,yytext);
            break;
        case TRUE:
           output::printToken(yylineno, TRUE, yytext);
            break;
        case FALSE:
            output::printToken(yylineno, FALSE, yytext);
            break;
        case RETURN:
            output::printToken(yylineno, RETURN, yytext);
            break;
        case IF:
            output::printToken(yylineno, IF, yytext);
            break;
        case ELSE:
            output::printToken(yylineno, ELSE, yytext);
            break;
        case WHILE:
            output::printToken(yylineno, WHILE, yytext);
            break;
        case BREAK:
            output::printToken(yylineno, BREAK, yytext);
            break;
        case CONTINUE:
            output::printToken(yylineno, CONTINUE, yytext);
            break;
        case SC:
            output::printToken(yylineno, SC, yytext);
            break;
        case COMMA:
            output::printToken(yylineno, COMMA, yytext); 
            break;
        case LPAREN:
            output::printToken(yylineno, LPAREN, yytext);
            break;
        case RPAREN:
            output::printToken(yylineno, RPAREN, yytext);
            break;
        case LBRACE:
            output::printToken(yylineno, LBRACE, yytext);
            break;
        case RBRACE:
            output::printToken(yylineno, RBRACE, yytext);
            break;
        case LBRACK:
            output::printToken(yylineno, LBRACK, yytext);
            break;
        case RBRACK:
            output::printToken(yylineno, RBRACK, yytext);
            break;
        case ASSIGN:
            output::printToken(yylineno, ASSIGN, yytext);
            break;
        case RELOP:
            output::printToken(yylineno, RELOP, yytext);
            break;
        case COMMENT:
            output::printToken(yylineno, COMMENT, yytext);
            break;
        case BINOP:
            output::printToken(yylineno, BINOP, yytext);
            break;
        case ID:
            output::printToken(yylineno, ID, yytext);
            break;
        case NUM:
            output::printToken(yylineno, NUM, yytext);
            break;
        case NUM_B:
            output::printToken(yylineno, NUM_B, yytext);
            break;
        case STRING:
        //output::printToken(yylineno,STRING,yytext);
            rebuildString();
            break;
        case UNCLOSED_STRING:
            output::errorUnclosedString();
            
            break;
        case UNDEF_ESCAPE:
            output::errorUndefinedEscape(yytext);//should i give it something else
          // yes you should :)
            break;
        case UNKNOWN_CHAR:
            //cout<<yytext<<std::endl;
            output::errorUnknownChar(yytext[0]);//not sure if thats enough
            break;
            
    }
}
void rebuildString() {
    std::string str(yytext);
    std::ostringstream out;
    
    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];
        char next = (i + 1 < str.size()) ? str[i + 1] : '\0';
        char next2 = (i + 2 < str.size()) ? str[i + 2] : '\0';
        char next3 = (i + 3 < str.size()) ? str[i + 3] : '\0';

        if (ch == '"') continue;  // Skip quotes

        else if (ch == '\\') {
            if (next == 'n')      { out << '\n'; i++; }
            else if (next == 't') { out << '\t'; i++; }
            else if (next == 'r') { /* skip \r */ i++; }
            else if (next == '0') { out << '\0'; i++; }
            else if (next == '"') { out << '"';  i++; }
            else if (next == '\\'){ out << '\\'; i++; }
            else if (next == 'x' && isxdigit(next2) && isxdigit(next3)) {
                std::stringstream ss;
                ss << std::hex << str.substr(i + 2, 2);
                int val;
                ss >> val;
                out << static_cast<char>(val);
                i += 3;
            }
            else {
                // Undefined escape, just print the raw backslash and next char
                out << '\\' << next;
                i++;
            }
        }
        else {
            out << ch;
        }
    }

    std::cout << yylineno << " STRING " << out.str() << std::endl;
}