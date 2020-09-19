#include <stdio.h>

int main(int argc, char **argv)
{
  // If there were argument supplied to program print them out
  if (argc > 1)
  {
    for (int i = 1; i < argc; i++)
    {
      printf("%s ", argv[i]);
    }
    printf("\n");
  }

  return 1;
}
