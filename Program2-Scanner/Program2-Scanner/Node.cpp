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
void StartNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING STARTNODE");
	this->mProgramNode->Code(machinecode);
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
void ProgramNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING PROGRAMNODE");
	this->mBlockNode->Code(machinecode);
}
BlockNode::BlockNode(StatementGroupNode * statementgroupnode, SymbolTableClass * symboltable)
	: mStatementGroupNode(statementgroupnode), mSymbolTable(symboltable) {
}
BlockNode::~BlockNode() {
	MSG("DELETING BLOCKNODE");
	delete this->mStatementGroupNode; 
}
void BlockNode::Interpret() {
	MSG("INTERPRETING BLOCKNODE");
	mSymbolTable->PushScope();
	mStatementGroupNode->Interpret();
	mSymbolTable->PopScope();
}
void BlockNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING BLOCKNODE");
	mSymbolTable->PushScope();
	this->mStatementGroupNode->Code(machinecode);
	mSymbolTable->PopScope();
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
void StatementGroupNode::Code(InstructionsClass &machinecode) {
	MSG("CODING STATEMENTGROUPNODE");
	for (unsigned int i = 0; i < this->mStatementNodes.size(); i++) {
		this->mStatementNodes[i]->Code(machinecode);
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
void DeclarationStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING DECLARATIONSTATEMENTNODE");
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
void AssignmentStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING ASSIGNMENTSTATEMENTNODE");
	this->mExpressionNode->CodeEvaluate(machinecode);
	machinecode.PopAndStore(this->mIdentifierNode->GetIndex());
}

PlusAssignmentStatementNode::PlusAssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode)
	: AssignmentStatementNode(identifiernode, expressionnode) {
}
PlusAssignmentStatementNode::~PlusAssignmentStatementNode() {
	MSG("    DELETING PLUSASSIGNMENTSTATEMENTNODE");
	//delete this->mIdentifierNode;
	//delete this->mExpressionNode;
}
void PlusAssignmentStatementNode::Interpret() {
	MSG("    INTERPRETING PLUSASSIGNMENTSTATEMENTNODE");
	this->mIdentifierNode->SetValue(this->mIdentifierNode->Evaluate() + this->mExpressionNode->Evaluate());
}
void PlusAssignmentStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING PLUSASSIGNMENTSTATEMENTNODE");
	this->mIdentifierNode->CodeEvaluate(machinecode);
	this->mExpressionNode->CodeEvaluate(machinecode);
	machinecode.PopPopAddPush();
	machinecode.PopAndStore(this->mIdentifierNode->GetIndex());
}

MinusAssignmentStatementNode::MinusAssignmentStatementNode(IdentifierNode * identifiernode, ExpressionNode * expressionnode)
	: AssignmentStatementNode(identifiernode, expressionnode) {
}
MinusAssignmentStatementNode::~MinusAssignmentStatementNode() {
	MSG("    DELETING MINUSASSIGNMENTSTATEMENTNODE");
	//delete this->mIdentifierNode;
	//delete this->mExpressionNode;
}
void MinusAssignmentStatementNode::Interpret() {
	MSG("    INTERPRETING MINUSASSIGNMENTSTATEMENTNODE");
	this->mIdentifierNode->SetValue(this->mIdentifierNode->Evaluate() - this->mExpressionNode->Evaluate());
}
void MinusAssignmentStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING MINUSASSIGNMENTSTATEMENTNODE");
	this->mIdentifierNode->CodeEvaluate(machinecode);
	this->mExpressionNode->CodeEvaluate(machinecode);
	machinecode.PopPopSubPush();
	machinecode.PopAndStore(this->mIdentifierNode->GetIndex());
}

CoutStatementNode::CoutStatementNode() {}
CoutStatementNode::~CoutStatementNode() {
	MSG("DELETING COUTSTATEMENTNODE");
	for (unsigned int i = 0; i < this->mExpressionNodes.size(); i++) {
		delete this->mExpressionNodes[i];
	}
	//delete this->mExpressionNode;
}
void CoutStatementNode::AddExpression(ExpressionNode * expressionnode)
{
	this->mExpressionNodes.push_back(expressionnode);
}
void CoutStatementNode::Interpret() {
	MSG("    INTERPRETING COUTSTATEMENTNODE");
	for (unsigned int i = 0; i < this->mExpressionNodes.size(); i++) {
		if (this->mExpressionNodes[i]) {
			std::cout << this->mExpressionNodes[i]->Evaluate();
		}
		else {
			std::cout << std::endl;
		}
	}
	//std::cout << this->mExpressionNode->Evaluate() << std::endl;
}
void CoutStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING COUTSTATEMENTNODE");
	for (unsigned int i = 0; i < this->mExpressionNodes.size(); i++) {
		if (this->mExpressionNodes[i])
		{
			this->mExpressionNodes[i]->CodeEvaluate(machinecode);
			machinecode.PopAndWrite();
		}
		else
		{
			machinecode.WriteEndl();
		}
	}
	//this->mExpressionNode->CodeEvaluate(machinecode);
	//machinecode.PopAndWrite();
}
IfStatementNode::IfStatementNode(ExpressionNode * expressionnode, StatementNode * statementnode)
	: mExpressionNode(expressionnode), mStatementNode(statementnode) {
}
IfStatementNode::~IfStatementNode() {
	MSG("DELETING IFSTATEMENTNODE");
	delete this->mExpressionNode;
	delete this->mStatementNode;
}
void IfStatementNode::Interpret() {
	MSG("    INTERPRETING IFSTATEMENTNODE");
	if (this->mExpressionNode->Evaluate() != 0) {
		this->mStatementNode->Interpret();
	}
}
void IfStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING IFSTATEMENTNODE");
	this->mExpressionNode->CodeEvaluate(machinecode);
	unsigned char * jump_address = machinecode.SkipIfZeroStack();

	unsigned char * address1 = machinecode.GetAddress();
	this->mStatementNode->Code(machinecode);
	unsigned char * address2 = machinecode.GetAddress();

	machinecode.SetOffset(jump_address, address2 - address1);
}
WhileStatementNode::WhileStatementNode(ExpressionNode * expressionnode, StatementNode * statementnode)
	: mExpressionNode(expressionnode), mStatementNode(statementnode) {
}
WhileStatementNode::~WhileStatementNode() {
	MSG("DELETING WHILESTATEMENTNODE");
	delete this->mExpressionNode;
	delete this->mStatementNode;
}
void WhileStatementNode::Interpret() {
	MSG("    INTERPRETING WHILESTATEMENTNODE");
	while (this->mExpressionNode->Evaluate() != 0) {
		this->mStatementNode->Interpret();
	}
}
void WhileStatementNode::Code(InstructionsClass &machinecode) {
	MSG("    CODING WHILESTATEMENTNODE");
	unsigned char * address0 = machinecode.GetAddress();
	this->mExpressionNode->CodeEvaluate(machinecode);
	unsigned char * jump_address1 = machinecode.SkipIfZeroStack();

	unsigned char * address1 = machinecode.GetAddress();
	this->mStatementNode->Code(machinecode);
	unsigned char * jump_address2 = machinecode.Jump();
	unsigned char * address2 = machinecode.GetAddress();

	machinecode.SetOffset(jump_address1, address2 - address1);
	machinecode.SetOffset(jump_address2, address0 - address2);
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
void IntegerNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING INTEGERNODE");
	machinecode.PushValue(this->mValue);
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
void IdentifierNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING IDENTIFIERNODE");
	machinecode.PushVariable(this->mSymbolTable->GetIndex(this->mLabel));
}
UnaryOperatorNode::UnaryOperatorNode(ExpressionNode * right_in)
	: mRight(right_in) {
}
UnaryOperatorNode::~UnaryOperatorNode() {
	//MSG("DELETING UNARYOPERATORNODE");
	delete this->mRight;
}
NotNode::NotNode(ExpressionNode * right)
: UnaryOperatorNode(right) {
}
int NotNode::Evaluate() {
	MSG("\tEVALUATING NOTNODE");
	return (this->mRight->Evaluate() != 0) ? 0 : 1;
}
void NotNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING NOTNODE");
	exit(1);
}
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode * left_in, ExpressionNode * right_in)
	: mLeft(left_in), mRight(right_in) {
}
BinaryOperatorNode::~BinaryOperatorNode() {
	//MSG("DELETING BINARYOPERATORNODE");
	delete this->mLeft; delete this->mRight; 
}
OrNode::OrNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int OrNode::Evaluate() {
	MSG("\tEVALUATING ORNODE");
	return ((this->mLeft->Evaluate() != 0) || (this->mRight->Evaluate() != 0)) ? 1 : 0;
}
void OrNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING ORNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopOrPush();
}
AndNode::AndNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int AndNode::Evaluate() {
	MSG("\tEVALUATING ANDNODE");
	return ((this->mLeft->Evaluate() != 0) && (this->mRight->Evaluate() != 0)) ? 1 : 0;
}
void AndNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING ANDNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopAndPush();
}
PlusNode::PlusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int PlusNode::Evaluate() {
	MSG("\tEVALUATING PLUSNODE");
	return this->mLeft->Evaluate() + this->mRight->Evaluate();
}
void PlusNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING PLUSNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int MinusNode::Evaluate() {
	MSG("\tEVALUATING MINUSNODE");
	return this->mLeft->Evaluate() - this->mRight->Evaluate();
}
void MinusNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING MINUSNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int TimesNode::Evaluate() {
	MSG("\tEVALUATING TIMESNODE");
	return this->mLeft->Evaluate() * this->mRight->Evaluate();
}
void TimesNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING TIMENODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopMulPush();
}

DivideNode::DivideNode(ExpressionNode * left, ExpressionNode * right)
	: BinaryOperatorNode(left, right) {
}
int DivideNode::Evaluate() {
	MSG("\tEVALUATING DIVIDENODE");
	return this->mLeft->Evaluate() / this->mRight->Evaluate();
}
void DivideNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING DIVIDENODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopDivPush();
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
void LessNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING LESSNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopLessPush();
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
void LessEqualNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING LESSEQUALNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopLessEqualPush();
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
void GreaterNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING GREATERNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopGreaterPush();
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
void GreaterEqualNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING GREATEREQUALNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopGreaterEqualPush();
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
void EqualNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING EQUALNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopEqualPush();
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
void NotEqualNode::CodeEvaluate(InstructionsClass &machinecode) {
	MSG("\tCODING NOTEQUALNODE");
	mLeft->CodeEvaluate(machinecode);
	mRight->CodeEvaluate(machinecode);
	machinecode.PopPopNotEqualPush();
}

