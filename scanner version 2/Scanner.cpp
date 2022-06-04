/************************************************************************/
/*   implemented / mohamed hamada mohamed mahmoud                       */                                            
/*               / mohamed yasser hanfy                                 */ 
/*				 / mahmoud mohamed banyamin                             */ 
/*				 / mohamed obada bahaa									*/
/*				 / mostafa asherf										*/
/************************************************************************/

#include "scanner.h"

scanner::scanner()
{   /* insert reserved words in the vector*/
	Reserved_Words.push_back("if");
	Reserved_Words.push_back("then");
	Reserved_Words.push_back("else");
	Reserved_Words.push_back("end");
	Reserved_Words.push_back("repeat");
	Reserved_Words.push_back("until");
	Reserved_Words.push_back("read");
	Reserved_Words.push_back("write");
	/*insert Special Symbols in stored vector*/
	Special_Symbols.push_back("[");
	Special_Symbols.push_back("]");
	Special_Symbols.push_back("+");
	Special_Symbols.push_back("-");
	Special_Symbols.push_back("*");
	Special_Symbols.push_back("/");
	Special_Symbols.push_back("=");
	Special_Symbols.push_back("<");
	Special_Symbols.push_back("(");
	Special_Symbols.push_back(")");
	Special_Symbols.push_back(";");
	Special_Symbols.push_back(":=");
}
void scanner::readFromFile(std::string path)
{   
	std::ifstream file(path + ".txt", std::ifstream::in);
	for (std::string word; file >> word; )
		scanText(word);
}
void scanner::scanText(std::string text)
{
	std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);

	std::regex word_regex("([a-zA-Z]+)|([\\!-\\~]*)([a-zA-Z]+)([\\!-\\~]*)(\\_)*|([0-9]+)|((:)(=))|([(-+)])|(=)|(\\-)|(<)|(>)|(;)|(\\[)|(\\])");
	auto words_begin =
		std::sregex_iterator(text.begin(), text.end(), word_regex);
	auto words_end = std::sregex_iterator();
	/****************************************************************/
	bool flag = false;
	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();



		for (auto it : Reserved_Words)
		{
			if (it == match_str)
			{

				result.push_back(make_pair(match_str, std::make_pair("reserved word", " ")));
				flag = true;
				break;
			}

		}
		if (!flag)
		{
			for (auto it : Special_Symbols)
			{
				if (it == match_str)
				{

					result.push_back(make_pair(match_str, std::make_pair("Special Symbols", " ")));
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				if (is_number(match_str))
				{

					result.push_back(make_pair(match_str, std::make_pair("number", " ")));
				}
				else if ((match_str[0] >= 'a' && match_str[0] <= 'z') || (match_str[0] >= 'A' && match_str[0] <= 'Z'))
				{
					result.push_back(make_pair(match_str, std::make_pair("identifier", " ")));
				}
				else
				{
					result.push_back(make_pair(match_str, std::make_pair("unknow", " ")));
				}
			}
		}
		flag = false;
	}
	identifyToken();
}
void scanner::clear()
{
	result.clear();
}
bool  scanner::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
void scanner::identifyToken()
{
	
	int i = 0;
	for (auto it : result)
	{

		/*********************  reserved word   ****************************/
		if (it.first == "if")
		{
			it.second.second = "IF";
		}
		else if (it.first == "then")
		{
			it.second.second = "THEN ";
		}
		else if (it.first == "else")
		{
			it.second.second = "ELSE";
		}
		else if (it.first == "end")
		{
			it.second.second = "END";
		}
		else if (it.first == "repeat")
		{
			it.second.second = "LOOP";
		}
		else if (it.first == "until")
		{
			it.second.second = "UNTIL";
		}
		else if (it.first == "read")
		{
			it.second.second = "READ";
		}
		else if (it.first == "write")
		{
			it.second.second = "WRITE";
		}
		/*****************************Special Symbols ***************************/
		else if (it.first == "+")
		{
			it.second.second = "addition";
		}
		else if (it.first == "-")
		{
			it.second.second = "subtraction ";
		}
		else if (it.first == "*")
		{
			it.second.second = "multiplication";
		}
		else if (it.first == "/")
		{
			it.second.second = "division";
		}
		else if (it.first == ":=")
		{
			it.second.second = "ASSIGN";
		}
		else if (it.first == "=")
		{
			it.second.second = "equal";
		}
		else if (it.first == ">")
		{
			it.second.second = "bigger than";
		}
		else if (it.first == "<")
		{
			it.second.second = "smaller than";
		}
		else if (it.first == ";")
		{
			it.second.second = "semicolon";
		}
		else if (it.first == "(")
		{
			it.second.second = "left brackets";
		}
		else if (it.first == ")")
		{
			it.second.second = "right brackets";
		}
		else if (it.first == "[")
		{
			it.second.second = "square brackets";
		}
		else if (it.first == "]")
		{
			it.second.second = "square brackets";
		}
		else if (it.second.first == "identifier")
		{
			it.second.second = "IDENTIFIER";
		}
		else if (it.second.first == "number")
		{
			it.second.second = "NUMBER";
		}
		else
		{
			it.second.second = "  ";
		}
		result[i].second.second = it.second.second;
		i++;
	}
}
std::vector <std::pair< std::string, std::pair< std::string, std::string>>> scanner::print()
{

	return result;


}
