#include "Parser.h"
#include "Token.h"
#include "Node.h"

ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *symboltable)
	:mScanner(scanner), mSymbolTable(symboltable)
{
}
StartNode * ParserClass::Start()
{
	ProgramNode * pn = this->Program();
	this->Match(ENDFILE_TOKEN);
	StartNode * sn = new StartNode(pn);
	return sn;
}
ProgramNode * ParserClass::Program()
{
	this->Match(VOID_TOKEN);
	this->Match(MAIN_TOKEN);
	this->Match(LPAREN_TOKEN);
	this->Match(RPAREN_TOKEN);
	BlockNode * bn = this->Block();
	ProgramNode * pn = new ProgramNode(bn);
	return pn;
}
BlockNode * ParserClass::Block()
{
	this->Match(LCURLY_TOKEN);
	StatementGroupNode * sgn = this->StatementGroup();
	this->Match(RCURLY_TOKEN);
	BlockNode * bn = new BlockNode(sgn);
	return bn;
}
StatementGroupNode * ParserClass::StatementGroup()
{
	StatementGroupNode * sgn = new StatementGroupNode();
	bool loop = true;
	while (loop)
	{
		StatementNode * sn = this->Statement();
		if (sn == NULL)
		{
			loop = false;
		}
		else {
			sgn->AddStatement(sn);
		}
	}
	return sgn;
}
StatementNode * ParserClass::Statement() {
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	StatementNode * sn;
	switch (tt)
	{
	case INTEGER_TOKEN:
		this->Match(tt);
		sn = this->DeclarationStatement();
		this->Match(SEMICOLON_TOKEN);
		break;
	case IDENTIFIER_TOKEN:
		sn = this->AssignmentStatement();
		this->Match(SEMICOLON_TOKEN);
		break;
	case COUT_TOKEN:
		this->Match(tt);
		sn = this->CoutStatement();
		this->Match(SEMICOLON_TOKEN);
		break;
	case IF_TOKEN:
		this->Match(tt);
		sn = this->IfStatement();
		break;
	case WHILE_TOKEN:
		this->Match(tt);
		sn = this->WhileStatement();
		break;
	case LCURLY_TOKEN:
		sn = this->Block();
		break;
	default:
		return NULL;
	}
	return sn;
}
DeclarationStatementNode * ParserClass::DeclarationStatement()
{
	IdentifierNode * in = this->Identifier();
	DeclarationStatementNode * dsn = new DeclarationStatementNode(in);
	return dsn;
}
AssignmentStatementNode * ParserClass::AssignmentStatement()
{
	IdentifierNode * in = this->Identifier();
	this->Match(ASSIGNMENT_TOKEN);
	ExpressionNode * en = this->Expression();
	AssignmentStatementNode * asn = new AssignmentStatementNode(in,en);
	return asn;
}
CoutStatementNode * ParserClass::CoutStatement()
{
	this->Match(INSERTION_TOKEN);
	ExpressionNode * en = this->Expression();
	CoutStatementNode * csn = new CoutStatementNode(en);
	return csn;
}
IfStatementNode * ParserClass::IfStatement()
{
	this->Match(LPAREN_TOKEN);
	ExpressionNode * en = this->Expression();
	this->Match(RPAREN_TOKEN);
	StatementNode * sn = this->Statement();
	IfStatementNode * isn = new IfStatementNode(en, sn);
	return isn;
}
WhileStatementNode * ParserClass::WhileStatement()
{
	this->Match(LPAREN_TOKEN);
	ExpressionNode * en = this->Expression();
	this->Match(RPAREN_TOKEN); 
	StatementNode * sn = this->Statement();
	WhileStatementNode * wsn = new WhileStatementNode(en, sn);
	return wsn;
}
ExpressionNode * ParserClass::Expression()
{
	ExpressionNode * current = this->Side();
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN	|| tt == LESSEQUAL_TOKEN	||
		tt == GREATER_TOKEN || tt == GREATEREQUAL_TOKEN ||
		tt == EQUAL_TOKEN	|| tt == NOTEQUAL_TOKEN)
	{
		this->Match(tt);
		switch (tt)
		{
		case LESS_TOKEN:
			current = new LessNode(current, this->Side());
			break;
		case LESSEQUAL_TOKEN:
			current = new LessEqualNode(current, this->Side());
			break;
		case GREATER_TOKEN:
			current = new GreaterNode(current, this->Side());
			break;
		case GREATEREQUAL_TOKEN:
			current = new GreaterEqualNode(current, this->Side());
			break;
		case EQUAL_TOKEN:
			current = new EqualNode(current, this->Side());
			break;
		case NOTEQUAL_TOKEN:
			current = new NotEqualNode(current, this->Side());
			break;
		}
	}
	return current;
}
ExpressionNode * ParserClass::Side()
{
	ExpressionNode * current = this->Or();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case OR_TOKEN:
			this->Match(tt);
			current = new OrNode(current, this->Or());
			break;
		//case PLUS_TOKEN:
		//	this->Match(tt);
		//	current = new PlusNode(current, this->PlusMinus());
		//	break;
		//case MINUS_TOKEN:
		//	this->Match(tt);
		//	current = new MinusNode(current, this->PlusMinus());
		//	break;
		default:
			loop = false;
			break;
		}
	}
	return current;
}
ExpressionNode * ParserClass::Or()
{
	ExpressionNode * lhs = this->And();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case OR_TOKEN:
			this->Match(tt);
			lhs = new OrNode(lhs, this->And());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::And()
{
	ExpressionNode * lhs = this->PlusMinus();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case AND_TOKEN:
			this->Match(tt);
			lhs = new AndNode(lhs, this->PlusMinus());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::PlusMinus()
{
	ExpressionNode * lhs = this->TimesDivide();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case PLUS_TOKEN:
			this->Match(tt);
			lhs = new PlusNode(lhs, this->TimesDivide());
			break;
		case MINUS_TOKEN:
			this->Match(tt);
			lhs = new MinusNode(lhs, this->TimesDivide());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::TimesDivide()
{
	ExpressionNode * lhs = this->Factor();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case TIMES_TOKEN:
			this->Match(tt);
			lhs = new TimesNode(lhs, this->Factor());
			break;
		case DIVIDE_TOKEN:
			this->Match(tt);
			lhs = new DivideNode(lhs, this->Factor());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::Factor()
{
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	switch (tt)
	{
	case IDENTIFIER_TOKEN:
		return this->Identifier();
	case INTEGER_TOKEN:
		return this->Integer();
	default:
		if (tt == LPAREN_TOKEN)
		{
			this->Match(LPAREN_TOKEN);
			ExpressionNode * en = this->Expression();
			this->Match(RPAREN_TOKEN);
			return en;
		}
		std::cerr << "ERROR: Token type from FACTOR function is wrong: Must be IDENTIFIER_TOKEN, INTEGER_TOKEN, or LPAREN_TOKEN" << std::endl;
		std::cerr << "CURRENTLY IS:" << TokenClass::GetTokenTypeName(tt) << std::endl;
		return NULL;
	}
}
IdentifierNode * ParserClass::Identifier()
{
	TokenClass token = this->Match(IDENTIFIER_TOKEN);
	IdentifierNode * in = new IdentifierNode(token.GetLexeme(), this->mSymbolTable);
	return in;
}
IntegerNode * ParserClass::Integer()
{
	TokenClass token = this->Match(INTEGER_TOKEN);
	IntegerNode * in = new IntegerNode(std::atoi(token.GetLexeme().c_str()));
	return in;
}
// Verify that the next token in the input file is of the same type
// that the parser expects.
TokenClass ParserClass::Match(TokenType expectedType)
{
	TokenClass currentToken = this->mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType)
	{
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type " <<
			TokenClass::GetTokenTypeName(expectedType) <<
			", but got type " << currentToken.GetTokenTypeName() <<
			std::endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token Type: " << currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken; // the one we just processed
}