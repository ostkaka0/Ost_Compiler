#pragma once
#include "Ast.h"

#define SINGLE_ARG(...) __VA_ARGS__
#define ENUM_CLASS(_name,_enum)\
class _name : public EnumClass\
{\
public:\
	static enum class Enum : char\
	{\
		_enum\
	};\
	_name::Enum Value;\
	_name(_name::Enum value)\
	{\
		Value = value;\
	}\
}

//#define LITERAL(_type, _name) class _name : public Object { public: _type Value; _name(_type value) { Value = value } }

class Object
{
};

/*class CharLiteral : public Object
{
public:
	char Value;
	Char(char value)
	{
		Value = value;
	}
};

class StringLiteral : public Object
{
public:
	std::string Value;
	String(string value)
	{
		Value = value;
	}
};

class BooleanLiteral : public Object
{
public:
	bool Value;
	Boolean(bool value)
	{
		Value = value;
	}
};

class IntegerLiteral : public Object
{
public:
	int Value;
	Integer(int value)
	{
		Value = value;
	}
};*/

template<typename T> class Literal
{
public:
	T Value;
	Literal(T value)
	{
		Value = value;
	}

	inline bool operator==(const T &right) { return Value == right; }
	inline bool operator!=(const T &right) { return Value != right; }
	inline bool operator< (const T &ritht) { return Value <  right; }
	inline bool operator> (const T &right) { return Value >  right; }
	inline bool operator<=(const T &right) { return Value <= right; }
	inline bool operator>=(const T &right) { return Value >= right; }

	inline T operator+(const Literal<T> &right) { return Value+right.Value; }
	inline T operator-(const T &right) { return Value-right; }
	inline T operator*(const T &right) { return Value*right; }
	inline T operator/(const T &right) { return Value/right; }
	inline T operator%(const T &right) { return Value%right; }

	Literal<T> &operator=(const T &right)
	{
		Value = right;
		return *this;
	}

	operator T&()
	{
		return Value;
	}

	std::ostream& operator<<(std::ostream& os)
	{
		os << Value;
		return os;
	}
	std::istream& operator>>(std::istream& is)
	{
	  is >> Value;
	  return is;
	}

};

class EnumClass : public Object
{
};

ENUM_CLASS(BinOp, SINGLE_ARG(
	ADD = 0,
	SUB,
	MUL,
	DIV,
	MOD,

	SHIFT_LEFT,
	SHIFT_RIGHT,

	OR,
	AND,
	XOR,

	B_OR,
	B_AND,

	EQUAL,
	NOTEQUAL,
	MORE,
	LESS,
	MORE_OR_EQUAL,
	LESS_OR_EQUAL,

	ENUM_END
));

ENUM_CLASS(AssignOp, SINGLE_ARG(
	ASSIGN = BinOp::Enum::ENUM_END,
	ASSIGN_ADD,
	ASSIGN_SUB,
	ASSIGN_MUL,
	ASSIGN_DIV,
	ASSIGN_MOD,

	ASSIGN_SHIFT_LEFT,
	ASSIGN_SHIFT_RIGHT,

	ASSIGN_OR,
	ASSIGN_AND,
	ASSIGN_XOR,

	ASSIGN_B_OR,
	ASSIGN_B_AND,

	ENUM_END
));

ENUM_CLASS(LogicOp, SINGLE_ARG(
	NOT = AssignOp::Enum::ENUM_END,
	B_NOT,
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