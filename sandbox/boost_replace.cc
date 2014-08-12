#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

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

  std::string s_character = "Ei; que jo* tinc un cullo de 'caracters' (especials)";
  re = ("\\*");//, boost::regex::perl|boost::regex::icase);
  s_character = boost::regex_replace(s_character, re, "\\\\*");
  cout << endl << endl << "s_character -{*}: " << s_character << endl;
  re = ("\\;");//, boost::regex::perl|boost::regex::icase);
  s_character = boost::regex_replace(s_character, re, "\\\\;");
  cout << endl << endl << "s_character -{*;}: " << s_character << endl;

  std::string base_name = "/home/usuaris/gilabert/asiya/gpu/sample/tmp/9179.63435714231.out.BLEU.sgml";
  cout << "name: " << base_name << endl;
  boost::filesystem::path pathname (base_name);
  cout << "base_name: " << pathname.filename().string() << endl;

}