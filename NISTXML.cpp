#include "NISTXML.hpp"
#include "Common.hpp"
#include "Config.hpp"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>

vector<vector<string> > NISTXML::write_fake_idx_file(string file, string IDX, int verbose) {
    vector<vector <string> > lIDX(0, vector<string>());

	if (verbose) fprintf(stderr, "reading raw file <%s>\n", file.c_str());
	string system_name = Common::give_system_name(file);
    ofstream f_idx(system_name.c_str());
    if (f_idx) {
        stringstream ss;
        ss << Common::UNKNOWN_SET << " " << Common::UNKNOWN_LANG << " " << Common::UNKNOWN_LANG;
        string fake_header = ss.str();

        f_idx << fake_header << endl;

        vector<string> l_header;

        boost::regex reeq(" ");
        boost::sregex_token_iterator j;
        for(boost::sregex_token_iterator i(fake_header.begin(), fake_header.end(), reeq, -1); i != j; ++i) {
            l_header.push_back(*i);
        }
        lIDX.push_back(l_header);

        ifstream f_raw(file.c_str());
        if (f_raw) {
            string line;
            int i = 1;

            while (getline(f_raw, line)) {
                stringstream sf;
                sf << Common::UNKNOWN_DOC << " " << Common::UNKNOWN_GENRE << " " << system_name << " " << i;
                string fake_line = sf.str();

                vector<string> l;

                boost::sregex_token_iterator jj;
                for(boost::sregex_token_iterator ii(fake_line.begin(), fake_line.end(), reeq, -1); ii != jj; ++ii) {
                    l.push_back(*ii);
                }
                lIDX.push_back(l);
                f_idx << fake_line << endl;
                i++;
            }
            f_raw.close();
        } else { fprintf(stderr, "couldn't open input file: %s\n", file.c_str());   exit(1); }

        f_idx.close();
    } else { fprintf(stderr, "couldn't open output IDX file: %s\n", system_name.c_str());	exit(1); }

    return lIDX;
}

void SGML_f_create_create_doc(string input, string output, int type, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node) {
        string randomInput, randomInput2;

        //if exists input....
        string input_gz = input + Common::GZEXT;
        boost::filesystem::path p (input);
        boost::filesystem::path p_gz (input_gz);
        if (exists(p) or exists(p_gz)) {

            if (Config::verbose > 1) printf("reading <%s\n>", input.c_str());

            if (!exists(p)) {
                string input2 = Common::replace_special_characters(input);
                stringstream rIn, rIn2, st;
                rIn << Common::DATA_PATH << "/" << Common::TMP << "/" << Common::give_system_name(input) << "." << rand() % (Common::NRAND + 1);
                rIn2 << Common::DATA_PATH << "/" << Common::TMP << "/" << Common::give_system_name(input2) << "." << rand() % (Common::NRAND + 1);
                randomInput = rIn.str();
                randomInput2 = rIn2.str();

                st << Common::GUNZIP << " -c " << input2 << "." << Common::GZEXT << " > " << randomInput2;
                string command = st.str();

                system(command.c_str());
            }

            int nSEGMENTS = 1;

            // STORE DOCUMENT
            xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);

            xmlNewProp(doc_node, BAD_CAST "docid", BAD_CAST "dummydoc");
            xmlNewProp(doc_node, BAD_CAST "sysid", BAD_CAST sysid.c_str());

            // DOCUMENTS
            string str, input_file;

            if (exists(p)) input_file = input;
            else input_file = randomInput;

            ifstream file(input_file.c_str());
            if (file) {
                cout << "OPENED : " << input_file << endl;
                while (getline(file, str)) {
                    boost::regex re("\\s+$");
                    string line = boost::regex_replace(str, re, "");

                    if (line == "") line = Common::EMPTY_ITEM;

                    xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "seg", BAD_CAST line.c_str());
                    char buffer[50];
                    sprintf(buffer, "%d", nSEGMENTS);
                    xmlNewProp(seg_node, BAD_CAST "id", (const xmlChar *) buffer);
                    ++nSEGMENTS;
                }
                file.close();
            } else { fprintf(stderr, "couldn't open file: %s\n", input_file.c_str()); exit(1); }
        } else fprintf(stderr, "\n[ERROR] UNAVAILABLE file <%s>!!!\n", input.c_str());
}

void NISTXML::SGML_f_create_mteval_doc(string input, string output, int type) {
    // description _ creation of a NIST SGML evaluation document from a "sentence-per-line" format corpus
    if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for NIST xml-parsing [type = %s]...\n", input.c_str(), (type == 0)? "SRC" : (type == 1)? "TST" : "REF");

    string set, sysid;
    switch(type) {
        case 0: set = "srcset"; sysid = "dummysysSRC"; break;
        case 1: set = "tstset"; sysid = "dummysysTST"; break;
        case 2: set = "refset"; sysid = "dummysysREF"; break;
    }
    cout << "--> type: " << type << " | set: " << set << " | sysid: " << sysid << endl;

    // Creates a new document, a node and a set it as a root node
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST set.c_str());
    xmlDocSetRootElement(doc, root_node);

    // STORE DOCUMENT
    xmlNewProp(root_node, BAD_CAST "setid", BAD_CAST "dummyset");
    xmlNewProp(root_node, BAD_CAST "srclang", BAD_CAST "dummylang");
    xmlNewProp(root_node, BAD_CAST "trglang", BAD_CAST "dummylang");

    srand(time(NULL));
    //string randomInput, randomInput2;

    SGML_f_create_create_doc(input, output, type, sysid, doc, root_node);

    xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void NISTXML::SGML_f_create_mteval_multidoc(string output, int type) {
    // description _ creation of a NIST SGML evaluation document from a "sentence-per-line" format corpus
    //              (multi-document)

    if (Config::verbose > 1) {
        map<string, string>::const_iterator it = Config::Hrefs.begin();
        fprintf(stderr, "OPENING [%s", it->first.c_str());
        ++it;
        while (it != Config::Hrefs.end()) {
            fprintf(stderr, " %s", it->first.c_str());
            ++it;
        }
        fprintf(stderr, "] for NIST* xml-parsing...\n");
    }

    string set, sysid;
    switch(type) {
        case 0: set = "srcset"; sysid = "dummysysSRC"; break;
        case 1: set = "tstset"; sysid = "dummysysTST"; break;
        case 2: set = "refset"; sysid = "dummysysREF"; break;
    }


    // Creates a new document, a node and a set it as a root node
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST set.c_str());
    xmlDocSetRootElement(doc, root_node);

    // STORE DOCUMENT
    xmlNewProp(root_node, BAD_CAST "setid", BAD_CAST "dummyset");
    xmlNewProp(root_node, BAD_CAST "srclang", BAD_CAST "dummylang");
    xmlNewProp(root_node, BAD_CAST "trglang", BAD_CAST "dummylang");

    srand(time(NULL));
    //string randomInput, randomInput2;

    for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {
        SGML_f_create_create_doc(it->second, output, type, it->first, doc, root_node);
    }
    xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

