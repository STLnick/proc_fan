#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>

int main (int argc, char **argv)
{
  pid_t pid;
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

  pid = fork();
  // If fork failed
  if (pid < 0)
  {
    perror("Fork failed - ");
    exit(1);
  }
  // Child process
  if (pid == 0)
  {
    char* args[] = { "./testsim", "1", "2", NULL};
    execv(args[0], args);
  }

  wait(NULL);
  printf("Parent waited for child");

  return 1;
}
