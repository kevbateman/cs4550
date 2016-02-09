#pragma once
#include "Debug.h"
#include "Token.h"
#include <fstream>

class ScannerClass {
public:
	ScannerClass(std::string string_input);
	TokenClass GetNextToken();
	int GetLineNumber();
private:
	std::ifstream mFin;
	int mLineNumber;
};