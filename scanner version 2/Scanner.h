/************************************************************************/
/*   implemented / mohamed hamada mohamed mahmoud                       */
/*               / mohamed yasser hanfy                                 */
/*				 / mahmoud mohamed banyamin                             */
/*				 / mohamed obada bahaa									*/
/*				 / mostafa asherf										*/
/************************************************************************/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include<fstream>
#include<sstream>
#include <utility>
class scanner
{
private:
	std::vector <std::string>	Reserved_Words; /* if read write .....  */
	std::vector <std::string>	Special_Symbols;  /* +  -  * /  .....*/
	std::vector <std::pair< std::string, std::pair< std::string, std::string>>> result;
	bool is_number(const std::string& s);
	void identifyToken();

public:
	scanner();
	void readFromFile(std::string path);
	void scanText(std::string text);
	void clear();
	std::vector <std::pair< std::string, std::pair< std::string, std::string>>> print();
};

