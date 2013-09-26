#pragma once
#include "Ast.h"

#define ENUM_CONSTRUCTOR(name) name(name::Enum value) { Value = value; }
#define SINGLE_ARG(...) __VA_ARGS__
#define ENUM_CLASS(name,_enum) class name : EnumClass { public: static enum class Enum : char { _enum } Value; ENUM_CONSTRUCTOR(name) }

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

class EnumClass : public Object
{
};

ENUM_CLASS(BinOp, SINGLE_ARG(
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
	LESSOREQUAL,

	ENUM_END
));

ENUM_CLASS(AssignOp, SINGLE_ARG(
	ASSIGN = BinOp::Enum::ENUM_END,
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
	ASSIGN_B_AND,

	ENUM_END
));

ENUM_CLASS(LogicOp, SINGLE_ARG(
	NOT = AssignOp::Enum::ENUM_END,
	PLUSPLUS,
	MINUSMINUS,
	REF,
	DEREF,
	MEMBER,
	DEREF_MEMBER,
	INDEX,

	ENUM_END
));

ENUM_CLASS(DeclareVariable, SINGLE_ARG(
	DECLARE_INT = LogicOp::Enum::ENUM_END,
	DECLARE_BOOLEAN,
	DECLARE_CHAR,
	DECLARE_STRING,
	DECLARE_DOUBLE,
	DECLARE_OBJECT,
	DECLARE_POINTER,

	ENUM_END
));

ENUM_CLASS(GetVariable, SINGLE_ARG(
	GET_INT = LogicOp::Enum::ENUM_END,
	GET_BOOLEAN,
	GET_CHAR,
	GET_STRING,
	GET_DOUBLE,
	GET_OBJECT,
	GET_POINTER,

	ENUM_END
	));

ENUM_CLASS(PushVariable, SINGLE_ARG(
	PUSH_INT = LogicOp::Enum::ENUM_END,
	PUSH_TRUE,
	PUSH_FALSE,
	PUSH_CHAR,
	PUSH_STRING,
	PUSH_DOUBLE,
	PUSH_OBJECT,
	PUSH_NULL,

	ENUM_END
	));

ENUM_CLASS(_DDF_, SINGLE_ARG(
	GOTO = PushVariable::Enum::ENUM_END,
	IF_TRUE,
	IF_FALSE,
	CALL_METHOD,

	ENUM_END
	));

ENUM_CLASS(sdf, SINGLE_ARG(
	GOTO = PushVariable::Enum::ENUM_END,
	IF_TRUE,
	IF_FALSE,
	CALL_METHOD,

	ENUM_END
	));