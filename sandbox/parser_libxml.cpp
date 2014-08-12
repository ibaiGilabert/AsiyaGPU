#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

static void print_element_names(xmlNode * a_node);

int main() {
  xmlDoc         *doc = NULL;           //Document pointer
  xmlNode        *root_element = NULL;  //Node pointer
  const char     *Filename = "sp1.xml"; //

  doc = xmlReadFile(Filename, NULL, 0);

  if (doc == NULL) printf("error: could not parse file %s\n", Filename);
  else {
    /* Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);

    /* free the document */
    xmlFreeDoc(doc);;
  }
  /* Free the global variables that may have been allocated by the parser.*/
  xmlCleanupParser();
}

/* Recursive function that prints the XML structure */
static void print_element_names(xmlNode * a_node) {
  xmlNode *cur_node = NULL;

  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE)
      printf("node type: Element, name: %s\n", cur_node->name);
    print_element_names(cur_node->children);
  }
}