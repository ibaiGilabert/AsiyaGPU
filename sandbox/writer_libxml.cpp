#include <stdio.h>
#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main(int argc, char **argv)
{
    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
    xmlDtdPtr dtd = NULL;       /* DTD pointer */

    xmlAttrPtr new_attr = NULL;
    xmlNodePtr new_node = NULL;

    char buff[256];
    int i, j;

    LIBXML_TEST_VERSION;


    //print $OUT "<?xml version=\"1.0\"?>\n";                  # print the XML declaration
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST "Powersettings");
    xmlDocSetRootElement(doc, root_node);

    xmlNewChild(root_node, NULL, BAD_CAST "PowerScheme", BAD_CAST "Testing");
    xmlNewChild(root_node, NULL, BAD_CAST "cpuspeed", BAD_CAST "Adaptive");

    new_attr = xmlNewProp(root_node, (const xmlChar *)"uri", (const xmlChar *)"puta");

    xmlNewChild(root_node, NULL, BAD_CAST "LockScreentime", BAD_CAST "no");

    xmlNewChild(root_node, NULL, BAD_CAST "Wbrightvalue", BAD_CAST "no");
    xmlNewChild(root_node, NULL, BAD_CAST "Ibrightvalue", BAD_CAST "no");
    xmlNewChild(root_node, NULL, BAD_CAST "Dimtime", BAD_CAST "no");

    /* Dumping document to stdio or file */
    xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);

    xmlFreeDoc(doc);
    xmlCleanupParser();
}
