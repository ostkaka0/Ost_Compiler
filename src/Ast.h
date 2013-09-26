#pragma once

#include <string>

#include "ByteObjects.h"

class Expr;

class BinOp;
class AssignOp;
class LogicOp;

class Stmt
{
};

class Sequence : public Stmt
{
public :
	Stmt *First;
	Stmt *Second;
};

/*class DeclareSequenze : public Stmt
{
public:
	std::string BaseType; //	const constant, datatype
	DeclareSequenzeObj *First;
};

class DeclareSequenzeObj : public Stmt
{
public:
	std::string ExtendType; //	*... pointers, & ref, &&rValue, * const konstant_ref, & const constant_ref
	std::string Ident;
	Expr *Expr;
	DeclareSequenzeObj *Next;
};*/

class DeclareVar : public Stmt
{
public:
	std::string DataType;
	std::string Ident;
	Expr *Expr;
};

class Assign : public Stmt
{
public:
	std::string Ident;
	AssignOp * AssignOP;
	Expr *Expr;
};

class Goto : public Stmt
{
public:
	Stmt *Statement;
};

class If : public Stmt
{
public:
	Expr *Condition;
	Stmt *Statement;
};

class IfElse : public Stmt
{
public:
	Expr *Condition;
	Stmt *Statement;
	Stmt *ElseStatement;
};

class WhileLoop : public Stmt
{
public:
	Expr *Condition;
	Stmt *Statement;
};

class DoWhile : public Stmt
{
public:
	Stmt *Statement;
	Expr *Condition;
};

class ForLoop : public Stmt
{
public:
	Stmt *Initialization;
	Expr *Condition;
	Stmt *Statement;
	Stmt *Update;
};

class Case : public Stmt
{
public:
	Expr *Condition;
	Stmt *Statement;
	Case *Next;
};


class Switch : public Stmt
{
public:
	Expr *Expression;
	Case *First;
};


/****    ****    Expressions    ****    ****/

class Expr
{
};

class BoolLiteral : public Expr
{
public:
	bool Value;
};

class IntLiteral : public Expr
{
public:
	int value;
};

class StringLiteral : public Expr
{
public:
	std::string Value;
};

class Logic : public Expr
{
public:
	LogicOp LogicOp;
	Expr *Expr;
};

class TypeCast : public Expr
{
public:
	std::string DataType;
	Expr *Expr;
};

class BindExpr : public Expr
{
public:
	Expr *Left;
	Expr *Right;
	BinOp Op;
};

class CondutionalEvaluation : public Expr
{
public:
	Expr *Condition;
	Expr *A;
	Expr *B;
};

class Variable : public Expr
{
public:
	std::string DataType;
	std::string Ident;
};





