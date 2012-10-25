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
#include <math.h>
#include "gcd.h"
#include "primes.h"
#include <iostream>

template<typename INT>
static bool less(const INT& n, const size_t& primes)
{
  return sizeof(n) < sizeof(size_t)?
    static_cast<size_t>(n) <= primes :
    n <= static_cast<INT>(primes);
}

template<size_t PRIMES, typename INT>
INT phi(const INT& n)
{
  static prime_sieve<INT, PRIMES> primes;

  // Negative numbers
  if ( n < 0 )
    return phi<PRIMES, INT>(-n);

  // By definition
  if ( n == 1 )
    return 1;

  // Base case
  if ( n < 2 )
    return 0;

  // Lehmer's conjecture
  if ( less(n, primes.size()) && primes.isprime(n) )
    return n-1;

  // Even number?
  if ( (n & 1) == 0 ) {
    INT m = n / 2;
    return (m & 1) == 0 ?
      2*phi<PRIMES, INT>(m)
      : phi<PRIMES, INT>(m);
  }

  // For all primes less than n ...
  const INT sqrt_n = 1+sqrt(n);
  for ( typename std::vector<INT>::const_iterator p = primes.first();
        p != primes.last() && *p <= sqrt_n; ++p )
  {
    INT m = *p;

    // Is m not a factor?
    if ( (n % m) != 0 )
      continue;

    // Phi is multiplicative
    INT o = n/m;
    INT d = binary_gcd<INT>(m, o);

    return d==1?
        phi<PRIMES, INT>(m) * phi<PRIMES, INT>(o)
      : phi<PRIMES, INT>(m) * phi<PRIMES, INT>(o) * d / phi<PRIMES, INT>(d);
  }

  // Find out if n is really prime
  INT p;
  for ( p=2+*(primes.last()-1); p < n && (n % p) != 0; p += 2 )
    ; // loop

  // If n is prime, use Lehmer's conjecture
  if ( p >= n )
    return n-1;

  // n must be composite, so divide up and recurse
  INT o = n/p;
  INT d = binary_gcd<INT>(p, o);

  return d==1?
      phi<PRIMES, INT>(p) * phi<PRIMES, INT>(o)
    : phi<PRIMES, INT>(p) * phi<PRIMES, INT>(o) * d / phi<PRIMES, INT>(d);
}
