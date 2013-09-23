#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

#include "Parser.h"
#include "Scanner.h"

using namespace std;

Parser::Parser(vector<void*> *tokens)
{
	this->tokens = tokens;
	index = 0;
	result = ParseStmt(0);
}

const Stmt *Parser::GetResult()
{
	return result;
}

Stmt *Parser::ParseStmt(int maximumSequences)
{
	Stmt *result;

	if (index == tokens->size())
	{
		throw "expected statement, got eof";
	}
	else if (typeid((*tokens)[index]) == typeid(string))
	{
		string token = *reinterpret_cast<string*>((*tokens)[index]);
		if (token == "int")
		{
			index++;
			DeclareVar *declareVar = new DeclareVar();
			declareVar->DataType = "int";

			if (index < tokens->size() &&
				typeid((*tokens)[index]) == typeid(string))
			{
				declareVar->Ident = *reinterpret_cast<string*>((*tokens)[index]);
			}
			else
			{
				throw "expected variable namn after 'int'";
			}

			index++;

			if (index == tokens->size() ||
				typeid((*tokens)[index]) != typeid(AssignOp))
			{
				throw "expected '=' after variable name '" + declareVar->DataType + "'";
			}
		}
		else
		{
			throw "parse error";
		}

		if (index < tokens->size() &&
			typeid((*tokens)[index]) == typeid(string) &&
			*reinterpret_cast<string*>((*tokens)[index]) == ";" &&
			maximumSequences != 1)
		{
			index++;

			if (index < tokens->size())
			{
				if (typeid((*tokens)[index]) == typeid(string) &&
					*reinterpret_cast<string*>((*tokens)[index]) == "}")
				{
					Sequence *sequence = new Sequence();
					sequence->First = result;
					sequence->Second = ParseStmt((maximumSequences == 0)? 0:maximumSequences-1);
				}
			}
		}
	}
	else
	{
		throw "parse error";
	}

	return result;
}

Expr *Parser::ParseExpr()
{
	if (index == tokens->size())
	{
		throw "expected expression, got end of file.";
	}
	else if (typeid(tokens[index]) == typeid(int))
	{
		int intValue = *static_cast<int*>((*tokens)[index]);
		IntLiteral *intLiteral = new IntLiteral();
		intLiteral->value = intValue;

		if (index+1 < tokens->size())
		{
			if (typeid(tokens[index]) == typeid(BinOp))
			{
				return ParseBindExpr(intLiteral);
			}
		}

		return intLiteral;
	}
	else
	{
		throw "expected expression";
	}
}

Expr *Parser::ParseBindExpr(Expr *left)
{
	BindExpr *bindExpr = new BindExpr();
	bindExpr->Left = left;
	bindExpr->Op = *static_cast<BinOp*>((*tokens)[index]);
	index++;
	bindExpr->Right = ParseExpr();

	return bindExpr;
}