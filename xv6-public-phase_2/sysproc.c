#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Just introduce sys_waitx and call waitx in it.
int
sys_waitx(void)
{
  int* waiting_time;
  int* running_time;

  // To handle the error "‘waiting_time’ is used uninitialized in this function".
  if (argptr(0, (char**)&waiting_time, sizeof(int)) < 0)
    return -1;

  // To handle the error "‘running_time’ is used uninitialized in this function".
  if (argptr(1, (char**)&running_time, sizeof(int)) < 0)
    return -1;

  return waitx(waiting_time, running_time);
}

// Just introduce sys_set_priority and call set_priority in it.
int
sys_set_priority(void)
{
  int priority;

  // To handle the error "‘priority’ is used uninitialized in this function".
  if (argint(0, &priority) < 0)
    return -1;

  return set_priority(priority);
}
int
sys_nice(void)
{
  int decrement;

  // To handle the error "‘decrement’ is used uninitialized in this function".
  if (argint(0, &decrement) < 0)
    return -1;

  return nice(decrement);
}
