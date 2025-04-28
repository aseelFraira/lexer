#include "tokens.hpp"
#include "output.hpp"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
std::string curr = "";

void rebuildString();
void dupString(const char* s){
    curr += s;
}

int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        if(token == STRING){
            rebuildString();
            curr = "";
        }else {
            output::printToken(yylineno, token, yytext);
        }
    }
    return 0;
}

void rebuildString() {
    std::string str(curr);
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
            else if (next == 'r') { out <<'\r' ; i++; }
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

    output::printToken(yylineno, STRING, out.str().c_str());

}