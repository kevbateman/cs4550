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
	BlockNode * bn = new BlockNode(sgn, mSymbolTable);
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
	
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	AssignmentStatementNode * asn;
	ExpressionNode * en;
	switch (tt)
	{
	case ASSIGNMENT_TOKEN:
		this->Match(ASSIGNMENT_TOKEN);
		en = this->Expression();
		asn = new AssignmentStatementNode(in, en);
		break;
	case PLUSASSIGNMENT_TOKEN:
		this->Match(PLUSASSIGNMENT_TOKEN);
		en = this->Expression();
		asn = new PlusAssignmentStatementNode(in, en);
		break;
	case MINUSASSIGNMENT_TOKEN:
		this->Match(MINUSASSIGNMENT_TOKEN);
		en = this->Expression();
		asn = new MinusAssignmentStatementNode(in, en);
		break;
	default:
		return NULL;
	}
	return asn;
}
CoutStatementNode * ParserClass::CoutStatement()
{
	CoutStatementNode * csn = new CoutStatementNode();
	this->Match(INSERTION_TOKEN);
	
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	switch (tt)
	{
	case ENDL_TOKEN:
		this->Match(ENDL_TOKEN);
		csn->AddExpression(NULL);
		break;
	default:
		csn->AddExpression(this->Expression());
		break;
	}

	while (true)
	{
		tt = this->mScanner->PeekNextToken().GetTokenType();

		if (tt != INSERTION_TOKEN) break;

		this->Match(INSERTION_TOKEN);

		tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case ENDL_TOKEN:
			this->Match(ENDL_TOKEN);
			csn->AddExpression(NULL);
			break;
		default:
			csn->AddExpression(this->Expression());
			break;
		}
	}
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
	ExpressionNode * current = this->Or();
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	if (tt == OR_TOKEN) {
		this->Match(tt);
		current = new OrNode(current, this->Or());
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
	ExpressionNode * lhs = this->Comparison();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case AND_TOKEN:
			this->Match(tt);
			lhs = new AndNode(lhs, this->Comparison());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::Comparison()
{
	ExpressionNode * lhs = this->PlusMinus();
	bool loop = true;
	while (loop) {
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();	
		switch (tt)
		{
		case LESS_TOKEN:
			this->Match(tt);
			lhs = new LessNode(lhs, this->PlusMinus());
			break;
		case LESSEQUAL_TOKEN:
			this->Match(tt);
			lhs = new LessEqualNode(lhs, this->PlusMinus());
			break;
		case GREATER_TOKEN:
			this->Match(tt);
			lhs = new GreaterNode(lhs, this->PlusMinus());
			break;
		case GREATEREQUAL_TOKEN:
			this->Match(tt);
			lhs = new GreaterEqualNode(lhs, this->PlusMinus());
			break;
		case EQUAL_TOKEN:
			this->Match(tt);
			lhs = new EqualNode(lhs, this->PlusMinus());
			break;
		case NOTEQUAL_TOKEN:
			this->Match(tt);
			lhs = new NotEqualNode(lhs, this->PlusMinus());
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
	ExpressionNode * lhs = this->Not();
	bool loop = true;
	while (loop)
	{
		TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
		switch (tt)
		{
		case TIMES_TOKEN:
			this->Match(tt);
			lhs = new TimesNode(lhs, this->Not());
			break;
		case DIVIDE_TOKEN:
			this->Match(tt);
			lhs = new DivideNode(lhs, this->Not());
			break;
		default:
			loop = false;
			break;
		}
	}
	return lhs;
}
ExpressionNode * ParserClass::Not()
{
	TokenType tt = this->mScanner->PeekNextToken().GetTokenType();
	switch (tt)
	{
	case NOT_TOKEN:
		this->Match(tt);
		return new NotNode(this->Not());
	default:
		return this->Factor();
	}
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