#include "Scanner.h"
#include "StateMachine.h"
#include <iostream>
#include <fstream>
#include <string>

ScannerClass::ScannerClass(std::string string_input) 
	: mLineNumber(1) {
	MSG("Initializing ScannerClass object");
	this->mFin.open(string_input);

	if (!this->mFin.is_open()) {
		std::cout << "ERROR: file failed to open";
		exit(0);
	}
}

TokenClass ScannerClass::GetNextToken() {
	StateMachineClass stateMachine;

	TokenType type;
	std::string lexeme;
	MachineState state = START_STATE;
	char c;
	do {
		c = this->mFin.get();
		if (c == '\n')
			this->mLineNumber++;
		if (state == START_STATE)
			lexeme.clear();
		state = stateMachine.UpdateState(c, type);
		lexeme += c;
	} while (state != CANTMOVE_STATE);
	
	lexeme.pop_back();
	if (c == '\n')
		this->mLineNumber--;
	this->mFin.unget();
	
	if (type == BAD_TOKEN) {
		if (lexeme.empty())
			lexeme = this->mFin.get();
		std::cout	<< "\tERROR\t<BAD_TOKEN>\n\t\tSTATE = "
					<< state << "\n\t\tLEXEME = " 
					<< lexeme << std::endl;
		exit(0);
	}
	TokenClass nextToken(type, lexeme);
	return nextToken;
}
int ScannerClass::GetLineNumber() {
	return this->mLineNumber;
}