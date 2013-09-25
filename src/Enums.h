#pragma once
#include "Ast.h"

class EnumClass : public Object
{
};

class BinOp : public EnumClass
{
public:
		static enum class Enum : char
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
			LESSOREQUAL,

			ENUM_END
		} Value;
};

class AssignOp : EnumClass
{
public:
	static enum class Enum : char
	{
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
	} Value;
};

class LogicOp : EnumClass
{
public:
	static enum class Enum : char
	{
		NOT = AssignOp::Enum::ENUM_END,
		PLUSPLUS,
		MINUSMINUS,
		REF,
		DEREF,
		MEMBER,
		DEREF_MEMBER,
		INDEX,
		
		ENUM_END
	} Value;
};

class  DeclareVarBytes : EnumClass
{
	static enum class Enum : char
	{
		DECLARE_INT = LogicOp::Enum::ENUM_END,
		DECLARE_BOOLEAN,
		DECLARE_CHAR,
		DECLARE_STRING,
		DECLARE_DOUBLE,
		DECLARE_OBJECT,

		ENUM_END
	} Value;
};

class GetVAriable : EnumClass
{
	static enum class Enum : char
	{
		GET_INT = LogicOp::Enum::ENUM_END,
		GET_BOOLEAN,
		GET_CHAR,
		GET_STRING,
		GET_DOUBLE,
		GET_OBJECT,

		ENUM_END

	}
};