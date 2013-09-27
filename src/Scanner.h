#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Ast.h";

#define DEFINE_CONSTANT(_name) static Object *const _name

class Scanner
{
	std::vector<void*> *result;

public:
	Scanner(std::ifstream &reader);
	std::vector<void*> *GetTokens();

#pragma region Constants
	DEFINE_CONSTANT(ADD);
	DEFINE_CONSTANT(SUB);
	DEFINE_CONSTANT(MUL);
	DEFINE_CONSTANT(DIV);
	DEFINE_CONSTANT(MOD);

	DEFINE_CONSTANT(SHIFT_LEFT);
	DEFINE_CONSTANT(SHIFT_RIGHT);

	DEFINE_CONSTANT(OR);
	DEFINE_CONSTANT(AND);
	DEFINE_CONSTANT(XOR);
	DEFINE_CONSTANT(B_OR);
	DEFINE_CONSTANT(B_AND);

	DEFINE_CONSTANT(NOT);
	DEFINE_CONSTANT(B_NOT);

	DEFINE_CONSTANT(EQUAL);
	DEFINE_CONSTANT(NOTEQUAL);
	DEFINE_CONSTANT(MORE);
	DEFINE_CONSTANT(LESS);
	DEFINE_CONSTANT(MORE_OR_EQUAL);
	DEFINE_CONSTANT(LESS_OR_EQUAL);

	DEFINE_CONSTANT(ASSIGN);
	DEFINE_CONSTANT(ASSIGN_ADD);
	DEFINE_CONSTANT(ASSIGN_SUB);
	DEFINE_CONSTANT(ASSIGN_MUL);
	DEFINE_CONSTANT(ASSIGN_DIV);
	DEFINE_CONSTANT(ASSIGN_MOD);
	DEFINE_CONSTANT(ASSIGN_SHIFT_LEFT);
	DEFINE_CONSTANT(ASSIGN_SHIFT_RIGHT);
	DEFINE_CONSTANT(ASSIGN_OR);
	DEFINE_CONSTANT(ASSIGN_AND);
	DEFINE_CONSTANT(ASSIGN_XOR);
	DEFINE_CONSTANT(ASSIGN_B_OR);
	DEFINE_CONSTANT(ASSIGN_B_AND);
#pragma endregion

private:
	void Scan(std::stringstream &reader);
	bool IsLetter(char c);
	bool IsDigit(char c);
private:
	void *ToArithmethicConstant(char c);
	void *ToArithmethicConstant(std::string str);
};