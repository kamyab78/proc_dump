#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

// Arbitrary function which takes a time.
void heavy_func(int n)
{
  int temp = 1;
  while (n != 0)
  {
    temp *= n;
    n--;
  }
  n = temp;
}

// Program that test set_priority system call.
int main(int argc, char* argv[])
{
  int pid;
  pid = fork();
  if (pid == 0)
  {
    // Child Process.
    set_priority(70);
    heavy_func(100); // Takes less time.
    printf(1, "%s\n", "child"); // Print second.
    sleep(5);
    exit();
  }
  else
  {
    // Parent Process.
    set_priority(30);
    heavy_func(1000000); // Takes more time.
    printf(1, "%s\n", "parent"); // Print first.
    sleep(5);
    exit();
  }
}
