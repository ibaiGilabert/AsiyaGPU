#include "../include/SC_ASIYA.hpp"
#include "../Common.hpp"
#include "../Config.hpp"

#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>


void SC_ASIYA::save_xml(string report_xml, string TGT, string REF, string METRIC, const MetricScore &m) {
    vector<vector<string> > idx = TESTBED::IDX[TGT];

    /*    cout << "-----------------idx-------------------" << endl;
        for (int i = 0; i < idx.size(); ++i) {
                //cout << "\tidx[" << i << "]" << endl;
                for(int j = 0; j < idx[i].size(); ++j) {
                        cout << "\t\tidx[" << i << "][" << j << "]: " << idx[i][j] << endl;
                }
                cout << endl;
        }
        cout << "---------------------------------------" << endl;

        for(int i = 0; i < doc_scores.size(); ++i) cout << "doc_scores[" << i  << "]: " << doc_scores[i] << endl;
        for(int i = 0; i < seg_scores.size(); ++i) cout << "seg_scores[" << i  << "]: " << seg_scores[i] << endl;*/



    int i = 1;
    int n_docs, n_doc_segs;
    n_docs = n_doc_segs = 0;

    string DOC = "-1";
    string document_id = "";

    // -> STORE IQREPORT
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "REPORT");
    xmlDocSetRootElement(doc, root_node);

    string app_name = Common::appNAME;
    boost::to_lower(app_name);
    string doc_type = app_name + ".dtd []"; //"!DOCTYPE " + SC_ASIYA::ROOT_ELEMENT + " \"" + app_name +".dtd\" []";
    xmlDtdPtr dtd = xmlCreateIntSubset(doc, BAD_CAST SC_FORMAT::ROOT_ELEMENT.c_str(), NULL, BAD_CAST doc_type.c_str());

/*
    xmlNewProp(root_node, BAD_CAST "hyp",       BAD_CAST    TGT.c_str());
    xmlNewProp(root_node, BAD_CAST "metric",    BAD_CAST    METRIC.c_str());

    char buffer[50];
    sprintf(buffer, "%d", n_docs);
    xmlNewProp(root_node, BAD_CAST "n_docs",    (const xmlChar *) buffer);

    sprintf(buffer, "%d", seg_scores.size());
    xmlNewProp(root_node, BAD_CAST "n_segments",(const xmlChar *) buffer);
    xmlNewProp(root_node, BAD_CAST "ref",       BAD_CAST    REF.c_str());

    //double x = Common::trunk_and_trim_number(sys_score, SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
    double x = sys_score;
    sprintf(buffer, "%f", x);
    xmlNewProp(root_node, BAD_CAST "score",     (const xmlChar *) buffer);
*/

    //double x;
    char buffer[50];
    xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);

    while (i < idx.size()) {
        if (idx[i][0] != document_id) { // NEW DOCUMENT

            if (DOC != "-1") {
                //x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
                //x = m.doc_scores[n_docs-1];
                xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

                sprintf(buffer, "%d", n_docs);
                xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

                sprintf(buffer, "%d", n_doc_segs);
                xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

                //sprintf(buffer, "%.%df", x);
                //trunk_and_trim_number(m.doc_scores[n_docs-1]);
                xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) trunk_and_trim_number(m.doc_scores[n_docs-1]).c_str());

                doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
            }
            DOC = document_id = idx[i][0];
            n_docs++;
            n_doc_segs = 0;
        }

        // CREATE A SEGMENT
        //x = Common::trunk_and_trim_number(seg_scores[i - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
        //x = m.seg_scores[i-1];
        //sprintf(buffer, "%f", x);
        xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "S", (const xmlChar *) trunk_and_trim_number(m.seg_scores[i-1]).c_str());
        sprintf(buffer, "%d", i);
        xmlNewProp(seg_node, BAD_CAST "n", (const xmlChar *) buffer);
        n_doc_segs++;
        i++;
    }

    // PASTE LAST DOC (if any)
    if (DOC != "-1") {
        //x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
        //x = m.doc_scores[n_docs-1];
        //doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
        xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

        sprintf(buffer, "%d", n_docs);
        xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

        sprintf(buffer, "%d", n_doc_segs);
        xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

        //sprintf(buffer, "%f", x);
        xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) trunk_and_trim_number(m.doc_scores[n_docs-1]).c_str());
    }

    xmlNewProp(root_node, BAD_CAST "hyp",       BAD_CAST    TGT.c_str());
    xmlNewProp(root_node, BAD_CAST "metric",    BAD_CAST    METRIC.c_str());

    //char buffer[50];
    sprintf(buffer, "%d", n_docs);
    xmlNewProp(root_node, BAD_CAST "n_docs",    (const xmlChar *) buffer);

    sprintf(buffer, "%d", (int)m.seg_scores.size());
    xmlNewProp(root_node, BAD_CAST "n_segments",(const xmlChar *) buffer);
    xmlNewProp(root_node, BAD_CAST "ref",       BAD_CAST    REF.c_str());

    //double x = Common::trunk_and_trim_number(sys_score, SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
    //x = m.sys_score;
    //sprintf(buffer, "%f", x);
    xmlNewProp(root_node, BAD_CAST "score",     (const xmlChar *) trunk_and_trim_number(m.sys_score).c_str());

    xmlSaveFormatFileEnc(report_xml.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}

void SC_ASIYA::write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {
    MetricScore m;
    m.sys_score = sys_score;
    m.doc_scores = doc_scores;
    m.seg_scores = seg_scores;
    write_report(TGT, REF, METRIC, m);
}

void SC_ASIYA::write_report(string TGT, string REF, string METRIC, const MetricScore &m){
    // description _ writes evaluation scores onto a given XML report file
    //stringstream r_xml;
    string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT +"/"+REF+"/"+METRIC+"."+Common::XMLEXT;

    if (Config::verbose) fprintf(stderr, "writing XML REPORT <%s>\n", report_xml.c_str());

    string p_aux = Common::DATA_PATH+"/"+Common::REPORTS;
    string p_tgt = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT;
    string p_ref = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF;

    boost::filesystem::path p (p_aux);
    boost::filesystem::path p2 (p_tgt);
    boost::filesystem::path p3 (p_ref);

    if (!exists(p)) {
        string s_aux = "mkdir " + p_aux;
        system(s_aux.c_str());
    }
    if (!exists(p2)) {
        string s_aux = "mkdir " + p_tgt;
        system(s_aux.c_str());
    }
    if (!exists(p3)) {
        string s_aux = "mkdir " + p_ref;
        system(s_aux.c_str());
    }

    save_xml(report_xml, TGT, REF, METRIC, m);

    report_xml = TESTBED::replace_special_characters(report_xml);

    string command = Common::GZIP + " " + report_xml;
    string error = "Couldn't " + Common::GZIP + " " + report_xml;
    Common::execute_or_die(command, error);
}



/*void SC_ASIYA::read_xml(xmlNodePtr a_node, ofstream &out_txt, ofstream &out_idx, pair<string, FileInfo> &m, string id, string docid, string genre) {

    xmlNodePtr cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"DOC"))) {
            docid = string( (char*)xmlGetProp(cur_node, (const xmlChar*)"docid") );
            genre = string( (char*)xmlGetProp(cur_node, (const xmlChar*)"genre") );
        }
        else if ((!xmlStrcmp(cur_node->name, (const xmlChar *)"seg"))) {
            char* segid = (char*)xmlGetProp(cur_node, (const xmlChar*)"id");
            out_idx << docid << " " << genre << " " << id << " " << segid << endl;
            out_txt << cur_node->children->content << endl;

            vector<string> lidx(4);
            lidx[0] = docid;    lidx[1] = genre;    lidx[2] = id; lidx[3] = segid;
            //m[id].idx.push_back(lidx);
            m.second.idx.push_back(lidx);
        }
        process_xml(cur_node->children, out_txt, out_idx, m, id, docid, genre);
    }
}*/

void SC_ASIYA::read_report(string TGT, string REF, string METRIC, Scores &hOQ) {
    // description _ reads evaluation scores from a given XML report file onto memory.
    // param1  _ TARGET
    // param2  _ REFERENCE
    // param3  _ METRIC name
    // param4  _ metric scores (hash ref)
    // param5  _ set of segments (topics) (hash ref)
    // param6  _ level of granularity ('sys' for system; 'doc' for document; 'seg' for segment; 'all' for all)
    if (Config::G == Common::G_SYS) {
        if(hOQ.exists_sys_score(METRIC, TGT, REF)) return;
    }
    else if (Config::G == Common::G_DOC) {
        if (hOQ.exists_doc_score(METRIC, TGT, REF)) return;
    }
    else if (Config::G == Common::G_SEG) {
        if (hOQ.exists_seg_score(METRIC, TGT, REF)) return;
    }
    else if (Config::G == Common::G_ALL) {
        if (hOQ.exists_all_score(METRIC, TGT, REF)) return;
    }
    else { fprintf(stderr, "[ERROR] Unknown granularity <%s>\n", Config::G.c_str()); exit(1); }

    string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT+"/"+REF+"/"+METRIC+"."+Common::XMLEXT;
    string report_xml_gz = report_xml + "." + Common::GZEXT;

    boost::filesystem::path p (report_xml);
    boost::filesystem::path p_gz (report_xml_gz);

    srand(time(NULL));
    double nr = rand() % (Common::NRAND + 1);   //random number [0, Common::NRAND];
    string randomXML, randomXML2;

    if (exists(p) or exists(p_gz)) {
        if (Config::verbose) fprintf(stderr, "reading XML report <%s>\n", report_xml.c_str());

        if (!exists(p)) {
            string report_xml2 = TESTBED::replace_special_characters(report_xml);
            boost::filesystem::path p2 (report_xml2);

            double r = rand() % (Common::NRAND + 1);   //random number [0, Common::NRAND];
            stringstream ss, ss2;
            ss << Common::DATA_PATH << "/" << Common::TMP << "/" << p.filename().string() << "." << r;
            ss2 << Common::DATA_PATH << "/" << Common::TMP << "/" << p2.filename().string() << "." << r;
            randomXML = ss.str();
            randomXML2 = ss2.str();

            string sys_aux = Common::GUNZIP + " -c " + report_xml2+"."+Common::GZEXT + " > " + randomXML2;
            system(sys_aux.c_str());
        }

        xmlDocPtr doc;
        if (exists(p))
            doc = xmlReadFile(report_xml.c_str(), NULL, 0);
        else
            doc = xmlReadFile(randomXML.c_str(), NULL, 0);
        if (doc == NULL) { fprintf(stderr, "[ERROR] Failed to parse XML REPORT"); exit(1); }

        xmlNodePtr root_node = xmlDocGetRootElement(doc);
        string REPORT = string( (char*)root_node->children->next->name );

        if (Config::G == Common::G_SYS or Config::G == Common::G_ALL) { // system_score
            string score = string( (char*)xmlGetProp(root_node->children->next, (const xmlChar*)"score") );
            hOQ.set_sys_score(METRIC, TGT, REF, atof(score.c_str()));
        }
        if (Config::G == Common::G_DOC or Config::G == Common::G_SEG or Config::G == Common::G_ALL) {
            xmlNodePtr cur_node = root_node->children;
            int son = 0;
            while (cur_node != NULL) {
                cout << "son: " << ++son << "; type: " << cur_node->name << endl;
                cur_node = cur_node->next;
            }
            //read_xml(root_node, out_txt, out_idx, m, "source", "", "");
        }
        xmlFreeDoc(doc);
    }
}

void SC_ASIYA::save_struct_scores(const Scores &hOQ, string filename) {
    ofstream ofs(filename.c_str());
    boost::archive::text_oarchive oa(ofs);
    oa << hOQ;
}

void SC_ASIYA::load_struct_scores(Scores &hOQ, string filename) {
    ifstream ifs(filename.c_str());
    boost::archive::text_iarchive ia(ifs);
    ia >> hOQ;
}


/*
    while (i < idx.size()) {
        if (idx[i][0] != document_id) { // NEW DOCUMENT
            if (DOC != "-1") {
                double x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
                xmlNodePtr doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
                xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

                sprintf(buffer, "%d", n_docs);
                xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

                sprintf(buffer, "%d", n_doc_segs);
                xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

                sprintf(buffer, "%f", x);
                xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) buffer);
            }
            DOC = document_id = idx[i][0];
            n_docs++;
            n_doc_segs = 0;
        }

        // CREATE A SEGMENT
        xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "S", NULL);
        double x = Common::trunk_and_trim_number(seg_scores[i - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
        char buffer[50];
        sprintf(buffer, "%d", i);
        xmlNewProp(seg_node, BAD_CAST "n", (const xmlChar *) buffer);
        n_doc_segs++;
        i++;
    }

    // PASTE LAST DOC (if any)
    if (DOC != "-1") {
        double x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], SC_ASIYA::FLOAT_LENGTH, SC_ASIYA::FLOAT_PRECISION);
        doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
        xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

        sprintf(buffer, "%d", n_docs);
        xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

        sprintf(buffer, "%d", n_doc_segs);
        xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

        sprintf(buffer, "%f", x);
        xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) buffer);
    }*/

