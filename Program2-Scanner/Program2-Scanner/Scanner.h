#pragma once
#include "Debug.h"
#include "Token.h"
#include "StateMachine.h"
#include <fstream>

class ScannerClass {
public:
	ScannerClass(std::string string_input);
	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int GetLineNumber();
private:
	std::ifstream mFin;
	int mLineNumber;
	StateMachineClass mStateMachine;
};