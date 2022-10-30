#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

// Program that test waitx system call.
int main(int argc, char* argv[])
{
  int pid, waitx_result, waiting_time, running_time;
  waitx_result = -1;
  pid = fork();
  if (pid == 0)
  {
    // Child Process.
    sleep(5);   // Sleep to increase waiting_time.
    exit();
  }
  else
    // Parent Process.
    waitx_result = waitx(&waiting_time, &running_time);

  // Print waiting_time, running_time and waitx_result...
  // in a beautiful box.
  printf(1, "#######################\n");
  printf(1, "##  Wait Time: %d     ##\n", waiting_time);
  printf(1, "##  Run Time: %d      ##\n", running_time);
  printf(1, "##  Waitx Result: %d  ##\n", waitx_result);
  printf(1, "#######################\n");
  exit();
}
