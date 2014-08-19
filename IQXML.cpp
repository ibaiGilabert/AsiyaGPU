#include "IQXML.hpp"
#include "Common.hpp"
#include "Config.hpp"

#include <sstream>

#include <boost/filesystem.hpp>

#include <libxml/parser.h>
#include <libxml/tree.h>

const int IQXML::FLOAT_LENGTH = 10;
const int IQXML::FLOAT_PRECISION = 8;
const string IQXML::ROOT_ELEMENT = "REPORT";


void save_xml(string report_xml, string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores) {

    vector<vector<string> > idx = Config::IDX[TGT];

   //FALTA "!DOCTYPE ..."
    int i = 1;
    int n_docs, n_doc_segs;
    n_docs = n_doc_segs = 0;

    string DOC = "-1";
    string document_id = "";

    // -> STORE IQREPORT
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "REPORT");
    xmlDocSetRootElement(doc, root_node);

    xmlNewProp(root_node, BAD_CAST "hyp",       BAD_CAST    TGT.c_str());
    xmlNewProp(root_node, BAD_CAST "metric",    BAD_CAST    METRIC.c_str());

    char buffer[50];
    sprintf(buffer, "%d", n_docs);
    xmlNewProp(root_node, BAD_CAST "n_docs",    (const xmlChar *) buffer);

    sprintf(buffer, "%d", seg_scores.size());
    xmlNewProp(root_node, BAD_CAST "n_segments",(const xmlChar *) buffer);
    xmlNewProp(root_node, BAD_CAST "ref",       BAD_CAST    REF.c_str());

    double x = Common::trunk_and_trim_number(sys_score, IQXML::FLOAT_LENGTH, IQXML::FLOAT_PRECISION);
    sprintf(buffer, "%f", x);
    xmlNewProp(root_node, BAD_CAST "score",     (const xmlChar *) buffer);

    xmlNodePtr doc_node;

    while (i < idx.size()) {
        if (idx[i][0] == document_id) { // NEW DOCUMENT
            if (DOC != "-1") {
                double x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], IQXML::FLOAT_LENGTH, IQXML::FLOAT_PRECISION);
                    doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
                    xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

                    sprintf(buffer, "%d", n_docs);
                    xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

                    sprintf(buffer, "%d", n_doc_segs);
                    xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

                    sprintf(buffer, "%f", x);
                    xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) buffer);
            }
            document_id = idx[i][0];
            n_docs++;
            n_doc_segs = 0;
        }

        // CREATE A SEGMENT
        xmlNodePtr seg_node = xmlNewChild(doc_node, NULL, BAD_CAST "S", NULL);
        double x = Common::trunk_and_trim_number(seg_scores[i - 1], IQXML::FLOAT_LENGTH, IQXML::FLOAT_PRECISION);
        char buffer[50];
        sprintf(buffer, "%d", i);
        xmlNewProp(seg_node, BAD_CAST "n", (const xmlChar *) buffer);
        n_doc_segs++;
        i++;
    }

    // PASTE LAST DOC (if any)
    if (DOC != "-1") {
        double x = Common::trunk_and_trim_number(doc_scores[n_docs - 1], IQXML::FLOAT_LENGTH, IQXML::FLOAT_PRECISION);
        doc_node = xmlNewChild(root_node, NULL, BAD_CAST "DOC", NULL);
        xmlNewProp(doc_node, BAD_CAST "id",         BAD_CAST document_id.c_str());

        sprintf(buffer, "%d", n_docs);
        xmlNewProp(doc_node, BAD_CAST "n",          (const xmlChar *) buffer);

        sprintf(buffer, "%d", n_doc_segs);
        xmlNewProp(doc_node, BAD_CAST "n_segments", (const xmlChar *) buffer);

        sprintf(buffer, "%f", x);
        xmlNewProp(doc_node, BAD_CAST "score",      (const xmlChar *) buffer);
    }

    xmlSaveFormatFileEnc(report_xml.c_str(), doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}


void IQXML::write_report(string TGT, string REF, string METRIC, double sys_score, const vector<double> &doc_scores, const vector<double> &seg_scores){
    // description _ writes evaluation scores onto a given XML report file
    //stringstream r_xml;
    string report_xml = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT +"/"+REF+METRIC+"."+Common::XMLEXT;

    if (Config::verbose > 1) printf("writing XML REPORT <%s>\n", report_xml.c_str());

    string p_aux = Common::DATA_PATH+"/"+Common::REPORTS;
    string p_tgt = Common::DATA_PATH+"/"+Common::REPORTS+"/"+TGT;
    string p_ref = Common::DATA_PATH+"/"+Common::REPORTS;+"/"+TGT+"/"+REF;

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

    save_xml(report_xml, TGT, REF, METRIC, sys_score, doc_scores, seg_scores);

    Common::replace_special_characters(report_xml);

    string command = Common::GZIP + " " + report_xml;
    string error = "Couldn't " + Common::GZIP + " " + report_xml;
    Common::execute_or_die(command, error);
}