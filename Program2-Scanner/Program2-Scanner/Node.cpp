#include "Node.h"
#include "Debug.h"

Node::~Node() {
}

StartNode::StartNode(ProgramNode * programnode) 
	: mProgramNode(programnode) {
}
StartNode::~StartNode() {
	MSG("DELETING STARTNODE");
	delete this->mProgramNode; 
}
void StartNode::Interpret() {
	MSG("INTERPRETING STARTNODE");
	mProgramNode->Interpret();
}

ProgramNode::ProgramNode(BlockNode * blocknode)
	: mBlockNode(blocknode) {
}
ProgramNode::~ProgramNode() {
	MSG("DELETING PROGRAMNODE");
	delete this->mBlockNode; 
}
void ProgramNode::Interpret() {
	MSG("INTERPRETING PROGRAMNODE");
	mBlockNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode * statementgroupnode)
	: mStatementGroupNode(statementgroupnode) {
}
BlockNode::~BlockNode() {
	MSG("DELETING BLOCKNODE");
	delete this->mStatementGroupNode; 
}
void BlockNode::Interpret() {
	MSG("INTERPRETING BLOCKNODE");
	mStatementGroupNode->Interpret();
}

StatementGroupNode::~StatementGroupNode() {
	MSG("DELETING STATEMENTGROUPNODE");
	for (unsigned int i = 0; i < this->mStatementNodes.size(); i++) {
		MSG("DELETING STATMENTNODE FROM STATEMENTGROUPNODE");
		delete this->mStatementNodes[i]; 
	} 
}
void StatementGroupNode::AddStatement(StatementNode * statementnode) {
	this->mStatementNodes.push_back(statementnode); 
}
void StatementGroupNode::Interpret() {
	MSG("INTERPRETING STATEMENTGROUPNODE");
	for (unsigned int i = 0; i < this->mStatementNodes.size(); i++) {
		this->mStatementNodes[i]->Interpret();
	}
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode * idenifiernode)
	: mIdentifierNode(idenifiernode) {
}
DeclarationStatementNode::~DeclarationStatementNode() {
	MSG("DELETING DECLARATIONNODE");
	delete this->mIdentifierNode; 
}
void DeclarationStatementNode::Interpret() {
	MSG("    INTERPRETING DECLARATIONSTATEMENTNODE");
	this->mIdentifierNode->DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode)
	: mIdentifierNode(identifiernode), mExpressionNode(expressionnode) {
}
AssignmentStatementNode::~AssignmentStatementNode() {
	MSG("DELETING ASSIGNMENTSTATEMENTNODE");
	delete this->mIdentifierNode; 
	delete this->mExpressionNode; 
}
void AssignmentStatementNode::Interpret() {
	MSG("    INTERPRETING ASSIGNMENTSTATEMENTNODE");
	this->mIdentifierNode->SetValue(this->mExpressionNode->Evaluate());
}

CoutStatementNode::CoutStatementNode(ExpressionNode * expressionnode)
	: mExpressionNode(expressionnode) {
}
CoutStatementNode::~CoutStatementNode() {
	MSG("DELETING COUTSTATEMENTNODE");
	delete this->mExpressionNode; 
}
void CoutStatementNode::Interpret() {
	MSG("    INTERPRETING COUTSTATEMENTNODE");
	std::cout << this->mExpressionNode->Evaluate() << std::endl;
}

ExpressionNode::~ExpressionNode() {
	//MSG("DELETING EXPRESSIONNODE"); 
}

IntegerNode::IntegerNode(int value)
	: mValue(value) {
}
IntegerNode::~IntegerNode() {
	MSG("DELETING INTEGERNODE");
}
int IntegerNode::Evaluate() {
	MSG("\tEVALUATING INTEGERNODE");
	return this->mValue; 
}

IdentifierNode::IdentifierNode(std::string label, SymbolTableClass * symboltable)
	: mLabel(label), mSymbolTable(symboltable) {
}
IdentifierNode::~IdentifierNode() {
	MSG("DELETING IDENTIFIERNODE WITH LABEL '" + this->mLabel + "'");
	this->mSymbolTable = NULL; 
}
void IdentifierNode::DeclareVariable() {
	this->mSymbolTable->AddEntry(this->mLabel); 
}
void IdentifierNode::SetValue(int value) {
	this->mSymbolTable->SetValue(this->mLabel, value); 
}
int IdentifierNode::GetIndex() {
	return this->mSymbolTable->GetIndex(this->mLabel); 
}
int IdentifierNode::Evaluate() {
	MSG("\tEVALUATING IDENTIFIERNODE");
	return this->mSymbolTable->GetValue(this->mLabel); 
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * left_in, ExpressionNode * right_in)
	: mLeft(left_in), mRight(right_in) {
}
BinaryOperatorNode::~BinaryOperatorNode() {
	//MSG("DELETING BINARYOPERATORNODE");
	delete this->mLeft; delete this->mRight; 
}

PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int PlusNode::Evaluate() {
	MSG("\tEVALUATING PLUSNODE");
	return this->mLeft->Evaluate() + this->mRight->Evaluate();
}

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int MinusNode::Evaluate() {
	MSG("\tEVALUATING MINUSNODE");
	return this->mLeft->Evaluate() - this->mRight->Evaluate();
}

TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int TimesNode::Evaluate() {
	MSG("\tEVALUATING TIMESNODE");
	return this->mLeft->Evaluate() * this->mRight->Evaluate();
}

DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int DivideNode::Evaluate() {
	MSG("\tEVALUATING DIVIDENODE");
	return this->mLeft->Evaluate() / this->mRight->Evaluate();
}

LessNode::LessNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int LessNode::Evaluate() {
	MSG("\tEVALUATING LESSNODE");
	if (this->mLeft->Evaluate() < this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

LessEqualNode::LessEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int LessEqualNode::Evaluate() {
	MSG("\tEVALUATING LESSEQUALNODE");
	if (this->mLeft->Evaluate() <= this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

GreaterNode::GreaterNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int GreaterNode::Evaluate() {
	MSG("\tEVALUATING GREATERNODE");
	if (this->mLeft->Evaluate() > this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int GreaterEqualNode::Evaluate() {
	MSG("\tEVALUATING GREATEREQUALNODE");
	if (this->mLeft->Evaluate() >= this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

EqualNode::EqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int EqualNode::Evaluate() {
	MSG("\tEVALUATING EQUALNODE");
	if (this->mLeft->Evaluate() == this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

NotEqualNode::NotEqualNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int NotEqualNode::Evaluate() {
	MSG("\tEVALUATING NOTEQUALNODE");
	if (this->mLeft->Evaluate() != this->mRight->Evaluate()) {
		return 1;
	}
	return 0;
}

