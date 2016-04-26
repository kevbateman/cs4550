#pragma once
#include "Instructions.h"
#include "Symbol.h"
#include <string>
#include <vector>

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class UnaryOperatorNode;
class NotNode;
class BinaryOperatorNode;
class IfStatementNode;
class WhileStatementNode;
class PlusNode;
class PlusEqualsNode;
class OrNode;
class AndNode;

class Node {
public:
	virtual ~Node();
	virtual void Interpret() = 0;
	virtual void Code(InstructionsClass &machinecode) = 0;
};

class StartNode : public Node {
public:
	StartNode(ProgramNode * programnode);
	~StartNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	ProgramNode * mProgramNode;
};

class ProgramNode : public Node {
public:
	ProgramNode(BlockNode * blocknode);
	~ProgramNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	BlockNode * mBlockNode;
};

class StatementNode : public Node {};

class BlockNode : public StatementNode {
public:
	BlockNode(StatementGroupNode * statementgroupnode);
	~BlockNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	StatementGroupNode * mStatementGroupNode;
};

class StatementGroupNode : public Node {
public:
	~StatementGroupNode();
	void AddStatement(StatementNode * statementnode);
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	std::vector < StatementNode * > mStatementNodes;
};


class DeclarationStatementNode : public StatementNode {
public:
	DeclarationStatementNode(IdentifierNode * idenifiernode);
	~DeclarationStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	IdentifierNode * mIdentifierNode;
};

class AssignmentStatementNode: public StatementNode {
public:
	AssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode);
	~AssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
protected:
	IdentifierNode * mIdentifierNode;
	ExpressionNode * mExpressionNode;
};

class PlusAssignmentStatementNode : public AssignmentStatementNode {
public:
	PlusAssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode);
	~PlusAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
};

class MinusAssignmentStatementNode : public AssignmentStatementNode {
public:
	MinusAssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode);
	~MinusAssignmentStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
};

class CoutStatementNode : public StatementNode {
public:
	CoutStatementNode();
	~CoutStatementNode();
	void AddExpression(ExpressionNode * expressionnode);
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	std::vector<ExpressionNode *> mExpressionNodes;
	//ExpressionNode * mExpressionNode;
};

class IfStatementNode : public StatementNode {
public:
	IfStatementNode(ExpressionNode * expressionnode, StatementNode * statementnode);
	~IfStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class WhileStatementNode : public StatementNode {
public:
	WhileStatementNode(ExpressionNode * expressionnode, StatementNode * statementnode);
	~WhileStatementNode();
	void Interpret();
	void Code(InstructionsClass &machinecode);
private:
	ExpressionNode * mExpressionNode;
	StatementNode * mStatementNode;
};

class ExpressionNode {
public:
	virtual ~ExpressionNode();
	virtual int Evaluate() = 0;
	virtual void CodeEvaluate(InstructionsClass &machinecode) = 0;
};

class IntegerNode : public ExpressionNode {
public:
	IntegerNode(int value);
	~IntegerNode();
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
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
	void CodeEvaluate(InstructionsClass &machinecode);
private:
	std::string mLabel;
	SymbolTableClass * mSymbolTable;
};

class UnaryOperatorNode : public ExpressionNode {
public:
	UnaryOperatorNode(ExpressionNode * right);
	~UnaryOperatorNode();
	virtual int Evaluate() = 0;
	void CodeEvaluate(InstructionsClass &machinecode) = 0;
protected:
	ExpressionNode * mRight;
};

class NotNode : public UnaryOperatorNode {
public:
	NotNode(ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class BinaryOperatorNode : public ExpressionNode {
public:
	BinaryOperatorNode(ExpressionNode * left, ExpressionNode * right);
	~BinaryOperatorNode();
	virtual int Evaluate() = 0;
	void CodeEvaluate(InstructionsClass &machinecode) = 0;
protected:
	ExpressionNode * mLeft;
	ExpressionNode * mRight;
};

class OrNode : public BinaryOperatorNode {
public:
	OrNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
class AndNode : public BinaryOperatorNode {
public:
	AndNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
class PlusNode : public BinaryOperatorNode {
public:
	PlusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
class MinusNode : public BinaryOperatorNode {
public:
	MinusNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
class TimesNode : public BinaryOperatorNode {
public:
	TimesNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
class DivideNode : public BinaryOperatorNode {
public:
	DivideNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class LessNode : public BinaryOperatorNode {
public:
	LessNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class LessEqualNode : public BinaryOperatorNode {
public:
	LessEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class GreaterNode : public BinaryOperatorNode {
public:
	GreaterNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class GreaterEqualNode : public BinaryOperatorNode {
public:
	GreaterEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class EqualNode : public BinaryOperatorNode {
public:
	EqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};

class NotEqualNode : public BinaryOperatorNode {
public:
	NotEqualNode(ExpressionNode * left, ExpressionNode * right);
	int Evaluate();
	void CodeEvaluate(InstructionsClass &machinecode);
};
