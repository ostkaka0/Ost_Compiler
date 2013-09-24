#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Ast.h";

class Scanner
{
	std::vector<void*> *result;

public:
	Scanner(std::ifstream &reader);
	std::vector<void*> *GetTokens();

#pragma region Constants
	static void *const Add;
	static void *const Sub;
	static void *const Mul;
	static void *const Div;
	static void *const Mod;

	static void *const ShiftLeft;
	static void *const ShiftRight;

	static void *const Or;
	static void *const And;
	static void *const Xor;

	static void *const Not;

	static void *const B_Not;
	static void *const B_Or;
	static void *const B_And;

	static void *const Equal;
	static void *const NotEqual;
	static void *const More;
	static void *const Less;
	static void *const MoreOrEqual;
	static void *const LessOrEqual;

	static void *const Assign_;
	static void *const Assign_Add;
	static void *const Assign_Sub;
	static void *const Assign_Mul;
	static void *const Assign_Div;
	static void *const Assign_Mod;
	static void *const Assign_ShiftLeft;
	static void *const Assign_ShiftRight;
	static void *const Assign_Or;
	static void *const Assign_And;
	static void *const Assign_Xor;
	static void *const Assign_B_Or;
	static void *const Assign_B_And;
#pragma endregion

private:
	void Scan(std::stringstream &reader);
	bool IsLetter(char c);
	bool IsDigit(char c);
private:
	void *ToArithmethicConstant(char c);
	void *ToArithmethicConstant(std::string str);
};