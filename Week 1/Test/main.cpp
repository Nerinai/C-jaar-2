#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	/*std::ostringstream file;
	char data [1000];
	char name[100] = "testassssa.txt";
	
	file << "../" << name;
	
	std::cout << file.str();
	
	std::ofstream outfile;
	outfile.open(file.str());
	
	std::cout << "Writing to the file" << std::endl;
	std::cout << "Enter your name: ";
	std::cin.getline(data, 1000);
	
	outfile << data << std::endl;
	
	std::cout << "enter your age: ";
	std::cin >> data;
	std::cin.ignore();
	
	outfile << data << std::endl;
	
	outfile.close();*/
	
	char data [1000];
	char name [100] = "2 Pac - Changes.txt";
	char * pname = name;
	
	std::ostringstream oss;
	
	oss << "../songs/" << pname;
	
	std::ifstream infile;
	infile.open(oss.str());
	
	std::cout << "Reading from file." << std::endl;
	infile >> data;
	
	std::cout << data << std::endl;
	
/*	void readfile (char *data, const char *name){
	
	std::ostringstream filename;
	
	filename << "../songs/" << name;
	std::string a = filename.str();
	
	
	std::ifstream file;
	file.open(a);
	
	file >> data;*/
//}
	
	return 0;
}
