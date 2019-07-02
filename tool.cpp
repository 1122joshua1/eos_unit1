#include <iostream>
#include <string>

std::string translate(std::string input, std::string variabele)
{ std::string result = ""; 
  result = variabele + "-a";
  for(int i=0; i<stoi(input); i++){
	result += "y";
}
  return result; }

int main(int argc, char *argv[])
{ std::string s;

  if(argc != 2)
  { std::cerr << "Deze functie heeft exact 1 argument nodig";
    return -1; }

  while(true)
  { std::cin >> s;
    if(std::cin.eof()){ return 0; }
std::cout << translate(argv[1], s) << std::endl; } }
