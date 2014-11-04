#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;

int main(int argc, char* argv[]) {
  string file;
  while(cin >> file) {
    boost::filesystem::path p(file);   // p reads clearer than argv[1] in the following code
    cout << "filename: " << p.filename().string() << endl;
    cout << "extension: " << p.extension().string() << endl;
  }
}