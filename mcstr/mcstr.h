/*

  Mcstr.h written by Jared Bruni

  (Master C style String Manipulation)

  www.lostsidedead.com

*/

#ifndef MCSTR 
#define MCSTR

#define NULLPOS -1
#define FAIL -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>

int findstr(const char *string, const char *search);// find string
int bfindstr(const char *string, const char *search);// backwards find string
int ifindstr(int start, const char *string, const char *search);// in find string
int ibfindstr(int start, const char *string, const char *search);// in backwards find string
void leftcopy(const char *in, char *out, int pos);// left copy
void rightcopy(const char *in, char *out, int pos);// right copy
void midcopy(const char *in, char *out, int start, int stop);// mid copy
void killspace(char *str);// kill space
int  findoccourance( const char *str, char c);// find occourance
BOOL ishexc(char c);// is this a hex character?
BOOL ishex(char *data);// does this string only contain hex digits?
int hextointc(char c); // translate this character, into its integer equilvanet
int  hextoint(char *data); // translate this string of hex characters, into a integer
BOOL iop(char *data); // do illegal characters exisit within this string
BOOL iopc(char c); // illegal character?
BOOL isnumeric(char *numeric); // is this a numeric string?
#endif