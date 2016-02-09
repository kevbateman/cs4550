#include "Token.h"
#include "Scanner.h"
#include "Debug.h"

#include <iostream>
#include <iomanip>
#include <string>

int main() {
	MSG("STARTING MAIN FUNCTION");
	ScannerClass my_scanner("input.txt");

	TokenClass my_token;

	do {
		my_token = my_scanner.GetNextToken();
		std::cout << my_scanner.GetLineNumber() << std::setw(3) << ' ' << my_token << std::endl;
	} while (my_token.GetTokenType() != ENDFILE_TOKEN);

	return 0;
}