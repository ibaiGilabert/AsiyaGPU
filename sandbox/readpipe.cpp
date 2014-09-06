#include <iostream>
#include <stdlib.h>
#include <boost/filesystem.hpp>

using namespace std;

int main() {
	boost::filesystem::path path( boost::filesystem::current_path() );
	std::cout << "Current path is : " << path << std::endl;
}