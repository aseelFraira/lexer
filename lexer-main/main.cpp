#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
void printGivenToken();
void checkToken(int token);
void printGivenToken(std::string name);
int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        checkToken(token);
    }
    return 0;
}
void printGivenToken(std::string name){
    cout << yylineno << " " << name << " " << yytext << endl;
}

void checkToken(int token) {
    switch (token) {
        case VOID:
            printGivenToken("VOID");
            break;
        case INT:
            printGivenToken("INT");
            break;
        case BYTE:
            printGivenToken("BYTE");
            break;
        case BOOL:
            printGivenToken("BOOL");
            break;
        case AND:
            printGivenToken("AND");
            break;
        case OR:
            printGivenToken("OR");
            break;
        case NOT:
            printGivenToken("NOT");
            break;
        case TRUE:
            printGivenToken("TRUE");
            break;
        case FALSE:
            printGivenToken("FALSE");
            break;
        case RETURN:
            printGivenToken("RETURN");
            break;
        case IF:
            printGivenToken("IF");
            break;
        case ELSE:
            printGivenToken("ELSE");
            break;
        case WHILE:
            printGivenToken("WHILE");
            break;
        case BREAK:
            printGivenToken("BREAK");
            break;
        case CONTINUE:
            printGivenToken("CONTINUE");
            break;
        case SC:
            printGivenToken("SC");
            break;
        case COMMA:
            printGivenToken("COMMA");
            break;
        case LPAREN:
            printGivenToken("LPAREN");
            break;
        case RPAREN:
            printGivenToken("RPAREN");
            break;
        case LBRACE:
            printGivenToken("LBRACE");
            break;
        case RBRACE:
            printGivenToken("RBRACE");
            break;
        case ASSIGN:
            printGivenToken("ASSIGN");
            break;
        case RELOP:
            printGivenToken("RELOP");
            break;
        case COMMENT:
            cout << yylineno << " COMMENT //" << endl;
            break;
        case BINOP:
            printGivenToken("BINOP");
            break;
        case ID:
            printGivenToken("ID");
            break;
        case NUM:
            printGivenToken("NUM");
            break;
            case NUM_B:
            printGivenToken("NUM_B");
            break;
        case STRING:
            printString();
            break;
        case UNCLOSED_STRING:
            output::errorUnclosedString();
            exit(0);
            break;
        case UNDEF_ESCAPE:
            output::errorUndefinedEscape(yytext);//should i give it something else
           exit(0);
            break;
        case UNKNOWN_CHAR:
            output::errorUnknownChar((char)yytext);
            exit(0);
    }
}
void printString(){//chack ig this works??
    std::string str(yytext);
    cout << yylineno << " STRING " ;
    for(int i = 0; i < str.size(); i++){
        char ch = str[i];
        char next_ch = str[i + 1];
        if(ch == '"') continue;
        else if(ch == '\\' && next_ch == 'x'){
            std::stringstream ss;
            ss << std::hex << str.substr(i+2, 2);
            int x;
            ss >> x;
            cout << char(x);
            i += 3;
        } else if(ch == '\\' && next_ch == 'n'){
            cout << '\n';
            i++;
        } else if(ch == '\\' && next_ch == 'r') {
            cout << '\r';
            i++;
        } else if(ch == '\\' && next_ch == 't'){
            cout << '\t';
            i++;
        }
        else if(ch == '\\' && next_ch == '\"'){
            cout << '\"';
            i++;
        } else if(ch == '\\'){
            cout << '\\';
            i++;
        } else {
            cout << ch;
        }
    }
    cout << endl;
}