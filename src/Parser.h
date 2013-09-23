#pragma once

#include <vector>
#include "Ast.h"

class Parser
{
	int index;
	const std::vector<void*> *tokens;
	const Stmt *result;

public:
	Parser(std::vector<void*> *tokens);
	const Stmt *GetResult();
private:

	// int maximumSequences - How many statements it will parse. 0 for endless.
	Stmt *ParseStmt(int maxiumSequences);
	Expr *ParseExpr();

	Expr *ParseBindExpr(Expr *left);
};