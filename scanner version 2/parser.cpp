#include "parser.h"
//
parser::parser()
{
    
    index = 0;
}
//
bool parser::checkStmtSequence()
{
    if (checkStatement())
    {
        if ((index == result.size()-1) || (index == result.size())||(result[index].first=="else"))
        {
            return true;
        }
        else
        {
            if (match(";"))
            {
                if (checkStatement())
                {
                    return true;
                }

            }
        }
    
    }
    return false;
}
//
bool parser::checkStatement()
{
    bool  t=false;
    if (result[index].first == "if")
    {
        
        t = checkIfStmt();
            
    }
    else if (result[index].first == "repeat")
    {
       
        t = checkRepeatStmt();
    }   
    else if (result[index].first == "read")
    {
        
        t = checkReadStmt();
    }
    else if (result[index].first == "write")
    {
       
        t = checkWriteStmt();
    }
    else if (result[index].second.first == "identifier")
    {
       
        t = checkAssignStmt();
    }
    else if (result[index].first == "end")
    {
        t = matchEnd();
    }

    
    //index++;
	return t;
}
//
bool parser::match(std:: string word)
{   
    if (result[index].first == word)
    {
        index++;
        return true;
    }
    else
    {
        index++;
        //  return error
    }

}
//
bool parser::matchSecond(std::string word)
{
    if (result[index].second.first == word)
    {
        index++;
        return true;
    }
    else
    {
        index++;
        //  return error
    }

}
//
bool parser::exp()
{
    if (checkSimpleExp())
    {
        if ((index == result.size()-1 ) || (index == result.size())||(result[index].first==";")|| (result[index].first == "until")|| (result[index].first == "else"))
        {
            return true;
        }
        else
        {
            if (checkComparisonOp())
            {
                if (checkSimpleExp())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
//
bool parser::checkIfStmt()
{
    if (match("if"))
    {
        flagIf.push(1);
        if (exp())
        {
            if (match("then"))
            {
                if (checkStmtSequence())
                {
                    if (result[index].first == "else")
                    {
                        if (match("else"))
                        {
                            if (checkStmtSequence())
                            {
                                
                                    return true;
                                
                            }
                        }
                    }
                    else
                    {
                        
                            return true;
                        
                    }

                }
            }
        }
    }
    
    return false;
}
bool parser::matchEnd()
{
    if (flagIf.empty())
    {
        return false;
    }
    else
    {
        flagIf.pop();
        return true;
    }



}
//
bool parser::checkRepeatStmt()
{
    if (match("repeat"))
    {
        if (checkStmtSequence())
        {
            if (match("until"))
            {
                
                {if (exp())
                    return true;
                }
            }
        }

    }
    return false;
}
//
bool parser::checkAssignStmt()
{
    if (matchSecond("identifier"))
    {
        if (match(":="))
        {
            if (exp())
            {
                return true;
            }
        }
    }
    return false;
}
//
bool parser::checkReadStmt()
{
    if (match("read"))
    {
        if (matchSecond("identifier"))
        {
            return true;
        }
    }
    return false;
}
//
bool parser::checkWriteStmt()
{
    if (match("write"))
    {
        if (exp())
        {
            return true;
        }
    }
    return false;
}
//
bool parser::checkComparisonOp()
{
    index++;
    if (result[index - 1].first == "<" || result[index - 1].first == "=" || result[index - 1].first == ">")
    {
        return true;
    }

    return false;
}
//
bool parser::checkSimpleExp()
{
    if (checkTerm())
    {
        if ((index == result.size()-1 ) || (index == result.size())||(result[index].first == "<") || (result[index].first == "=")|| (result[index].first == ";"))
        {
            
        
            return true;
        }
        else
        {
             if (result[index].second.first == "reserved word")
            {
                 if (result[index].first == "then"|| result[index].first == "until"||result[index].first == "else")
                 {
                     return true;
                  }
             }
             else if (checkAddop())
                {
                    if (checkTerm())
                    {
                        return true;
                    }
                }
            
            }

    }
    return false;
}
//
bool parser::checkAddop()
{
    index++;
    if (result[index - 1].first == "+" || result[index - 1].first == "-")
    {
        return true;
    }

    return false;
    
}
//
bool parser::checkTerm()
{
    if (checkfactor())
    {
        if ((index == result.size()-1)|| (index == result.size() )||(result[index].first =="<")||(result[index].first == "=") || (result[index].first == ";"))
        {
            return true;
        }
        else
        {
            if (result[index].second.first =="reserved word")
            {
                if (result[index].first=="then"|| result[index].first == "until"|| result[index].first == "else")
                {
                    return true;
                }
            }
            else if (checkmulop())
            {
                if (checkfactor())
                {
                    return true;
                }
            }
        }
    }
    return false;
}
//
bool parser::checkmulop()
{
    index++;
    if (result[index-1].first == "*" || result[index-1].first == "/")
    {   
        return true;
    }

    return false;
}
//
bool parser::checkfactor()
{
    if (result[index].first == "(")
    {
        if (match("("))
        {
            if (exp())
            {
                if (match(")"))
                {
                    return true;
                }

            }
        }
    }
     
    else  if (result[index].second.first == "identifier")
    {
        if (matchSecond("identifier"))
        {
            return true;
        }
        
    }
    else if (result[index].second.first == "number")
    {
        if (matchSecond("number"))
        {
            return true;
        }
       
    }
    return false;
}
//
void parser::readFromFile(std::string path)
{
   /******************************************************/
    std::ifstream file(path /*+ ".txt"*/, std::ifstream::in);
    for (std::string word; getline(file, word); )
    {
        std::stringstream ss(word);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        for (auto it : vstrings)
        { 
            
            scan.scanText(it);
        }
       // std::vector <std::pair< std::string, std::pair< std::string, std::string>>> result;
       
        result = scan.print();
        
        if (checkStmtSequence())
        {
            std::cout << "true" << std::endl;
        }
        else
        {
            std::cout << "false" << std::endl;
        }
        /*
       
        for (auto it : r)
        {

            std::cout << std::setw(30) << it.first << "    ->" << std::setw(30) << it.second.first << "    ->" << std::setw(30) << it.second.second << std::endl;
            std::cout << "............................................................................................................" << std::endl;

        }*/
        scan.clear();
        index = 0;
       /* 
        if (checkStmtSequence())
        {
            std::cout << "true" << std::endl;
        }
        else
        {
            std::cout << "false" << std::endl;
        }
        scan.clear();
        index = 0;*/
    }
   /**********************************************************/
    
       
    
}