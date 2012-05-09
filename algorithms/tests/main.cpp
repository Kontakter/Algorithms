#ifdef DEBUG_OUTPUT
#include "debug_output.h"
#else
#define DEBUG(x)
#endif

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <memory.h>
#include <set>
#include <map>
#include <cstdio>
#include <cassert>
using namespace std;

#include "../number_theory.h"


// Enlarge MSVS stack size
#pragma comment(linker, "/STACK:16777216")

#define pb push_back
#define all(c) c.begin(), c.end()
#define mp(x, y) make_pair(x, y)
#define sz(x) static_cast<int>(x.size())
typedef long long int64;

template<class T> T sqr(const T& t) {return t * t;}
template<class T> T abs(const T& t) {return ((t > 0) ? (t) : (-t));}

void initialize()
{
    freopen("_.in", "r", stdin);
    freopen("_.out", "w", stdout);
}

int main()
{
    initialize();

    assert(mulModSmart(5, 5, 7) == 4);
    int res = 1;
    for (int i = 0; i < 10; ++i) {
        assert(pow(7ll, i) == res);
        assert(powMod(7ll, i, 11ll) == res % 11);
        assert(powModSmart(7ll, i, 11ll) == res % 11);
        res *= 7;
    }
    for (int i = 1; i <= 100; ++i) {
        assert(isPrime(i) == isPrimeSmart(i));
        if (i == 2 || i == 3 || i == 5 || i == 31) {
            assert(isPrime(i));
        }
    }
    assert(isPrimeSmart((int)1e9 + 7));
    assert(isPrimeSmart(2305843009213693951));
    assert(!isPrimeSmart(2305843009213693953));
    assert(!isPrimeSmart(2305843009213693957));
    assert(!isPrimeSmart((int)1e9 + 5));
    
    assert(primesList(10) == vector<int>({2, 3, 5, 7}));
    
    assert(factorize(22) == vector<PrimeFactor>({PrimeFactor(2, 1), PrimeFactor(11, 1)}));
    assert(factorize(27) == vector<PrimeFactor>({PrimeFactor(3, 3)}));
    
    assert(phi(9) == 6);

    PrimeField field(7);
    assert(field.generator() == 3);


    long long num = (long long)1e9;
    assert(isSqr(num * num));
    assert(!isSqr(num * num + 1));
    assert(isSqr((num + 3) * (num + 3)));
    
    return 0;
}
