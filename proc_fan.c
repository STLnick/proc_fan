#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <unistd.h>

void createargs(char **args, char *str);

int main (int argc, char **argv)
{
  pid_t pid; // Holds pid from fork to determine child or parent

  int pr_count, pr_limit, opt, status;
  pr_count = 0; // Number of running children processes
  pr_limit = 0; // Limit of processes to run concurrently

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
    pid = fork();
   
    pr_count++; // Increment number of child processes running

    // If fork failed
    if (pid < 0)
    {
      perror("Fork failed - ");
      exit(1);
    }

    char *args[3];
    createargs(args, buf);
   
    // Child process
    if (pid == 0)
    {
      execv(args[0], args);
      perror("Child failed to exec command!");
    }

    // Parent process
    if (pr_count == pr_limit)
    {
      wait(&status);
      pr_count--;
      printf("Parent waited for child...\n");
    }
  }

  // Wait for remaining children processes to finish
  wait(NULL);

  return 0;
}

void createargs(char **args, char *str)
{
  char delim[] = " "; // Separate strings by spaces
  int args_index = 0; // Index to build custom args

  char *ptr = strtok(str, delim);

  args[args_index] = ptr;

  args_index++;

  while ((ptr = strtok(NULL, delim)) != NULL)
  {
    args[args_index] = ptr;
    args_index++;
  }
  args[args_index] = '\0'; // Explicitly add null terminator to end of new args array
}
