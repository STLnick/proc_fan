#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <getopt.h>

#define PR_TARGET 20

void createArgs (char **args, char str[]);

int main (int argc, char **argv)
{
  pid_t pid; // Holds pid from fork to determine child or parent

  FILE *fp; // File pointer to read from inputs.data
  char command_str[12]; // Holds a line read from inputs.data
  char *args[3]; // Custom args array to exec built from command_str

  int pr_count, pr_limit, opt;
  pr_count = 0; // Number of running children processes
  pr_limit = 0; // Limit of children allowed to run at once

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

  // Open inputs.data file for command inputs
  fp = fopen("./inputs.data", "r");
  while (fgets(command_str, 13, fp) != NULL)
  {
    printf(":%s", command_str);
    createArgs(args, command_str);
    printf("%s, %s, %s\n", args[0], args[1], args[2]);
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

void createArgs (char **args, char str[])
{
  char delim[] = " ";
  int args_index = 0;

  char *ptr = strtok(str, delim);

  args[args_index] = ptr;

  args_index++;

  while (args_index < 3)
  {
    ptr = strtok(NULL, delim);
    args[args_index] = ptr;
    args_index++;
  }
  printf("createArgs called...");
}
