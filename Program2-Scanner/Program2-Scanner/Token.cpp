#include "Token.h"

TokenClass::TokenClass() 
	: mType(IDENTIFIER_TOKEN),mLexeme("") {
	// empty
}
TokenClass::TokenClass(TokenType type, const std::string & lexeme)
	: mType(type), mLexeme(lexeme) {
	// empty 
}
void TokenClass::CheckReserved() {
	if (this->mLexeme == "void") {
		this->mType = VOID_TOKEN;
	}
	else if (this->mLexeme == "main") {
		this->mType = MAIN_TOKEN;
	}
	else if (this->mLexeme == "int") {
		this->mType = INT_TOKEN;
	}
	else if (this->mLexeme == "cout") {
		this->mType = COUT_TOKEN;
	}
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc)
{
	out << tc.GetTokenType() << ' ' << tc.GetTokenTypeName() << ' ' << tc.GetLexeme();
	return out;
}
