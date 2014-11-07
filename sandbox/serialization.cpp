#include <fstream>
#include <iostream>

using namespace std;

class gps_position {
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & degrees;
        ar & minutes;
        ar & seconds;
    }
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position(){};
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}

    void print_data(string name) const {
        cout << "--------" << endl;
        cout << "gpu_position: " << name << endl;
        cout << "\tdegrees: " << degrees << endl;
        cout << "\tminutes: " << minutes << endl;
        cout << "\tseconds: " << seconds << endl;
        cout << "--------" << endl;
    }
};

int main() {
    // create and open a character archive for output
    ofstream ofs("filename");

    // create class instance
    const gps_position g(35, 59, 24.567f);

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << g;
        // archive and stream closed when destructors are called
    }

    g.print_data("g");
    // ... some time later restore the class instance to its orginal state
    gps_position newg;
    {
        // create and open an archive for input
        ifstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> newg;
        // archive and stream closed when destructors are called
    }
    newg.print_data("newg");
    return 0;
}