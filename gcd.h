/*
 * A fast BINARY GCD ALGORITHM using ITERATION and BIT SHIFTS.
 *
 * Copyright (c) 2012 Christian Stigen Larsen
 * http://csl.sublevel3.org
 *
 * Distributed under the BSD 3-clause license; see the file LICENSE.
 *
 */

template<typename INT>
INT binary_gcd(INT  u, INT  v)
{
  INT shl = 0;

  while ( u && v && u!=v ) {
    // even numbers?
    bool eu = (u & 1) == 0;
    bool ev = (v & 1) == 0;

    if ( eu && ev ) {
      ++shl;
      u /= 2;
      v /= 2;
    }
    else if ( eu && !ev ) u /= 2;
    else if ( !eu && ev ) v /= 2;
    else if ( u>=v ) u = (u-v)/2;
    else {
      INT tmp = u;
      u = (v-u)/2;
      v = tmp;
    }
  }

  return !u? v<<shl : u<<shl;
}
