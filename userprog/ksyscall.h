/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"




void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

bool cmp(char A[], char B[])
{
  int i=0;
  bool bigger=false;
  bool hasAns=false;
  while(true)
  {
    if(A[i]=='\0') 
    {
      if(B[i]!='\0') return false;
      return hasAns && bigger;
    }
    else if(B[i]=='\0')
    {
      return true;
    }
    else if(A[i]!=B[i])
    {
      if(A[i]>B[i] && !hasAns)
      {
        bigger=true;
        hasAns=true;
      } 
      else if(A[i]<B[i] && !hasAns)
      {
        bigger=false;
        hasAns=true;
      }
    } 
    i++;
  }
  return false;
}

void SysPrintNumRecursion(int n, bool isNegative)
{
  if(n==0)
  {
    if(isNegative)
    {
      kernel->synchConsoleOut->PutChar('-');
      
    }
    return;
  }
  SysPrintNumRecursion(n/10, isNegative);
  int i=n%10;
  char t=(char)(i+'0');
  kernel->synchConsoleOut->PutChar(t);
}

void SysPrintNum(int n)
{
  bool isNegative=false;
  if(n==0)
  {
    kernel->synchConsoleOut->PutChar('0');
    return;
  }
  if(n<0)
  {
    isNegative=true;
    n=-n;
  }
  SysPrintNumRecursion(n, isNegative);
}

int inflate(char A[])
{
  int ans=0;
  int i=0;
  while(true)
  {
    if(A[i]=='\0') return ans;
    ans=ans*10+(A[i]-'0');
    i++;
  }
  return 0;
}

char* SysReadString(char* buffer, int length)
{
  int i=0;
  char oneChar;
  while(i<length)
  {
    oneChar=kernel->synchConsoleIn->GetChar();
    if(oneChar!='\n')
    {
      buffer[i]=oneChar;
      i++;
    }
    else
    {
      break;
    }
  }
  buffer[i]='\0';
  return buffer;
}

bool SysReadNum(int &ans)
{
  char IntMax[12]="2147483647\0";
  char IntMin[12]="2147483648\0";
  char buffer[1000];
  char oneChar;
  int i=0;
  int isNegative=0;
  while(i<1000)
  {
    oneChar=kernel->synchConsoleIn->GetChar();
    if(oneChar=='-' && i==0)
    {
      isNegative=1;
    }
    else if(oneChar>='0' && oneChar<='9')
    {
      buffer[i-isNegative]=oneChar;
    }
    else if(oneChar=='\n' || oneChar==' ')
    {
      break;
    }
    else
    {
      return false;
    }
    i++;
  }
  buffer[i-isNegative]='\0';
  if((isNegative==1 && cmp(buffer, IntMin)) || (isNegative==0 && cmp(buffer, IntMax)))
  {
    return false;
  }
  ans=inflate(buffer);
  if(isNegative==1)
  {
    ans=-ans;
  }
  return true;
  
}



void SysPrintString(char* buffer)
{
  int i=0;
  while(*(buffer+i)!='\0')
  {
    kernel->synchConsoleOut->PutChar(*(buffer+i));
    i++;
  }
  kernel->synchConsoleOut->PutChar('\n');
}






#endif /* ! __USERPROG_KSYSCALL_H__ */
