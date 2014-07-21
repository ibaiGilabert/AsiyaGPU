#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;

int main(){
  string str = "/home/usuaris/\\gilabert/asiya/gpu/sample/   ";
  boost::regex re("\\/\\s*$");//, boost::regex::perl|boost::regex::icase);
  string result = boost::regex_replace(str, re, "");

  cout << str << '|' << endl;
  cout << result << '|' << endl;

  string tools = "/ho//me/soft//asiya/tools//";
  boost::regex re2("/+");

  cout << tools << endl;
  tools = boost::regex_replace(tools, re2, "/");
  cout << tools << endl;

  string command = "[\n] directory <\n> does not exist!\n";
  cout << "command before: " << command;
  boost::regex re3("\\R");
  command = boost::regex_replace(command, re3, "");
  cout << "command after: " << command;
}