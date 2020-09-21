#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>

int main (int argc, char **argv)
{
  pid_t pid; // Holds pid from fork to determine child or parent

  int pr_count, pr_limit, opt;
  pr_count = 0; // Number of running children processes
  pr_limit = 0; // Limit of children allowed to run at once

  // TODO: Remove these testing variables and allow user to type in commands
  // to run, wait until they're done then start fork/exec-ing
  int pr_target = 20; // Number of processes to run in total

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

  // Get file input and build commands
  char buf[32];
  
  while(fgets(buf, 32, stdin))
  {
    printf("%s\n", buf);
  }

  for (int i = 0; i < pr_target; i++)
  {
    pid = fork();
   
    pr_count++; // Increment number of child processes running

    // If fork failed
    if (pid < 0)
    {
      perror("Fork failed - ");
      exit(1);
    }

    char* args[] = { "./testsim",
        "2",
        "3",
        NULL
    };
    
    // Child process
    if (pid == 0)
    {
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

  wait(NULL);

  return 1;
}
