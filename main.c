#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  int nfound, ncount, opt;
  nfound = 0;
  ncount = 0;

  // Parse command line to ensure n-flag was used and store value of n passed
  while ((opt = getopt(argc, argv, "n:")) != -1)
  {
    switch (opt)
    {
    case 'n':
      nfound = 1;
      ncount = atoi(optarg);
      break;
    }
  }

  // If no n-flag was used error out
  if (nfound == 0)
  {
    perror("Error: ");
    return -1;
  }

  // If n was specified as greater than 20 error out
  if (ncount > 20)
  {
    perror("Error: ");
    return -1;
  }

  printf("nfound: %d // ncount: %d", nfound, ncount);

  return 1;
}
