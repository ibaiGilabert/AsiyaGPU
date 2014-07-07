#include <iostream>
#include <getopt.h>

#define no_argument 0
#define required_argument 1 
#define optional_argument 2


int main(int argc, char * argv[])
{
  std::cout << "Hello" << std::endl;

  const struct option long_opts[] =
  {
    {"version",     no_argument,        0, 'v'},
    {"help",        no_argument,        0, 'h'},
    {"metric_set",  required_argument,  0, 'm'},
    {"eval",        required_argument,  0, 'e'},
    {0,0,0,0},
  };

  int index;
  int iarg=0;

  //turn off getopt error message
  opterr=1; 

  while(iarg != -1)
  {
    iarg = getopt_long_only(argc, argv, "e:m:h", long_opts, &index);

    switch (iarg)
    {
      case 'e':
        std::cout << "You hit eval" << std::endl;
        break;

      case 'm':
        std::cout << "You hit metric_set: " << optarg << std::endl;
        break;

      case 'h':
        std::cout << "You hit help" << std::endl;
        break;
    }
  }

  std::cout << "GoodBye!" << std::endl;

  return 0; 
}