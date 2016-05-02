#pragma once
#include <string>
#include <vector>

class SymbolTableClass {
private:
	struct Variable {
		std::string mLabel;
		int mValue;
	};
	std::vector<Variable> variables;
	std::vector<int> mScopes;

public:
	// returns true if <s> is already in the symbol table. 
	bool Exists(std::string s);

	// adds <s> to the symbol table, 
	// or quits if it was already there 
	void AddEntry(std::string s);

	// returns the current value of variable <s>, when
	// interpreting. Meaningless for Coding and Executing.
	// Prints a message and quits if variable s does not exist. 
	int GetValue(std::string s);

	// sets variable <s> to the given value, when interpreting.
	// Meaningless for Coding and Executing.
	// Prints a message and quits if variable s does not exist.
	void SetValue(std::string s, int v);

	// returns the index of where variable <s> is.
	// returns -1 if variable <s> is not there.
	int GetIndex(std::string s);

	int GetScopeIndex(std::string s);

	// returns the current number of variables in the symbol
	// table.
	int GetCount();

	void PushScope();
	void PopScope();

};