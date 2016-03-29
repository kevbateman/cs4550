#include "Token.h"
#include "Scanner.h"
#include "Debug.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

#include <iostream>
#include <iomanip>
#include <string>

int main() {
	MSG("STARTING MAIN FUNCTION");

	// SCANNERCLASS TESTCODE
	ScannerClass my_scanner("input.txt");

	TokenClass my_token;

	do {
	my_token = my_scanner.GetNextToken();
	std::cout << std::setw(3) << my_scanner.GetLineNumber() << std::setw(3) << ' ' << my_token << std::endl;
	} while (my_token.GetTokenType() != ENDFILE_TOKEN);



	// SYMBOLTABLECLASS TESTCODE
	/*SymbolTableClass table;
	MSG("Adding 'FIRST'")
	table.AddEntry("FIRST");

	MSG("Adding 'SECOND'")
	table.AddEntry("SECOND");

	MSG("Adding 'THIRD'")
	table.AddEntry("THIRD");

	//MSG("ADDING 'FIRST'");
	//table.AddEntry("FIRST");

	MSG("Checking if 'SECOND' exists:");
	bool second_exists = table.Exists("SECOND");
	if (second_exists) {
	MSG("true");
	}
	else {
	MSG("false");
	}

	MSG("Getting number of added variables:");
	int var_count = table.GetCount();
	MSG(var_count);

	MSG("Getting index of 'SECOND':");
	int second_index = table.GetIndex("SECOND");
	MSG(second_index);

	MSG("Getting index of 'FOURTH':");
	int fourth_index = table.GetIndex("FOURTH");
	MSG(fourth_index);

	MSG("Setting 'FIRST' value to 4");
	table.SetValue("FIRST", 4);

	//MSG("Setting 'FOURTH' value to 1")
	//table.SetValue("FOURTH", 1);

	MSG("Getting 'FIRST' value:");
	int first_value = table.GetValue("FIRST");
	MSG(first_value);

	MSG("Getting 'SECOND' value:");
	int second_value = table.GetValue("SECOND");
	MSG(second_value);*/


	// NODE CLASSES TEST CODE
	//{
	//	int x;
	//	x = 5;
	//	cout << x + 3;
	//}
	/*SymbolTableClass symboltable = SymbolTableClass();

	IntegerNode *integern1					= new IntegerNode(3);
	IdentifierNode *identifiern1			= new IdentifierNode("x", &symboltable);
	PlusNode *plusn							= new PlusNode(identifiern1, integern1);
	CoutStatementNode *coutstatementn		= new CoutStatementNode(plusn);

	IntegerNode *integern2					= new IntegerNode(5);
	IdentifierNode *identifiern2			= new IdentifierNode("x", &symboltable);
	AssignmentStatementNode *assignmentn	= new AssignmentStatementNode(identifiern2, integern2);

	IdentifierNode *identifiern3			= new IdentifierNode("x", &symboltable);
	DeclarationStatementNode *declarationn	= new DeclarationStatementNode(identifiern3);

	StatementGroupNode *statementgroupn		= new StatementGroupNode();
	statementgroupn->AddStatement(coutstatementn);
	statementgroupn->AddStatement(assignmentn);
	statementgroupn->AddStatement(declarationn);

	BlockNode *blockn						= new BlockNode(statementgroupn);

	ProgramNode *programn					= new ProgramNode(blockn);

	StartNode *startn						= new StartNode(programn);

	delete startn;*/


	// EXPRESSION CLASSES TEST CODE
	//{
	//	Rate*3+(5-3+x)/10 <= x*(3+x*(2+x))
	//}


	// PARSER TEST CODE
	SymbolTableClass symboltable = SymbolTableClass();
	ScannerClass scanner("input.txt");
	ParserClass parser(&scanner, &symboltable);
	StartNode * sn = parser.Start();
	sn->Interpret();
	delete sn;

	return 0;
}