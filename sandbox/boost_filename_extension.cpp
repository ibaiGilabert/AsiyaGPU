#include <iostream>
#include <string>
#include <libgen.h>
#include <boost/filesystem.hpp>
using namespace std;

int main(int argc, char* argv[]) {
  string file;
  while(cin >> file) {
    boost::filesystem::path p(file);   // p reads clearer than argv[1] in the following code
    cout << "dirname: " << dirname(&file[0]) << endl; //p.parent_path()
    cout << "basename: " << basename(&file[0]) << endl;
    cout << "filename: " << p.filename().string() << endl;
    cout << "stem: " << p.stem() << endl;
    cout << "extension: " << p.extension().string() << endl;
    cout << "extension-{.} " << (file.substr(file.find_last_of(".") + 1)) << endl;
    cout << "replace_ext (idx): " << p.replace_extension(".idx") << endl;
  }
}
