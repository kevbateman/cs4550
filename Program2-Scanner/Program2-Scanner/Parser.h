#pragma once
#include "Scanner.h"
#include "Token.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass
{
public:
	ParserClass(ScannerClass *scanner, SymbolTableClass *symboltable);
	StartNode * Start();
	ProgramNode * Program();
	BlockNode * Block();
	StatementGroupNode * StatementGroup();
	StatementNode * Statement();
	DeclarationStatementNode * DeclarationStatement();
	AssignmentStatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	ExpressionNode * Expression();
	ExpressionNode * Side();
	ExpressionNode * PlusMinus();
	ExpressionNode * TimesDivide();
	ExpressionNode * Factor();
	//ExpressionNode * FactorTail();
	IdentifierNode * Identifier();
	IntegerNode * Integer();
	TokenClass Match(TokenType expectedType);
private:
	ScannerClass *mScanner;
	SymbolTableClass *mSymbolTable;
};