/*
 * A fast version of EULER'S TOTIENT FUNCTION PHI(n).
 *
 * Copyright (c) 2012 Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the BSD 3-clause license; see the file LICENSE.
 *
 * For information on Euler's totient function, see
 *
 *     http://en.wikipedia.org/wiki/Euler%27s_totient_function
 *
 * This is an *EXTREMELY* fast function and uses several tricks to recurse.
 * It will need a fast prime number sieve (and vector) and a fast GCD.
 *
 */

#include <vector>
#include <inttypes.h>
#include "gcd.h"
#include "primes.h"

template<size_t PRIMES, typename INT>
INT phi(const INT& n)
{
  static prime_sieve<INT, PRIMES> primes;

  // Base case
  if ( n < 2 )
    return 0;

  // Lehmer's conjecture
  if ( primes.isprime(n) )
    return n-1;

  // Even number?
  if ( (n & 1) == 0 ) {
    int m = n / 2;

    return (m & 1) == 0 ?
      2*phi<PRIMES, INT>(m)
      : phi<PRIMES, INT>(m);
  }

  // For all primes ...
  for ( typename std::vector<INT>::const_iterator p = primes.first();
        p != primes.last() && *p <= n; ++p )
  {
    int m = *p;

    if ( n % m )
      continue;

    // phi is multiplicative
    int o = n/m;
    int d = binary_gcd<INT>(m, o);

    return d==1?
        phi<PRIMES, INT>(m) * phi<PRIMES, INT>(o)
      : phi<PRIMES, INT>(m) * phi<PRIMES, INT>(o) * d / phi<PRIMES, INT>(d);
  }

  // Should not happen
  assert(false);
  return 0;
}
