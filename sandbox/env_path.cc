#include <stdlib.h>     /* getenv */
#include <iostream>
using namespace std;

int main ()
{
	char* path = getenv("PUTA");
	if (path) cout << "path: " << path << endl;
	else {
		cout << "res de res" << endl;
		exit(EXIT_FAILURE);
	}

/*  char* pPath;
  pPath = getenv ("PATH");
  if (pPath!=NULL)
    printf ("The current path is: %s",pPath);
  return 0;
*/}