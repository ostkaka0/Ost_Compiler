#include <sstream>

#include "Scanner.h"
#include "ByteObjects.h"

#define DECLARE_CLASS_ENUM_OBJ(_enum,_value) Object *const Scanner::_value = new _enum(_enum::Enum::_value)

using namespace std;

#pragma region Constants
	DECLARE_CLASS_ENUM_OBJ(BinOp,ADD);
	DECLARE_CLASS_ENUM_OBJ(BinOp,SUB);
	DECLARE_CLASS_ENUM_OBJ(BinOp,MUL);
	DECLARE_CLASS_ENUM_OBJ(BinOp,DIV);
	DECLARE_CLASS_ENUM_OBJ(BinOp,MOD);

	DECLARE_CLASS_ENUM_OBJ(BinOp,SHIFT_LEFT);
	DECLARE_CLASS_ENUM_OBJ(BinOp,SHIFT_RIGHT);

	DECLARE_CLASS_ENUM_OBJ(BinOp,OR);
	DECLARE_CLASS_ENUM_OBJ(BinOp,AND);
	DECLARE_CLASS_ENUM_OBJ(BinOp,XOR);
	DECLARE_CLASS_ENUM_OBJ(BinOp,B_OR);
	DECLARE_CLASS_ENUM_OBJ(BinOp,B_AND);

	DECLARE_CLASS_ENUM_OBJ(LogicOp,NOT);
	DECLARE_CLASS_ENUM_OBJ(LogicOp,B_NOT);

	DECLARE_CLASS_ENUM_OBJ(BinOp,EQUAL);
	DECLARE_CLASS_ENUM_OBJ(BinOp,NOTEQUAL);
	DECLARE_CLASS_ENUM_OBJ(BinOp,MORE);
	DECLARE_CLASS_ENUM_OBJ(BinOp,LESS);
	DECLARE_CLASS_ENUM_OBJ(BinOp,LESS_OR_EQUAL);
	DECLARE_CLASS_ENUM_OBJ(BinOp,MORE_OR_EQUAL);

	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_ADD);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_SUB);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_MUL);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_DIV);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_MOD);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_SHIFT_LEFT);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_SHIFT_RIGHT);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_OR);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_AND);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_XOR);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_B_OR);
	DECLARE_CLASS_ENUM_OBJ(AssignOp,ASSIGN_B_AND);
#pragma endregion

Scanner::Scanner(ifstream &reader)
{
	stringstream ss;
	ss << reader;
	Scan(ss);
}

vector<void *> *Scanner::GetTokens()
{
	return result;
}

void Scanner::Scan(stringstream &reader)
{
	char ch;
		
	while (reader >> ch)
	{
		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
		{
			continue;
		}
		else if (IsLetter(ch))
		{
			stringstream sstream;
			do
			{
				sstream << ch;
			}
			while(reader >> ch && IsLetter(ch));

			string *str;
			sstream >> *str;

			result->push_back(str);
		}
		else if (IsDigit(ch))
		{
			stringstream sstream;
			do
			{
				sstream << ch;
			}
			while(reader >> ch && IsDigit(ch));

			int integer;
			sstream >> integer;

			result->push_back(new Literal<int>(integer));
		}
		else if (ch == '"')
		{
			reader >> ch;
			stringstream sstream;
			sstream << '"';
			do
			{
				sstream << ch;
			}
			while(reader >> ch && ch != '"');

			sstream << '"';
			string str;
			sstream >> str;
			result->push_back(new Literal<string>(str));
			reader >> ch;
		}
		else if (ch == '\'')
		{
			reader >> ch;
			reader >> ch;
			result->push_back(new Literal<char>(ch));
			reader >> ch;
		}
		else switch(ch)
		{
		case '+':	// (ch)= is possible.
		case '-':
		case '*':
		case '/':
		case '%':

		case '|':
		case '&':
		case '^':

		case '!':
		case '~':

		case '=':
		case '>':
		case '<':
			{
				char c;
				reader >> c;
				if (c == '=' ||
					c == ch &&
						(c == '+' || c == '-' || c == '|' || c == '&' ||
						c == '<' || c == '>'))
				{
					char characters[] = {c,ch}; 
					result->push_back(ToArithmethicConstant(string(characters)));
					break;
				}
				else
				{
					reader << c;
					result->push_back(ToArithmethicConstant(ch));
				}
			}
			break;

		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case ';':
			result->push_back(ToArithmethicConstant(ch));
			break;
		}
	}
}

bool Scanner::IsLetter(char c)
{
	return c >= 'a' && c <= 'z' ||
		c >= 'A' && c <= 'Z' ||
		c == '_';
}

bool Scanner::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

void *Scanner::ToArithmethicConstant(char c)
{
	switch(c)
	{
	case '+':
		return Scanner::ADD;
	case '-':
		return Scanner::SUB;
	case '*':
		return Scanner::MUL;
	case '/':
		return Scanner::DIV;
	case '%':
		return Scanner::MOD;

	case '|':
		return Scanner::OR;
	case '&':
		return Scanner::AND;
	case '^':
		return Scanner::XOR;

	case '~':
		return Scanner::NOT;
	case '!':
		return Scanner::B_NOT;

	case '=':
		return Scanner::EQUAL;
	case '>':
		return Scanner::MORE;
	case '<':
		return Scanner::LESS;

	default:
		throw "undefined arithmethic constant '" + string(&c) + "'";
	}
}

void *Scanner::ToArithmethicConstant(string str)
{
	if (str == "||")
	{
		return Scanner::B_OR;
	}
	else if (str == "&&")
	{
		return Scanner::B_AND;
	}
	else if (str == "==")
	{
		return Scanner::EQUAL;
	}
	else if (str == "!=")
	{
		return Scanner::NOTEQUAL;
	}
	else if (str == "<=")
	{
		return Scanner::LESS_OR_EQUAL;
	}
	else if (str == ">=")
	{
		return Scanner::MORE_OR_EQUAL;
	}
	else if (str == "+=")
	{
		return Scanner::ASSIGN_ADD;
	}
	else if (str == "-=")
	{
		return Scanner::ASSIGN_SUB;
	}
	else if (str == "*=")
	{
		return Scanner::ASSIGN_MUL;
	}
	else if (str == "/=")
	{
		return Scanner::ASSIGN_DIV;
	}
	else if (str == "%=")
	{
		return Scanner::ASSIGN_MOD;
	}
	else if (str == "<<=")
	{
		return Scanner::ASSIGN_SHIFT_LEFT;
	}
	else if (str == ">>=")
	{
		return Scanner::ASSIGN_SHIFT_RIGHT;
	}
	else if (str == "|=")
	{
		return Scanner::ASSIGN_OR;
	}
	else if (str == "&=")
	{
		return Scanner::ASSIGN_AND;
	}
	else if (str == "^=")
	{
		return Scanner::ASSIGN_XOR;
	}
	else if (str == "||=")
	{
		return Scanner::ASSIGN_B_OR;
	}
	else if (str == "&&=")
	{
		return Scanner::ASSIGN_B_AND;
	}
	else
	{
		throw "undefined arithmethic constant '" + str + "'";
	}
}