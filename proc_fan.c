#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>

#define PR_TARGET 20

int main (int argc, char **argv)
{
  pid_t pid;
  int nfound, pr_count, pr_limit, opt;
  pr_count = 0;
  pr_limit = 0;

  // Parse command line to ensure n-flag was used and store value of n passed
  while ((opt = getopt(argc, argv, "n:")) != -1)
  {
    switch (opt)
    {
    case 'n':
      pr_limit = atoi(optarg);
      break;
    }
  }

  // If no n-flag was used error out
  if (pr_limit == 0)
  {
    perror("Error: No -n flag was used to specify the limit of processes");
    return -1;
  }

  // If n was specified as greater than 20 error out
  if (pr_limit > 20)
  {
    perror("Error: Limit of process was specified was too large");
    return -1;
  }
  
  for (int i = 0; i < PR_TARGET; i++)
  {
    pid = fork();
   
    pr_count++;
    printf("PROCESSES RUNNING: %i\n", pr_count);

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

    // Parent process
    if (pr_count == pr_limit)
    {
      wait();
      pr_count--;
      printf("Parent waited for child...\n");
    }
  }

  return 1;
}
