#pragma once

#include <string>

class Expr;

class BinOp { public: static enum class Enum; };
class AssignOp { public: static enum class Enum : char; };
class LogicOp { public: static enum class Enum : char; };

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
	LogicOp::Enum LogicOp;
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
	BinOp::Enum Op;
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

class Object
{
};



class Char : public Object
{
public:
	char Value;
};

class String : public Object
{
public:
	std::string Value;
};

class Boolean : public Object
{
public:
	bool Value;
};

class Integer : public Object
{
public:
	int Value;
};

enum class BinOp::Enum
	{
		ADD,
		SUB,
		MUL,
		DIV,
		MOD,

		SHIFTLEFT,
		SHIFTRIGHT,

		OR,
		AND,
		XOR,

		EQUAL,
		NOTEQUAL,
		MORE,
		LESS,
		MOREOREQUAL,
		LESSOREQUAL
	} Value;

class AssignOp : Object
{
	static enum class Enum : char
	{
		ASSIGN,
		ASSIGN_ADD,
		ASSIGN_SUB,
		ASSIGN_MUL,
		ASSIGN_DIV,
		ASSIGN_MOD,

		ASSIGN_SHIFTLEFT,
		ASSIGN_SHIFTRIGHT,

		ASSIGN_OR,
		ASSIGN_AND,
		ASSIGN_XOR,

		ASSIGN_B_OR,
		ASSIGN_B_AND
	} Value;
};

class LogicOp : Object
{
public:
	static enum class Enum : char
	{
		NOT,
		PLUSPLUS,
		MINUSMINUS,
		REF,
		DEREF,
		MEMBER,
		DEREF_MEMBER,
		INDEX
	} Value;
};