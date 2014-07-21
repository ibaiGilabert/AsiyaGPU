/* system example : DIR */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
using namespace std;

int main ()
{
  int i;
  printf ("Checking if processor is available...");
  if (system(NULL)) puts ("Ok");
    else exit (EXIT_FAILURE);
  printf ("Executing command DIR...\n");
  i=system ("ls");
  if (i) printf("MERDA\n");
  else printf("ALL RIGHT\n");
  printf ("The value returned was: %d.\n",i);

  boost::filesystem::path pathname ("/home/ibai/Escriptori/AsiyaGPU/sandbox/boost_ip.cc");
  string dirname = pathname.parent_path().string();
  string basename = pathname.filename().string();

  cout << "dirname: " << dirname << endl;
  cout << "pathname: " << pathname << endl;
}