#include <sstream>

#include "Scanner.h"

using namespace std;

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

			int *integer;
			sstream >> *integer;

			result->push_back(integer);
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
			string *str = new string();
			sstream >> *str;
			result->push_back(str);
			reader >> ch;
		}
		else if (ch == '\'')
		{
			reader >> ch;
			reader >> ch;
			result->push_back(new char(ch));
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
					result->push_back(new string(characters));
					break;
				}
				else
				{
					reader << c;
					result->push_back(new string(&ch));
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
			result->push_back(new string(&ch));
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
		return Scanner::Add;
	case '-':
		return Scanner::Sub;
	case '*':
		return Scanner::Mul;
	case '/':
		return Scanner::Div;
	case '%':
		return Scanner::Mod;

	case '|':
		return Scanner::Or;
	case '&':
		return Scanner::And;
	case '^':
		return Scanner::Xor;

	case '~':
		return Scanner::Not;
	case '!':
		return Scanner::B_Not;

	case '=':
		return Scanner::Equal;
	case '>':
		return Scanner::More;
	case '<':
		return Scanner::Less;

	default:
		throw "undefined arithmethic constant '" + string(&c) + "'";
	}
}

void *Scanner::ToArithmethicConstant(string str)
{
	if (str == "||")
	{
		return Scanner::B_Or;
	}
	else if (str == "&&")
	{
		return Scanner::B_And;
	}
	else if (str == "==")
	{
		return Scanner::Equal;
	}
	else if (str == "!=")
	{
		return Scanner::NotEqual;
	}
	else if (str == "<=")
	{
		return Scanner::LessOrEqual;
	}
	else if (str == ">=")
	{
		return Scanner::MoreOrEqual;
	}
	else if (str == "+=")
	{
		return Scanner::Assign_Add;
	}
	else if (str == "-=")
	{
		return Scanner::Assign_Sub;
	}
	else if (str == "*=")
	{
		return Scanner::Assign_Mul;
	}
	else if (str == "/=")
	{
		return Scanner::Assign_Div;
	}
	else if (str == "%=")
	{
		return Scanner::Assign_Mod;
	}
	else if (str == "<<=")
	{
		return Scanner::Assign_ShiftLeft;
	}
	else if (str == ">>=")
	{
		return Scanner::Assign_ShiftRight;
	}
	else if (str == "|=")
	{
		return Scanner::Assign_Or;
	}
	else if (str == "&=")
	{
		return Scanner::Assign_And;
	}
	else if (str == "^=")
	{
		return Scanner::Assign_Xor;
	}
	else if (str == "||=")
	{
		return Scanner::Assign_B_Or;
	}
	else if (str == "&&=")
	{
		return Scanner::Assign_B_And;
	}
	else
	{
		throw "undefined arithmethic constant '" + str + "'";
	}
}