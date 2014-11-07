#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
//#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>

/*#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>*/

using namespace std;

class Data {
public:
	Data() {}

	Data(string c_name, double c_v1, double c_v2, double c_v3, string c_check) {
		name = c_name;
		v1 = c_v1;
		v2 = c_v2;
		v3 = c_v3;
		if (c_check == "y") m[name] = 1;
		else m[name] = 0;
	}

    void save_struct(const Data &s, const char* filename){
    	// make an archive
	    ofstream ofs(filename);
	    boost::archive::text_oarchive oa(ofs);
	    oa << s;
	}

	void restore_struct(Data &s, const char* filename) {
	    // open the archive
	    ifstream ifs(filename);
	    boost::archive::text_iarchive ia(ifs);
		ia >> s;
	}

	void print_data() {
		cout << "---data---" << endl;
		cout << "\tname: " << name;
		cout << "\tv1: " << v1 << ";\tv2: " << v2 << ";\tv3: " << v3 << endl;
		for(map<string, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
			cout << "\t\tKEY: " << it->first << " -> VALUE: " << it->second << endl;
		}
		cout << "----------" << endl;
	}

private:
	string name;
	double v1, v2, v3;
	map<string, int> m;

    friend class boost::serialization::access;
	template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        //ar & boost::serialization::base_object<SingleMetric>(*this);
        ar & name;
        ar & v1;
        ar & v2;
        ar & v3;
        ar & m;
    }
};



int main() {
	string name, check;
	double v1, v2, v3;
	cout << "Input Data name:" << endl;
	cin >> name;

	cout << "Input three values:" << endl;
	cin >> v1 >> v2 >> v3;

	cout << "May I check it? (y/n)" << endl;
	cin >> check;

	Data data(name, v1, v2, v3, check);

	string filename = "demofile.txt";
	cout << "file to serialize <" << filename << ">" << endl;

	data.save_struct(data, filename.c_str());

	Data data_rest;
	data_rest.restore_struct(data_rest, filename.c_str());

	data_rest.print_data();
}