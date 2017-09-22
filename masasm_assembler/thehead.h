/*

  MasAsm - written by Jared Bruni
  www.lostsidedead.com

  assembler, for the MAS bytecode

  written in the C programming language
  decided to change up my style for this one
  for practice


  About me

  My name is Jared Bruni, I am 18 years old
  and live in a suburb of sacramento called Elk Grove.
  All I want in my life, is to produce software,
  it is what drives me, it is my passion.
  I am looking possibly to relocate into a programming 
  position that can challenge me , with ethier C++, C, Java, Pascal, 
  or Assembly. (I would prefer C++)

  If you think you have a position that you think I could fill
  please email me at

  Master322@aol.com

  MASASM - what this is

  What this program does, is read in code written in mas. 
  Mas is a high level language, similar to basic
  and javascript. The difference is mas, can be executed
  from within a C++ program. This application can setup
  a table of function pointers, that the script can then
  call.


  Basic Overview of this applications algorithm in PCODE

  Start

  Read in Source File

  Translate Source

  Print Out Errors

  if no Error then

  output mve executable 

  end if

  Stop


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <malloc.h>
#include <stdarg.h>

#include "mcstr.h"

#define MASASM_VERSION 1
#define TYPE_NUMERIC   1
#define TYPE_STRING    2
#define TYPE_REAL      3
#define TYPE_NULL      0

// codeblock data structure
struct CodeBlock
{
	char *data; // draw script data
	char *cdata; // compiled data
	char name[100];// name of code block
};

// variables data structure
struct Variables
{
	char *data;
	char name[100];
	int type;
};

// program header structure
struct ProgramHeader
{
	char name[100];
	struct CodeBlock* blocks;
	struct Variables* var;
	int num;
	int vnum;
	int voff;
};


extern struct ProgramHeader prog;

// function prototypes
BOOL isfile(char *filename);
int  flen(const char *filename);
void readfile (const char *filename, char *data);
void trimr(char *source);
void trimcomments(char *in);
void lcase(char *source);
void killwspace(char *source);
void killline(char *source);
void trimquotes(char *source);
BOOL checkvname(char *name);
void codetrim(char* code);
void inctrim(char* code);
void encryptcode(char* code);
void decryptcode(char* code);
BOOL cmdcheck(char *code);
BOOL cmdcheckc(char c);
void nametrim(char *name);
int isins(char *ins);
BOOL ismaschar(char c);



