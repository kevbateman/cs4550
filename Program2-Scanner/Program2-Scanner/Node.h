#pragma once
#include "Symbol.h"
#include <string>
#include <vector>

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;

class Node {
public:
	virtual ~Node();
	virtual void Interpret() = 0;
};

class StartNode : public Node {
public:
	StartNode(ProgramNode * programnode);
	~StartNode();
	void Interpret();
private:
	ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
	ProgramNode(BlockNode * blocknode);
	~ProgramNode();
	void Interpret();
private:
	BlockNode * mBlockNode;
};

class BlockNode : public Node {
public:
	BlockNode(StatementGroupNode * statementgroupnode);
	~BlockNode();
	void Interpret();
private:
	StatementGroupNode * mStatementGroupNode;
};

class StatementGroupNode : public Node {
public:
	~StatementGroupNode();
	void AddStatement(StatementNode * statementnode);
	void Interpret();
private:
	std::vector < StatementNode * > mStatementNodes;
};

class StatementNode : public Node {};

class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode * idenifiernode);
	~DeclarationStatementNode();
	void Interpret();
private:
	IdentifierNode * mIdentifierNode;
};

class AssignmentStatementNode: public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode);
	~AssignmentStatementNode();
	void Interpret();
private:
	IdentifierNode * mIdentifierNode;
	ExpressionNode * mExpressionNode;
};

class CoutStatementNode: public StatementNode {
public:
	CoutStatementNode(ExpressionNode * expressionnode);
	~CoutStatementNode();
	void Interpret();
private:
	ExpressionNode * mExpressionNode;
};

class ExpressionNode {
public:
	virtual ~ExpressionNode();
	virtual int Evaluate() = 0;
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int value);
	~IntegerNode();
	int Evaluate();
private:
	int mValue;
};

class IdentifierNode : public ExpressionNode {
public:
	IdentifierNode(std::string label, SymbolTableClass *symboltable);
	~IdentifierNode();
	void DeclareVariable();
	void SetValue(int value);
	int GetIndex();
	int Evaluate();
private:
	std::string mLabel;
	SymbolTableClass * mSymbolTable;
};

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode * left, ExpressionNode * right);
	~BinaryOperatorNode();
	virtual int Evaluate() = 0;
protected:
	ExpressionNode * mLeft;
	ExpressionNode * mRight;
};

class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};
class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};
class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};
class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
};
