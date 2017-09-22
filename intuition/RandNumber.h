#ifndef _STDIO_H_
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#endif

typedef unsigned long uint32;            // 32 bit unsigned integer

class TMotherRandomGenerator {           // encapsulate random number generator
  public:
  void RandomInit(uint32 seed);          // initialization
  void SetInterval(int min, int max);    // set interval for iRandom
  int iRandom();                         // get integer random number
  double Random();                       // get floating point random number
  TMotherRandomGenerator(uint32 seed=-1);// constructor
  protected:
  double x[5];                           // history buffer
  int imin, iinterval;                   // interval for iRandom
  };


// constructor:
TMotherRandomGenerator::TMotherRandomGenerator(uint32 seed) {
  // check that compiler supports 80-bit long double
  assert(sizeof(long double)>9);
  // initialize
  RandomInit(seed);  SetInterval(0, 99);}


// set interval for iRandom:
void TMotherRandomGenerator::SetInterval(int min, int max) {
  imin = min; iinterval = max - min + 1;}


// returns a random number between 0 and 1:
double TMotherRandomGenerator::Random() {
  long double c;
  c = 2111111111.0 * x[3] +
      1492.0 * (x[3] = x[2]) +
      1776.0 * (x[2] = x[1]) +
      5115.0 * (x[1] = x[0]) +
      x[4];
  x[4] = floorl(c);
  x[0] = c - x[4];
  x[4] = x[4] * (1./(65536.*65536.));
  return x[0];}


// returns integer random number in desired interval:
int TMotherRandomGenerator::iRandom() {
  int i = iinterval * Random();
  if (i >= iinterval) i = iinterval;
  return imin + i;}


// this function initializes the random number generator:
void TMotherRandomGenerator::RandomInit (uint32 seed) {
  int i;
  // make sure seed != 0
  if (seed==0) seed = -1;

  // make random numbers and put them into the buffer
  for (i=0; i<5; i++) {
    seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
    x[i] = seed * (1./(65536.*65536.));}
  // randomize some more
  for (i=0; i<19; i++) Random();}