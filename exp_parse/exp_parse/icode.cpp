#include "icode.h"
#include<string.h>
int isize = 0;
Icode icode[max_size];
int offset = 0;

void Put(int token, int val, char *str) {

icode[offset].token = token;
icode[offset].val = val;
strncpy(icode[offset].str, str,256);
icode[offset++].str[strlen(str)] = 0;
isize++;

}