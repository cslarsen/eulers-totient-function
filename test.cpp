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
  #define LIMIT 10000000
  cout << "Calculating " << 10*(LIMIT) << " prime numbers" << endl;

  for ( uint64_t n=0; n < LIMIT/10; n += 56789 ) {
    cout << "phi(" << n << ") = "
         << phi<LIMIT>(n) << endl;
  }

  for ( uint64_t n=1000000; n < LIMIT; n += 1122334/2 ) {
    cout << "phi(" << n << ") = "
         << phi<LIMIT>(n) << endl;
  }
}

int main()
{
  test1();
  test2();
  return 0;
}
