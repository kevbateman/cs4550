#include "Symbol.h"
#include <cstdlib>
#include <iostream>

bool SymbolTableClass::Exists(std::string s) {
	for (unsigned int i = 0; i < this->variables.size(); i++) {
		if (this->variables[i].mLabel == s) {
			return true;
		}
	}
	return false;
}

void SymbolTableClass::AddEntry(std::string s) {
	if (this->GetScopeIndex(s) == -1) {
		this->variables.push_back(Variable{ s });
	}
	else {
		try {
			throw s;
		}
		catch (std::string e) {
			std::cout << "An exception occured. Failed to add '" << e << "' because this label already exists." << std::endl;
			std::exit(0);
		}
	}
}

int SymbolTableClass::GetValue(std::string s) {
	int i = GetIndex(s);
	if (i != -1) {
		return this->variables[i].mValue;
	}
	else {
		try {
			throw s;
		}
		catch (std::string e) {
			std::cout << "An exception occured. Failed to get value for '" << e << "' because this label doesn't exist." << std::endl;
			std::exit(0);
		}
	}
}

void SymbolTableClass::SetValue(std::string s, int v) {
	int i = GetIndex(s);
	if (i != -1) {
		this->variables[i].mValue = v;
	}
	else {
		try {
			throw s;
		}
		catch (std::string e) {
			std::cout << "An exception occured. Failed to set value for '" << e << "' because this label doesn't exist." << std::endl;
			std::exit(0);
		}
	}
}

int SymbolTableClass::GetIndex(std::string s) {
	for ( int i = this->variables.size() - 1; i >= 0; i--) {
		if (this->variables[i].mLabel == s) {
			return i;
		}
	}
	return -1;
}

int SymbolTableClass::GetScopeIndex(std::string s) {
	//std::cout << this->mScopes.back();
	for (int i = this->variables.size() - 1; i >= this->mScopes.back(); i--) {
		if (this->variables[i].mLabel == s) {
			return i;
		}
	}
	return -1;
}
int SymbolTableClass::GetCount() {
	return this->variables.size();
}


void SymbolTableClass::PushScope() {
	this->mScopes.push_back(this->variables.size());
}

void SymbolTableClass::PopScope() {
	while (this->variables.size() > this->mScopes.back()) {
		this->variables.pop_back();
	}
	this->mScopes.pop_back();
}