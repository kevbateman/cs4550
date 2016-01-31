#include "Token.h"

#include <iostream>
#include <string>

int main() {
	TokenType token_type = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass my_token(token_type, lexeme);
	std::cout << my_token << std::endl;
	return 0;
}