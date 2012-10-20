/*
 * A fast SIEVE OF ERATOSTHENES using BIT SETS and VECTOR to remember them.
 *
 * Copyright (c) 2012 Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the BSD 3-clause license; see the file LICENSE.
 *
 */

#include <vector>
#include <algorithm>
#include <bitset>
#include <inttypes.h>

template<typename INT = uint64_t, size_t PRIMES = 1000000>
class prime_sieve
{
public:
  std::bitset<PRIMES> p;
  std::vector<INT> v;

  prime_sieve()
  {
    rebuild();
  }

  void rebuild()
  {
    p.reset();
    p.flip();

    p[0] = p[1] = 1;

    for ( size_t n=2; n < PRIMES; ++n )
      if ( p[n] ) {
        v.push_back(n);

        for ( size_t m=n<<1; m < PRIMES; m += n )
          p[m] = 0;
      }
  }

  inline bool isprime(const INT& n) const
  {
    return p[n];
  }

  inline bool isprime_safe(const INT& n) const
  {
    return p.at(n);
  }

  inline size_t size() const
  {
    return v.size();
  }

  inline typename std::vector<INT>::const_iterator first() const
  {
    return v.begin();
  }

  inline typename std::vector<INT>::const_iterator last() const
  {
    return v.end();
  }

  inline typename std::vector<INT>::const_iterator find(const INT& n) const
  {
    return std::equal_range(v.begin(), v.end(), n).second;
  }
};
