#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
char ASCII_LOWER[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char ASCII_UPPER[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char rot_n(char param_1,int param_2)
{
  char *pcVar1;
  
  pcVar1 = strchr(ASCII_UPPER,(int)param_1);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = strchr(ASCII_LOWER,(int)param_1);
    if (pcVar1 != (char *)0x0) {
      param_1 = ASCII_LOWER[(param_1 + -0x61 + param_2) % 0x1a];
    }
  }
  else {
    param_1 = ASCII_UPPER[(param_1 + -0x41 + param_2) % 0x1a];
  }
  return param_1;
}

int is_prime(int param_1)
{
  int uVar1;
  double dVar2;
  int local_c;
  
  if (param_1 < 2) {
    uVar1 = 0;
  }
  else {
    local_c = 2;
    while (dVar2 = sqrt((double)param_1), local_c <= (int)dVar2) {
      if (param_1 % local_c == 0) {
        return 0;
      }
      local_c = local_c + 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}


//rot_n and is_prime are just copied functions from ghidra
int main()
{
    int check[] = {0x5f, 0x40, 0x5a, 0x15, 0x75, 0x45, 0x62, 0x53, 0x75, 0x46, 0x52, 0x43, 0x5f, 0x75, 0x50, 0x52, 0x75, 0x5f, 0x5c, 0x4f};
    for(int i=0;i<sizeof(check)/sizeof(check[0]);i++)
        check[i]^=42;
        
    int counter = 0x1c-7;
    while(counter-->=0){
        int rot_number = counter*4;
        while(!is_prime(rot_number))rot_number+=1;
        check[counter] = rot_n((char)check[counter], 26-(rot_number%26));
    }
    
    cout<<"corctf{";
    for(int i=0;i<sizeof(check)/sizeof(check[0]);i++)
        cout<<(char)check[i];
    cout<<"}";
    return 0;
}
