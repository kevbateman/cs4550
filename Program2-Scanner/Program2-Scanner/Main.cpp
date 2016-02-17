#include "Token.h"
#include "Scanner.h"
#include "Debug.h"
#include "Symbol.h"

#include <iostream>
#include <iomanip>
#include <string>

int main() {
	MSG("STARTING MAIN FUNCTION");
	ScannerClass my_scanner("input.txt");

	TokenClass my_token;

	do {
		my_token = my_scanner.GetNextToken();
		std::cout << my_scanner.GetLineNumber() << std::setw(3) << ' ' << my_token << std::endl;
	} while (my_token.GetTokenType() != ENDFILE_TOKEN);

	//SymbolTableClass table;
	//MSG("Adding 'FIRST'")
	//table.AddEntry("FIRST");

	//MSG("Adding 'SECOND'")
	//table.AddEntry("SECOND");

	//MSG("Adding 'THIRD'")
	//table.AddEntry("THIRD");

	////MSG("ADDING 'FIRST'");
	////table.AddEntry("FIRST");

	//MSG("Checking if 'SECOND' exists:");
	//bool second_exists = table.Exists("SECOND");
	//if (second_exists) {
	//	MSG("true");
	//}
	//else {
	//	MSG("false");
	//}

	//MSG("Getting number of added variables:");
	//int var_count = table.GetCount();
	//MSG(var_count);
	//
	//MSG("Getting index of 'SECOND':");
	//int second_index = table.GetIndex("SECOND");
	//MSG(second_index);

	//MSG("Getting index of 'FOURTH':");
	//int fourth_index = table.GetIndex("FOURTH");
	//MSG(fourth_index);

	//MSG("Setting 'FIRST' value to 4");
	//table.SetValue("FIRST", 4);

	////MSG("Setting 'FOURTH' value to 1")
	////table.SetValue("FOURTH", 1);

	//MSG("Getting 'FIRST' value:");
	//int first_value = table.GetValue("FIRST");
	//MSG(first_value);

	//MSG("Getting 'SECOND' value:");
	//int second_value = table.GetValue("SECOND");
	//MSG(second_value);

	return 0;
}