/*
 * Some tests of Euler's Totient Function phi.
 *
 * Copyright (c) 2012 Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the BSD 3-clause license; see the file LICENSE.
 */

#include <iostream>
#include <iomanip>
#include <inttypes.h>
#include <cassert>
#include "phi.h"

using namespace std;

/*
 * Count test cases
 */
int fail = 0;
int good = 0;

template<size_t PRIMES, typename INT>
void test(const INT& n, const INT& expected)
{
  INT actual = phi<PRIMES>(n);
  bool ok = (expected == actual);
  ++(ok? good : fail);
  cout << (fail+good) << " "
       << (ok? "OK: " : "FAIL:") << " "
       << "phi(" << n << ") ==> " << actual;

  if ( !ok )
    cout << " != " << expected;

  cout << endl;
}

/*
 * Assert that the phi function is correct for some known cases.  Check that
 * we are able to calculate phi even though the prime sieve is much less
 * than the square root of the number we are calculating phi for.
 */
void test1()
{
  test<100>(12, 4);
  test<10>(12, 4);
  test<3>(12, 4);

  test<10>(1234, 616);
  test<10>(12345, 6576);
  test<10>(123456, 41088);
  test<10>(1234567, 1224720);
  test<10>(12345678, 4027392);
  test<10>(123456789, 82260072);
  test<10>(1234567890, 329040288);

  test<100>(1234, 616);
  test<100>(12345, 6576);
  test<100>(123456, 41088);
  test<100>(1234567, 1224720);
  test<100>(12345678, 4027392);
  test<100>(123456789, 82260072);
  test<100>(1234567890, 329040288);

  test<1000>(1234, 616);
  test<1000>(12345, 6576);
  test<1000>(123456, 41088);
  test<1000>(1234567, 1224720);
  test<1000>(12345678, 4027392);
  test<1000>(123456789, 82260072);
  test<1000>(1234567890, 329040288);

  test<10000>(1234, 616);
  test<10000>(12345, 6576);
  test<10000>(123456, 41088);
  test<10000>(1234567, 1224720);
  test<10000>(12345678, 4027392);
  test<10000>(123456789, 82260072);
  test<10000>(1234567890, 329040288);

  test<100000>(1234, 616);
  test<100000>(12345, 6576);
  test<100000>(123456, 41088);
  test<100000>(1234567, 1224720);
  test<100000>(12345678, 4027392);
  test<100000>(123456789, 82260072);
  test<100000>(1234567890, 329040288);

  test<1000000>(1234, 616);
  test<1000000>(12345, 6576);
  test<1000000>(123456, 41088);
  test<1000000>(1234567, 1224720);
  test<1000000>(12345678, 4027392);
  test<1000000>(123456789, 82260072);
  test<1000000>(1234567890, 329040288);

  test<10000000>(1234, 616);
  test<10000000>(12345, 6576);
  test<10000000>(123456, 41088);
  test<10000000>(1234567, 1224720);
  test<10000000>(12345678, 4027392);
  test<10000000>(123456789, 82260072);
  test<10000000>(1234567890, 329040288);

  // Test a really large number
  test<1000000>(12345678901234567890U, 3256788124177920000U);
}

/*
 * The purpose of this test is to check that we can calculate phi for
 * relatively large numbers.
 */
void test2()
{
  #define LIMIT 10000000
  cout << "Calculating all primes below " << LIMIT << endl;

  for ( uint64_t n=0; n < LIMIT/10; n += 56789 ) {
    cout << "phi(" << n << ") = "
         << phi<LIMIT>(n) << endl;
  }

  for ( uint64_t n=1000000; n < LIMIT; n += 1122334/2 ) {
    cout << "phi(" << n << ") = "
         << phi<LIMIT>(n) << endl;
  }
}

/*
 * The purpose of this test is to check that we can make do with a smaller
 * prime set than the numbers we want to calculate phi for.
 */
void test3()
{
  for ( int i=100-11-11; i<1000; i += 11 ) {
    cout << "phi(" << setw(3) << i << ")=" << setw(3) << phi<100>(i) << "   ";
    if ( (i % 3) == 1 )
      cout << endl;
  }
}

int main()
{
  test2();
  test3();
  test1();
  return 0;
}
