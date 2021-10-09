#include "syscall.h"

int
main()
{
  char space[2]=" ";
  int n=0, i, j, tmp;
  int A[101];
  n = ReadNum();
  if(n>100)
  {
      Halt();
  }
  for(i=0;i<n;i++)
  {
      A[i]=ReadNum();
  }
  for(i=0;i<n;i++)
  {
      for(j=0;j<n-i-1;j++)
      {
          if(A[j]>A[j+1])
          {
              tmp=A[j];
              A[j]=A[j+1];
              A[j+1]=tmp;
          }
      }
  }
  for(i=0;i<n;i++)
  {
      PrintNum(A[i]);
      PrintString(space);
  }
  Halt();
}