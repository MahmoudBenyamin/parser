#include"scanner.h"
#include <iomanip>
#include"parser.h"
using namespace std;
int main()
{
	/*scanner  s;
	ofstream out_file;
	std::string path_input;
	std::string path_output;
	cout << " the scanner take input file and create output file \n please enter the input and output path in formula (path+\\ file name) \n";
	while (1) {
		std::cout << "please enter the path of the file input : ";
		getline(cin, path_input);
		s.readFromFile(path_input);
		std::cout << "please enter the path of the file output : ";
		getline(cin, path_output);
		s.readFromFile(path_input);
		out_file.open(path_output + ".txt");

		std::vector <std::pair< std::string, std::pair< std::string, std::string>>> result = s.print();
		for (auto it : result)
		{
			
			out_file << setw(30) << it.first << "    ->" << setw(30) << it.second.first << "    ->" << setw(30) << it.second.second << std::endl;
			out_file << "............................................................................................................" << std::endl;

		}
		cout << "the scan is done ,please check the output file " << std::endl;
		s.clear();
		cout << "\n\n" << "if you want to scan new program , please enter the input path \n";
	}
	*/
	parser p;
	p.readFromFile("file.txt");
	system("pause");
	
}