

#include "syscall.h"

int
main()
{
  int result;
  
  char buffer[100];
  int length=10;

  ReadString(buffer, length);
  PrintString(buffer);

  Halt();
  /* not reached */
}
