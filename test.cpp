/*
 * Some tests of Euler's Totient Function phi.
 *
 * Copyright (c) 2012 Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the BSD 3-clause license; see the file LICENSE.
 */

#include <iostream>
#include <inttypes.h>
#include <cassert>
#include "phi.h"

using namespace std;

void test1()
{
  int n = phi<100>(12);
  assert(n == 4);
}

void test2()
{
  #define LIMIT1 1000000
  cout << "Calculating " << 10*(LIMIT1) << " prime numbers" << endl;

  for ( uint64_t n=0; n < LIMIT1; n += 56789 ) {
    cout << "phi(" << n << ") = "
         << phi<10*LIMIT1>(n) << endl;
  }

  #define LIMIT2 10000000
  cout << endl;
  cout << "Calculating " << 10*(LIMIT2) << " prime numbers" << endl;

  for ( uint64_t n=1000000; n < LIMIT2; n += 1122334/2 ) {
    cout << "phi(" << n << ") = "
         << phi<10*LIMIT2>(n) << endl;
  }
}

int main()
{
  test1();
  test2();
  return 0;
}
