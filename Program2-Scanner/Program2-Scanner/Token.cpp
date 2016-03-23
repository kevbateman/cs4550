#include "Token.h"
#include <iomanip>

TokenClass::TokenClass() 
	: mType(IDENTIFIER_TOKEN),mLexeme("") {
	// empty
}

TokenClass::TokenClass(TokenType type, const std::string & lexeme)
	: mType(type), mLexeme(lexeme) {
	this->CheckReserved();
}

void TokenClass::CheckReserved() {
	if (this->mLexeme == "void") {
		this->mType = VOID_TOKEN;
	}
	else if (this->mLexeme == "main") {
		this->mType = MAIN_TOKEN;
	}
	else if (this->mLexeme == "int") {
		this->mType = INTEGER_TOKEN;
	}
	else if (this->mLexeme == "cout") {
		this->mType = COUT_TOKEN;
	}
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc)
{
	out << std::setw(4) << std::left << tc.GetTokenType() << " | " 
		<< std::setw(10) << std::left << tc.GetTokenTypeName() << " | " 
		<< std::setw(10) << std::left << tc.GetLexeme();
	return out;
}
