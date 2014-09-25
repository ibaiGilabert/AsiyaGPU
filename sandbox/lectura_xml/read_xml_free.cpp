/**
 * section: Parsing
 * synopsis: Parse an XML file to a tree and free it
 * purpose: Demonstrate the use of xmlReadFile() to read an XML file
 *          into a tree and and xmlFreeDoc() to free the resulting tree
 * usage: parse1 test1.xml
 * test: parse1 test1.xml
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libgen.h>

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

 using namespace std;

 struct FileInfo {
    vector<vector<string> > idx;    //vector de linies. Linia -> vector de paraules
    string txt;
    int wc;
};

#ifdef LIBXML_TREE_ENABLED

/**
 * example1Func:
 * @filename: a filename or an URL
 *
 * Parse the resource and free the resulting tree
 */

void process_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, map<string, FileInfo> &m, string id, string docid, string genre) {
    xmlNodePtr cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        /*if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"refset"))) {
            xmlChar* setid = xmlGetProp(cur_node, (const xmlChar*)"setid");
            xmlChar* refid = xmlGetProp(cur_node, (const xmlChar*)"refid");
            xmlChar* srclang = xmlGetProp(cur_node, (const xmlChar*)"srclang");
            xmlChar* trglang = xmlGetProp(cur_node, (const xmlChar*)"trglang");

            xmlFree(setid);
            xmlFree(refid);
            xmlFree(srclang);
            xmlFree(trglang);
        }*/
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

map<string, FileInfo> example1Func(const char *filename) {
    map<string, FileInfo> m;

    xmlDocPtr doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) { fprintf(stderr, "[ERROR] Failed to parse %s\n", filename); exit(1); }

    xmlNodePtr root_node = xmlDocGetRootElement(doc);
    string type = string( (char*)root_node->children->next->name );

    string dir = dirname((char*)filename);

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

    return m;
}

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "[ERROR] Input file please...\n"); exit(1); }

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    map<string, FileInfo> m = example1Func(argv[1]);

    cout << "---------------------" << endl;
    for (map<string, FileInfo>::const_iterator it = m.begin(); it != m.end(); ++it) {
        cout << "\t" << it->first << endl;
        vector<vector<string> > mat = it->second.idx;
        for(int i = 0; i < mat.size(); ++i) {
            cout << "\t\t[";
            for(int j = 0; j < mat[i].size(); ++j) cout << mat[i][j] << ",";
            cout << "]" << endl;
        }
        cout << "\ttxt: " << it->second.txt << endl;
        cout << "\twc: " << it->second.wc << endl;
    }
    cout << "---------------------" << endl;

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}
#endif