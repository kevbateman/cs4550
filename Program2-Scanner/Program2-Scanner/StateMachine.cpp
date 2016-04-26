#include "StateMachine.h"
#include <iostream>

StateMachineClass::StateMachineClass()
	: mCurrentState(START_STATE) {
	MSG("INITIALIZING STATEMACHINECLASS");
	// First, initialize all the mLegalMoves to CANTMOVE_STATE
	// Then, reset the mLegalMoves that are legitimate
	unsigned int i;
	for (i = 0; i < LAST_STATE; i++) {
		for (unsigned int j = 0; j < LAST_CHAR; j++) {
			this->mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	// Start states
	this->mLegalMoves[START_STATE][LETTER_CHAR]			= IDENTIFIER_STATE;
	this->mLegalMoves[START_STATE][DIGIT_CHAR]			= INTEGER_STATE;
	this->mLegalMoves[START_STATE][WHITESPACE_CHAR]		= START_STATE;
	this->mLegalMoves[START_STATE][NEWLINE_CHAR]		= START_STATE;
	this->mLegalMoves[START_STATE][ENDFILE_CHAR]		= ENDFILE_STATE;
	this->mLegalMoves[START_STATE][UNDERBAR_CHAR]		= IDENTIFIER_STATE;
	this->mLegalMoves[START_STATE][LESS_CHAR]			= LESS_STATE;
	this->mLegalMoves[START_STATE][GREATER_CHAR]		= GREATER_STATE;
	this->mLegalMoves[START_STATE][EQUAL_CHAR]			= ASSIGNMENT_STATE;
	this->mLegalMoves[START_STATE][SEMICOLON_CHAR]		= SEMICOLON_STATE;
	this->mLegalMoves[START_STATE][DOT_CHAR]			= INTEGER_STATE;
	this->mLegalMoves[START_STATE][LPAREN_CHAR]			= LPAREN_STATE;
	this->mLegalMoves[START_STATE][RPAREN_CHAR]			= RPAREN_STATE;
	this->mLegalMoves[START_STATE][LCURLY_CHAR]			= LCURLY_STATE;
	this->mLegalMoves[START_STATE][RCURLY_CHAR]			= RCURLY_STATE;
	this->mLegalMoves[START_STATE][MINUS_CHAR]			= MINUS_STATE;
	this->mLegalMoves[START_STATE][PLUS_CHAR]			= PLUS_STATE;
	this->mLegalMoves[START_STATE][TIMES_CHAR]			= TIMES_STATE;
	this->mLegalMoves[START_STATE][DIVIDE_CHAR]			= DIVIDE_STATE;
	this->mLegalMoves[START_STATE][NOT_CHAR]			= NOT_STATE;
	this->mLegalMoves[START_STATE][VBAR_CHAR]			= VBAR_STATE;
	this->mLegalMoves[START_STATE][AMPERSAND_CHAR]		= AMPERSAND_STATE;

	// Identifier states
	this->mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]		= IDENTIFIER_STATE;
	this->mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]	= IDENTIFIER_STATE;
	this->mLegalMoves[IDENTIFIER_STATE][UNDERBAR_CHAR]	= IDENTIFIER_STATE;

	// Integer states
	this->mLegalMoves[INTEGER_STATE][DIGIT_CHAR]		= INTEGER_STATE;
	this->mLegalMoves[INTEGER_STATE][LETTER_CHAR]		= PURGATORY_STATE;

	// Less states
	this->mLegalMoves[LESS_STATE][LESS_CHAR]			= INSERTION_STATE;
	this->mLegalMoves[LESS_STATE][EQUAL_CHAR]			= LESSEQUAL_STATE;

	// Greater states
	this->mLegalMoves[GREATER_STATE][EQUAL_CHAR]		= GREATEREQUAL_STATE;

	// Divide states
	this->mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR]		= LINECOMMENT_STATE;
	this->mLegalMoves[DIVIDE_STATE][TIMES_CHAR]			= LBLOCKCOMMENT_STATE;


	// Line comment states
	for (int i = 0; i < LAST_CHAR; i++)
		this->mLegalMoves[LINECOMMENT_STATE][i]			= LINECOMMENT_STATE;
	this->mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR]	= START_STATE;
	this->mLegalMoves[LINECOMMENT_STATE][ENDFILE_CHAR]	= ENDFILE_STATE;

	// Left block comment states
	for (int i = 0; i < LAST_CHAR; i++)
		this->mLegalMoves[LBLOCKCOMMENT_STATE][i]		= LBLOCKCOMMENT_STATE;
	this->mLegalMoves[LBLOCKCOMMENT_STATE][TIMES_CHAR]	= RBLOCKCOMMENT_STATE;

	// Right block comment states
	for (int i = 0; i < LAST_CHAR; i++)
		this->mLegalMoves[RBLOCKCOMMENT_STATE][i]		= LBLOCKCOMMENT_STATE;
	this->mLegalMoves[RBLOCKCOMMENT_STATE][TIMES_CHAR]	= RBLOCKCOMMENT_STATE;
	this->mLegalMoves[RBLOCKCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;
	
	// && and || states
	this->mLegalMoves[VBAR_STATE][VBAR_CHAR]			= OR_STATE;
	this->mLegalMoves[AMPERSAND_STATE][AMPERSAND_CHAR]	= AND_STATE;

	// != states
	this->mLegalMoves[NOT_STATE][EQUAL_CHAR]			= NOTEQUAL_STATE;

	// + and - states
	this->mLegalMoves[PLUS_STATE][EQUAL_CHAR]			= PLUSASSIGNMENT_STATE;
	this->mLegalMoves[MINUS_STATE][EQUAL_CHAR]			= MINUSASSIGNMENT_STATE;

	// First, initialize all states to correspond to the BAD token type.
	// Then, reset the end states to correspond to the correct token types.
	for (i = 0; i<LAST_STATE; i++) {
		this->mCorrespondingTokenTypes[i]					= BAD_TOKEN;
	}
	this->mCorrespondingTokenTypes[IDENTIFIER_STATE]		= IDENTIFIER_TOKEN;
	this->mCorrespondingTokenTypes[INTEGER_STATE]			= INTEGER_TOKEN;
	this->mCorrespondingTokenTypes[ENDFILE_STATE]			= ENDFILE_TOKEN;
	this->mCorrespondingTokenTypes[LESS_STATE]				= LESS_TOKEN;
	this->mCorrespondingTokenTypes[GREATER_STATE]			= GREATER_TOKEN;
	this->mCorrespondingTokenTypes[ASSIGNMENT_STATE]		= ASSIGNMENT_TOKEN;
	this->mCorrespondingTokenTypes[SEMICOLON_STATE]			= SEMICOLON_TOKEN;
	this->mCorrespondingTokenTypes[LPAREN_STATE]			= LPAREN_TOKEN;
	this->mCorrespondingTokenTypes[RPAREN_STATE]			= RPAREN_TOKEN;
	this->mCorrespondingTokenTypes[LCURLY_STATE]			= LCURLY_TOKEN;
	this->mCorrespondingTokenTypes[RCURLY_STATE]			= RCURLY_TOKEN;
	this->mCorrespondingTokenTypes[MINUS_STATE]				= MINUS_TOKEN;
	this->mCorrespondingTokenTypes[PLUS_STATE]				= PLUS_TOKEN;
	this->mCorrespondingTokenTypes[TIMES_STATE]				= TIMES_TOKEN;
	this->mCorrespondingTokenTypes[DIVIDE_STATE]			= DIVIDE_TOKEN;
	this->mCorrespondingTokenTypes[LESSEQUAL_STATE]			= LESSEQUAL_TOKEN;
	this->mCorrespondingTokenTypes[GREATEREQUAL_STATE]		= GREATEREQUAL_TOKEN;
	this->mCorrespondingTokenTypes[NOTEQUAL_STATE]			= NOTEQUAL_TOKEN;
	this->mCorrespondingTokenTypes[INSERTION_STATE]			= INSERTION_TOKEN;
	this->mCorrespondingTokenTypes[OR_STATE]				= OR_TOKEN;
	this->mCorrespondingTokenTypes[AND_STATE]				= AND_TOKEN;
	this->mCorrespondingTokenTypes[NOT_STATE]				= NOT_TOKEN;
	this->mCorrespondingTokenTypes[PLUSASSIGNMENT_STATE]	= PLUSASSIGNMENT_TOKEN;
	this->mCorrespondingTokenTypes[MINUSASSIGNMENT_STATE]	= MINUSASSIGNMENT_TOKEN;
}

MachineState StateMachineClass::UpdateState(
		char currentCharacter, 
		TokenType& correspondingTokenType) {
	// convert the input character into an input character type 
	CharacterType charType = BAD_CHAR;
	if (isalpha(currentCharacter)) {
		charType = LETTER_CHAR;
	}
	if (isdigit(currentCharacter)) {
		charType = DIGIT_CHAR;
	}
	if (isspace(currentCharacter) && currentCharacter != '\n') {
		charType = WHITESPACE_CHAR;
	}
	if (currentCharacter == EOF) {
		charType = ENDFILE_CHAR;
	}
	if (currentCharacter == '_') {
		charType = PLUS_CHAR;
	}
	if (currentCharacter == '<') {
		charType = LESS_CHAR;
	}
	if (currentCharacter == '>') {
		charType = GREATER_CHAR;
	}
	if (currentCharacter == '=') {
		charType = EQUAL_CHAR;
	}
	if (currentCharacter == ';') {
		charType = SEMICOLON_CHAR;
	}
	if (currentCharacter == '.') {
		charType = DOT_CHAR;
	}
	if (currentCharacter == '(') {
		charType = LPAREN_CHAR;
	}
	if (currentCharacter == ')') {
		charType = RPAREN_CHAR;
	}
	if (currentCharacter == '{') {
		charType = LCURLY_CHAR;
	}
	if (currentCharacter == '}') {
		charType = RCURLY_CHAR;
	}
	if (currentCharacter == '-') {
		charType = MINUS_CHAR;
	}
	if (currentCharacter == '+') {
		charType = PLUS_CHAR;
	}
	if (currentCharacter == '*') {
		charType = TIMES_CHAR;
	}
	if (currentCharacter == '/') {
		charType = DIVIDE_CHAR;
	}
	if (currentCharacter == '!') {
		charType = NOT_CHAR;
	}
	if (currentCharacter == '\n') {
		charType = NEWLINE_CHAR;
	}
	if (currentCharacter == '|') {
		charType = VBAR_CHAR;
	}
	if (currentCharacter == '&') {
		charType = AMPERSAND_CHAR;
	}

	correspondingTokenType = this->mCorrespondingTokenTypes[this->mCurrentState];
	this->mCurrentState = this->mLegalMoves[this->mCurrentState][charType];
	//std::cout << "tokentype = " << correspondingTokenType << std::endl;
	//std::cout << "mCurrentState = " << this->mCurrentState << std::endl;
	return this->mCurrentState;
}

void StateMachineClass::ResetState() {
	this->mCurrentState = START_STATE;
}

MachineState StateMachineClass::GetCurrentState() {
	return this->mCurrentState;
}