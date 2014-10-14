#include "../include/TB_NIST.hpp"
#include "../Common.hpp"
#include "../Config.hpp"

#include <fstream>
#include <sstream>

#include <libgen.h>
#include <stdlib.h>
#include <time.h>

#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>




void TB_NIST::process_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, map<string, FileInfo> &m, string id, string docid, string genre) {
    xmlNodePtr cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"doc"))) {
            docid = string( (char*)xmlGetProp(cur_node, (const xmlChar*)"docid") );
            genre = string( (char*)xmlGetProp(cur_node, (const xmlChar*)"genre") );
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"seg"))) {
            char* segid = (char*)xmlGetProp(cur_node, (const xmlChar*)"id");
            out_idx << docid << " " << genre << " " << id << " " << segid << endl;
            out_txt << cur_node->children->content << endl;

            vector<string> lidx(4);
            lidx[0] = docid;    lidx[1] = genre;    lidx[2] = id; lidx[3] = segid;
            m[id].idx.push_back(lidx);
        }
        process_xml(cur_node->children, out_txt, out_idx, m, id, docid, genre);
    }
}

map<string, FileInfo> TB_NIST::read_file(const char* file) {
    // description _ reads a NIST XML file and writes an equivalent RAW file and the correspondence between them (IDX)
    //               (conforming ftp://jaguar.ncsl.nist.gov/mt/resources/mteval-xml-v1.5.dtd)
    if (Config::verbose > 1) fprintf(stderr, "reading NIST XML <%s>\n", file);

    map<string, FileInfo> m;

    boost::filesystem::path p (file);
    string file_gz = string(file) + "." + Common::GZEXT;
    boost::filesystem::path p_gz (file_gz);

    if (exists(p) or exists(p_gz)) {
        if (!exists(p) and exists(p_gz)) {
            string sysaux = Common::GUNZIP + " " + file_gz;
            system(sysaux.c_str());
        }

        xmlDocPtr doc = xmlReadFile(file, NULL, 0);
        if (doc == NULL) { fprintf(stderr, "[ERROR] Failed to parse %s\n", file); exit(1); }

        xmlNodePtr root_node = xmlDocGetRootElement(doc);
        string type = string( (char*)root_node->children->next->name );

        string dir = dirname((char*)file);

        //cout << "type: |" << type << "|" << endl;
        //cout << "dir: |" << dirname << "|" << endl;

        ofstream out_txt, out_idx;
        if (type == "srcset") {
            //cout << "OPEN file as <" << type << "> type" << endl;
            string basename = dir + "/" + "source";
            string name_txt = basename + ".txt"; //Common::SOURCEID; + ".txt";
            string name_idx = basename + ".idx";
            out_txt.open(name_txt.c_str());
            out_idx.open(name_idx.c_str());

            string setid = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"setid") );
            string srclang = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"srclang") );
            out_idx << setid << " " << srclang << " " << "***EMPTY***" << endl;
            vector<string> lidx_headline(3);
            lidx_headline[0] = setid;   lidx_headline[1] = srclang; lidx_headline[2] = "***EMPTY***";   //Common::EMPTY_ITEM;
            m["source"].idx.push_back(lidx_headline);

            process_xml(root_node, out_txt, out_idx, m, "source", "", "");
            m["source"].txt = name_txt;
            m["source"].wc = m["source"].idx.size() - 1;

            cout << "wc: " << m["source"].wc << endl;
        }
        else if (type == "refset" or type == "tstset") {
            string id;
            if (type == "refset") id = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"refid") );
            else id = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"sysid") );

            string basename = dir + "/";
            string name_txt = basename + id + ".txt";
            string name_idx = basename + id + ".idx";
            out_txt.open(name_txt.c_str());
            out_idx.open(name_idx.c_str());

            string setid = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"setid") );
            string srclang = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"srclang") );
            string trglang = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"trglang") );
            out_idx << setid << " " << srclang << " " << trglang << endl;
            vector<string> lidx_headline(3);
            lidx_headline[0] = setid;   lidx_headline[1] = srclang; lidx_headline[2] = trglang;
            m[id].idx.push_back(lidx_headline);

            process_xml(root_node, out_txt, out_idx, m, id, "", "");
            m[id].txt = name_txt;
            m[id].wc = m[id].idx.size() - 1;

            cout << "wc: " << m[id].wc << endl;
        }
        out_idx.close();
        out_txt.close();
        xmlFreeDoc(doc);

    } else { fprintf(stderr, "[ERROR] unavailable file <%s>\n", file); exit(1); }

    return m;
}


void TB_NIST::process_nist_file(string file, string type) {
    // description _ read the contents of a NIST xml and generate txt and idx files
    //              (idx structure is also stored onto memory)
    cout << "----------NIST INPUT FILES----------" << endl;
    map<string, FileInfo> contents = TB_NIST::read_file(file.c_str());
    for(map<string, FileInfo>::const_iterator it = contents.begin(); it != contents.end(); ++it) {
        if (type == "source" or type == "src") {
            TESTBED::src = it->second.txt;
            TESTBED::IDX["source"] = it->second.idx;
            TESTBED::wc["source"] = it->second.wc;
        }
        else if (type == "reference" or type == "ref") {
            if (TESTBED::Hrefs.find(it->first) != TESTBED::Hrefs.end()) {
                fprintf(stderr, "[ERROR] reference name '%s' duplicated!!\n", it->first.c_str()); exit(1);
            }
            TESTBED::Hrefs[it->first] = it->second.txt;
            TESTBED::IDX[it->first] = it->second.idx;
            TESTBED::wc[it->first] = it->second.wc;
        }
        else if (type == "system" or type == "sys") {
            if (TESTBED::Hsystems.find(it->first) != TESTBED::Hsystems.end()) {
                fprintf(stderr, "[ERROR] system name '%s' duplicated!!\n", it->first.c_str()); exit(1);
            }
            TESTBED::Hsystems[it->first] = it->second.txt;
            TESTBED::IDX[it->first] = it->second.idx;
            TESTBED::wc[it->first] = it->second.wc;
        }
        else { fprintf(stderr, "[ERROR] unknown file type <%s>!!\n", type.c_str()); exit(1); }
    }
}


void SGML_f_create_create_doc(string input, string output, string sysid, xmlDocPtr &doc, xmlNodePtr &root_node) {
        string randomInput, randomInput2;

        //if exists input....
        string input_gz = input + "." + Common::GZEXT;
        boost::filesystem::path p (input);
        boost::filesystem::path p_gz (input_gz);
        if (exists(p) or exists(p_gz)) {

            if (Config::verbose > 1) printf("reading <%s\n>", input.c_str());

            if (!exists(p)) {
                double nr = rand() % (Common::NRAND + 1);
                string input2 = TESTBED::replace_special_characters(input);
                stringstream rIn, rIn2, st;

                rIn << Common::DATA_PATH << "/" << Common::TMP << "/" << TESTBED::give_system_name(input) << "." << nr;
                rIn2 << Common::DATA_PATH << "/" << Common::TMP << "/" << TESTBED::give_system_name(input2) << "." << nr;

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
                //cout << "OPENED : " << input_file << endl;
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

void TB_NIST::SGML_f_create_mteval_doc(string input, string output, int type) {
    // description _ creation of a NIST SGML evaluation document from a "sentence-per-line" format corpus
    if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for NIST xml-parsing [type = %s]...\n", input.c_str(), (type == 0)? "SRC" : (type == 1)? "TST" : "REF");

    string set, sysid;
    switch(type) {
        case 0: set = "srcset"; sysid = "dummysysSRC"; break;
        case 1: set = "tstset"; sysid = "dummysysTST"; break;
        case 2: set = "refset"; sysid = "dummysysREF"; break;
    }
    //cout << "--> type: " << type << " | set: " << set << " | sysid: " << sysid << endl;

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

    SGML_f_create_create_doc(input, output, sysid, doc, root_node);

    xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void TB_NIST::SGML_f_create_mteval_multidoc(string output, int type) {
    // description _ creation of a NIST SGML evaluation document from a "sentence-per-line" format corpus
    //              (multi-document)
    if (Config::verbose > 1) {
        map<string, string>::const_iterator it = TESTBED::Hrefs.begin();
        fprintf(stderr, "OPENING [%s", it->first.c_str());
        ++it;
        while (it != TESTBED::Hrefs.end()) {
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

    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
        SGML_f_create_create_doc(it->second, output, it->first, doc, root_node);
    }
    xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}


void TB_NIST::SGML_GTM_f_create_mteval_doc(string input, string output) {
    // description _ creation of a NIST SGML evaluation document from a "sentence-per-line" format corpus
    if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for GTM xml-parsing...\n", input.c_str());

    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = NULL;
    xmlDocSetRootElement(doc, root_node);

    srand(time(NULL));
    SGML_f_create_create_doc(input, output, "dummysys", doc, root_node);

    xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}



void f_create_create_doc(string input, string output, string TGT, string cas, int type) {
    string set, id_label;
    vector<vector<string> > idx;
    switch(type) {
        case 0: set = "srcset"; id_label = "srcid"; idx = TESTBED::IDX["source"]; break;
        case 1: set = "tstset"; id_label = "sysid"; idx = TESTBED::IDX[TGT]; break;
        case 2: set = "refset"; id_label = "refid"; idx = TESTBED::IDX[TGT]; break;
    }

    string id = idx[1][2];
    //string input = it->second;
    string input_gz = input + "." + Common::GZEXT;

    boost::filesystem::path p (input);
    boost::filesystem::path p_gz (input_gz);

    string randomInput, randomInput2;

    if (exists(p) or exists(p_gz)) {

        if (Config::verbose > 1) printf("reading <%s\n>", input.c_str());

        if (!exists(p)) {
            double nr = rand() % (Common::NRAND + 1);
            string input2 = TESTBED::replace_special_characters(input);
            stringstream rIn, rIn2, st;
            rIn << Common::DATA_PATH << "/" << Common::TMP << "/" << TESTBED::give_system_name(input) << "." << nr;
            rIn2 << Common::DATA_PATH << "/" << Common::TMP << "/" << TESTBED::give_system_name(input2) << "." << nr;
            randomInput = rIn.str();
            randomInput2 = rIn2.str();

            st << Common::GUNZIP << " -c " << input2 << "." << Common::GZEXT << " > " << randomInput2;
            string command = st.str();

            system(command.c_str());
        }


        // Creates a new document, a node and a set it as a root node
        xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
        xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "mteval");
        xmlDocSetRootElement(doc, root_node);

        // STORE DOCUMENT
        root_node = xmlNewChild(root_node, NULL, BAD_CAST set.c_str(), NULL);
        xmlNewProp(root_node, BAD_CAST id_label.c_str(), BAD_CAST id.c_str());
        xmlNewProp(root_node, BAD_CAST "setid", BAD_CAST idx[0][0].c_str());
        xmlNewProp(root_node, BAD_CAST "srclang", BAD_CAST idx[0][1].c_str());
        xmlNewProp(root_node, BAD_CAST "trglang", BAD_CAST idx[0][2].c_str());


        int nSEGMENTS = 1;

        // DOCUMENTS
        string str, input_file, docid;

        if (exists(p)) input_file = input;
        else input_file = randomInput;

        ifstream file(input_file.c_str());
        if (file) {
            //cout << "OPENED : " << input_file << endl;
            xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "doc", NULL);

            while (getline(file, str)) {

                if (idx[nSEGMENTS][0] != docid) {   //NEW DOCUMENT
                    if (nSEGMENTS > 1) {
                        xmlNewProp(doc_node, BAD_CAST "docid", BAD_CAST docid.c_str());
                        xmlNewProp(doc_node, BAD_CAST "genre", BAD_CAST idx[nSEGMENTS-1][1].c_str());
                        xmlNewProp(doc_node, BAD_CAST  id_label.c_str(), BAD_CAST id.c_str());
                        if (type == 2) xmlNewProp(doc_node, BAD_CAST "sysid", BAD_CAST id.c_str());

                        doc_node = xmlNewChild(root_node, NULL, BAD_CAST "doc", NULL);
                    }
                    docid = idx[nSEGMENTS][0];
                }
                boost::regex re("\\s+$");
                string line = boost::regex_replace(str, re, "");
                if (cas == Common::CASE_CI) boost::to_lower(line);
                if (line == "") line = Common::EMPTY_ITEM;

                xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "seg", BAD_CAST line.c_str());
                //char buffer[50];
                //sprintf(buffer, "%d", nSEGMENTS);
                //xmlNewProp(seg_node, BAD_CAST "id", (const xmlChar *) buffer);
                xmlNewProp(seg_node, BAD_CAST "id", BAD_CAST idx[nSEGMENTS][3].c_str());
                ++nSEGMENTS;
            }
            //LAST DOCUMENT
            xmlNewProp(doc_node, BAD_CAST "docid", BAD_CAST docid.c_str());
            xmlNewProp(doc_node, BAD_CAST "genre", BAD_CAST idx[nSEGMENTS-1][1].c_str());
            xmlNewProp(doc_node, BAD_CAST  id_label.c_str(), BAD_CAST id.c_str());
            if (type == 2) xmlNewProp(doc_node, BAD_CAST "sysid", BAD_CAST id.c_str());

            file.close();
        } else { fprintf(stderr, "couldn't open file: %s\n", input_file.c_str()); exit(1); }

        xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
        xmlFreeDoc(doc);
        xmlCleanupParser();
    }
}

void TB_NIST::f_create_mteval_doc(string input, string output, string TGT, string cas, int type) {
    // description _ creation of a NIST XML evaluation document from a "sentence-per-line" format corpus
    //               (conforming ftp://jaguar.ncsl.nist.gov/mt/resources/mteval-xml-v1.5.dtd)
    if (Config::verbose > 1) fprintf(stderr, "OPENING <%s> for NIST xml-parsing [type = %s]...\n", input.c_str(), (type == 0)? "SRC" : (type == 1)? "TST" : "REF");
    /*
        cout << "TB_NIST::f_create_mteval_doc(" << endl;
        cout << "\tinput: " << input << endl;
        cout << "\toutput: " << output << endl;
        cout << "\tTGT: " << TGT << endl;
        cout << "\tcas: " << cas << endl;
        cout << "\ttype: " << type << endl << ")" << endl;
    */
    srand(time(NULL));
    f_create_create_doc(input, output, TGT, cas, type);
}

void TB_NIST::f_create_mteval_multidoc(string output, string cas, int type) {
    // description _ creation of a NIST XML evaluation document from a "sentence-per-line" format corpus
    //               (conforming ftp://jaguar.ncsl.nist.gov/mt/resources/mteval-xml-v1.5.dtd)
    //               (multi-document)
    if (Config::verbose > 1) {
        map<string, string>::const_iterator it = TESTBED::Hrefs.begin();
        fprintf(stderr, "OPENING [%s", it->first.c_str());
        ++it;
        while (it != TESTBED::Hrefs.end()) {
            fprintf(stderr, " %s", it->first.c_str());
            ++it;
        }
        fprintf(stderr, "] for NIST* xml-parsing...\n");
    }
    /*
        cout << "TB_NIST::f_create_mteval_multidoc(" << endl;
        cout << "\toutput: " << output << endl;
        cout << "\tcas: " << cas << endl;
        cout << "\ttype: " << type << endl << ")" << endl;
    */
    srand(time(NULL));
    for (map<string, string>::const_iterator it = TESTBED::Hrefs.begin(); it != TESTBED::Hrefs.end(); ++it) {
        f_create_create_doc(it->second, output, it->first, cas, type);
    }
}

/*void TB_NIST::f_create_mteval_multidoc(string output, string cas, int type) {
    // description _ creation of a NIST XML evaluation document from a "sentence-per-line" format corpus
    //               (conforming ftp://jaguar.ncsl.nist.gov/mt/resources/mteval-xml-v1.5.dtd)
    //               (multi-document)
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

    srand(time(NULL));
    for (map<string, string>::const_iterator it = Config::Hrefs.begin(); it != Config::Hrefs.end(); ++it) {

        string set, id_label;
        vector<vector<string> > idx;
        switch(type) {
            case 0: set = "srcset"; id_label = "srcid"; idx = Config::IDX["source"]; break;
            case 1: set = "tstset"; id_label = "sysid"; idx = Config::IDX[it->first]; break;
            case 2: set = "refset"; id_label = "refid"; idx = Config::IDX[it->first]; break;
        }

        string id = idx[1][2];
        string input = it->second;
        string input_gz = input + "." + Common::GZEXT;

        boost::filesystem::path p (input);
        boost::filesystem::path p_gz (input_gz);

        string randomInput, randomInput2;

        if (exists(p) or exists(p_gz)) {

            if (Config::verbose > 1) printf("reading <%s\n>", input.c_str());

            if (!exists(p)) {
                double nr = rand() % (Common::NRAND + 1);
                string input2 = Common::replace_special_characters(input);
                stringstream rIn, rIn2, st;
                rIn << Common::DATA_PATH << "/" << Common::TMP << "/" << Common::give_system_name(input) << "." << nr;
                rIn2 << Common::DATA_PATH << "/" << Common::TMP << "/" << Common::give_system_name(input2) << "." << nr;
                randomInput = rIn.str();
                randomInput2 = rIn2.str();

                st << Common::GUNZIP << " -c " << input2 << "." << Common::GZEXT << " > " << randomInput2;
                string command = st.str();

                system(command.c_str());
            }


            // Creates a new document, a node and a set it as a root node
            xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
            xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "mteval");
            xmlDocSetRootElement(doc, root_node);

            // STORE DOCUMENT
            root_node = xmlNewChild(root_node, NULL, BAD_CAST set.c_str(), NULL);
            xmlNewProp(root_node, BAD_CAST id_label.c_str(), BAD_CAST id.c_str());
            xmlNewProp(root_node, BAD_CAST "setid", BAD_CAST idx[0][0].c_str());
            xmlNewProp(root_node, BAD_CAST "srclang", BAD_CAST idx[0][1].c_str());
            xmlNewProp(root_node, BAD_CAST "trglang", BAD_CAST idx[0][2].c_str());


            int nSEGMENTS = 1;

            // DOCUMENTS
            string str, input_file, docid;

            if (exists(p)) input_file = input;
            else input_file = randomInput;

            ifstream file(input_file.c_str());
            if (file) {
                //cout << "OPENED : " << input_file << endl;
                xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "doc", NULL);

                while (getline(file, str)) {

                    if (idx[nSEGMENTS][0] != docid) {   //NEW DOCUMENT
                        if (nSEGMENTS > 1) {
                            xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "doc", NULL);
                            xmlNewProp(doc_node, BAD_CAST "docid", BAD_CAST docid.c_str());
                            xmlNewProp(doc_node, BAD_CAST "genre", BAD_CAST idx[nSEGMENTS-1][1].c_str());
                            xmlNewProp(doc_node, BAD_CAST  id_label.c_str(), BAD_CAST id.c_str());
                            xmlNewProp(doc_node, BAD_CAST "sysid", BAD_CAST id.c_str());
                        }
                        docid = idx[nSEGMENTS][0];
                    }
                    boost::regex re("\\s+$");
                    string line = boost::regex_replace(str, re, "");
                    if (cas == Common::CASE_CI) boost::to_lower(line);
                    if (line == "") line = Common::EMPTY_ITEM;

                    xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "seg", BAD_CAST line.c_str());
                    //char buffer[50];
                    //sprintf(buffer, "%d", nSEGMENTS);
                    //xmlNewProp(seg_node, BAD_CAST "id", (const xmlChar *) buffer);
                    xmlNewProp(seg_node, BAD_CAST "id", BAD_CAST idx[nSEGMENTS][3].c_str());
                    ++nSEGMENTS;
                }
                //LAST DOCUMENT
                xmlNewProp(doc_node, BAD_CAST "docid", BAD_CAST docid.c_str());
                xmlNewProp(doc_node, BAD_CAST "genre", BAD_CAST idx[nSEGMENTS-1][1].c_str());
                xmlNewProp(doc_node, BAD_CAST  id_label.c_str(), BAD_CAST id.c_str());
                xmlNewProp(doc_node, BAD_CAST "sysid", BAD_CAST id.c_str());

                file.close();
            } else { fprintf(stderr, "couldn't open file: %s\n", input_file.c_str()); exit(1); }

            xmlSaveFormatFileEnc(output.c_str(), doc, "UTF-8", 1);
            xmlFreeDoc(doc);
            xmlCleanupParser();
        }
    }
}*/