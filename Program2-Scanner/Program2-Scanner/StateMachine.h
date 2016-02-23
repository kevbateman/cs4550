#pragma once
#include "Debug.h"
#include "Token.h"

enum MachineState {
	START_STATE, CANTMOVE_STATE, IDENTIFIER_STATE, INTEGER_STATE,
	ENDFILE_STATE, LESS_STATE, GREATER_STATE, ASSIGNMENT_STATE, SEMICOLON_STATE,
	LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	MINUS_STATE, PLUS_STATE, TIMES_STATE, DIVIDE_STATE,
	LESSEQUAL_STATE, GREATEREQUAL_STATE, NOTEQUAL_STATE,
	INSERTION_STATE, PURGATORY_STATE,
	LINECOMMENT_STATE, LBLOCKCOMMENT_STATE, RBLOCKCOMMENT_STATE,
	LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, BAD_CHAR, ENDFILE_CHAR, UNDERBAR_CHAR,
	LESS_CHAR, GREATER_CHAR, EQUAL_CHAR, SEMICOLON_CHAR, DOT_CHAR,
	LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR,
	MINUS_CHAR, PLUS_CHAR, TIMES_CHAR, DIVIDE_CHAR, NOT_CHAR, NEWLINE_CHAR,
	LAST_CHAR
};

class StateMachineClass {
public:
	StateMachineClass();
	MachineState UpdateState(
		char currentCharacter, 
		TokenType& correspondingTokenType);
	void ResetState();
private:
	MachineState mCurrentState;

	// The matrix of legal moves:
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

	// Which end-machine-states correspond to which token types.
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenTypes[LAST_STATE];
};