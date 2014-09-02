#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
int main()
{
    std::string s = "Hello,How,Are,You,Today";
    std::string s2 = "Hello How Are You Today Man";

    std::vector<std::string> v;
    std::istringstream buf(s2);
    for(std::string token; getline(buf, token, ' '); )
        v.push_back(token);
    //copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "."));
    //std::cout << '\n';

    for (int i = 0; i < v.size(); ++i) std::cout << "v[" << i << "]: " << v[i] << std::endl;
}