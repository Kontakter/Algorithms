// {{{ GCD

long long gcd(long long a, long long b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long gcdWide(long long a, long long b, long long& u, long long& v) {
    if (a == 0) {
        u = 0; v = 1;
        return b;
    }
    long long oldU, oldV;
    long long d = gcdWide(b % a, a, oldU, oldV);
    u = oldV - (b / a) * oldU;
    v = oldU;
    return d;
}

// }}} 

// {{{ Pow

long long pow(long long a, long long d) {
    long long b = a;
    long long res = 1;
    while (d > 0) {
        if ((d & 1) > 0) {
            res *= b;
        }
        b *= b;
        d >>= 1;
    }
    return res;
}

long long powMod(long long a, long long d, long long mod) {
    long long b = a % mod;
    long long res = 1 % mod;
    while (d > 0) {
        if ((d & 1) > 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        d >>= 1;
    }
    return res;
}

long long mulModSmart(long long a, long long b, long long mod) {
    long long res = 0;
    long long cur = a;
    while (b > 0) {
        if ((b & 1) > 0) {
            res = res + cur;
            if (res >= mod) res -= mod;
        }
        cur <<= 1;
        if (cur >= mod) cur -= mod;
        b >>= 1;
    }
    return res;
}

long long powModSmart(long long a, long long d, long long mod) {
    long long b = a % mod;
    long long res = 1 % mod;
    while (d > 0) {
        if ((d & 1) > 0) {
            res = mulModSmart(res, b, mod);
        }
        b = mulModSmart(b, b, mod);
        d >>= 1;
    }
    return res;
}

// }}}

// {{{ Primes

bool isPrime(long long num) {
    if (num == 1) return false;
    for (long long x = 2; x * x <= num; ++x) {
        if (num % x == 0) return false;
    }
    return true;
}

// Fast version by Miller-Rabin algorithm
bool isPrimeSmart(long long num, int iter = 100) {
    if (num == 2) {
        return true;
    }
    if (num < 2 || num % 2 == 0) {
        return false;
    }
        
    long long phi = num - 1;
    int pow2 = 0;
    while (phi % 2 == 0) {
        pow2 += 1;
        phi /= 2;
    }

    for (int i = 0; i < iter; ++i) {
        long long witness = max(rand() % num, 2ll);
        if (gcd(num, witness) > 1) return false;

        long long x = powModSmart(witness, phi, num);
        for (int j = 0; j < pow2; ++j) {
            long long prevX = x;
            // Improve by TLong
            x = mulModSmart(x, x, num);
            if (x == 1 && prevX != 1 && prevX != num - 1) {
                return false;
            }
        }
        if (x != 1) return false;
    }
    return true;
}

vector<bool> primesIndicator(int count) {
    vector<bool> res(count + 1, true);
    res[0] = res[1] = false;
    for (int i = 2; i <= count; ++i) {
        if (res[i]) {
            for (int j = i + i; j <= count; j += i) {
                res[j] = false;
            }
        }
    }
    return res;
}

vector<int> primesList(int count) {
    vector<bool> res(count + 1, true);
    vector<int> list;
    res[0] = res[1] = false;
    for (int i = 2; i <= count; ++i) {
        if (res[i]) {
            list.push_back(i);
            for (int j = i + i; j <= count; j += i) {
                res[j] = false;
            }
        }
    }
    return list;
}

// }}}

// {{{ Factorization
struct PrimeFactor {
    PrimeFactor(long long number_, int power_): number(number_), power(power_)
    { }
    long long number;
    int power;
};

bool operator == (const PrimeFactor& lhs, const PrimeFactor& rhs) {
    return (lhs.number == rhs.number) && (lhs.power == rhs.power);
}

vector<PrimeFactor> factorize(long long num) {
    vector<PrimeFactor> factors;
    for (long long factor = 2; factor * factor <= num; ++factor) {
        if (num % factor == 0) {
            PrimeFactor f(factor, 0);
            while (num % factor == 0) {
                num /= factor;
                f.power += 1;
            }
            factors.push_back(f);
        }
    }
    if (num != 1) {
        factors.push_back(PrimeFactor(num, 1));
    }
    return factors;
}

vector<PrimeFactor> factorizePollard(long long num) {
    assert(false);
}

// }}}

// {{{ Field calculus
long long phi(const vector<PrimeFactor>& factors) {
    long long res = 1;
    for (const auto& factor: factors) {
        for (int i = 0; i < factor.power; ++i) {
            if (i == 0) res *= factor.number - 1;
            else res *= factor.number;
        }
    }
    return res;
}

long long phi(long long num) {
    return phi(factorize(num));
}

class PrimeField {
public:
    explicit PrimeField(long long mod): mod_(mod)
    { assert(isPrimeSmart(mod_)); }

    long long pow(long long a, long long d) { return powMod(a, d, mod_); }

    long long reciprocal(long long num) {return pow(num, mod_ - 2); }

    long long generator()
    {
        auto factors = factorize(mod_ - 1);
        for (long long num = 2; num < mod_; num += 1) {
            if (none_of(factors.begin(), factors.end(),
                [&] (const PrimeFactor& factor) {return pow(num, (mod_ - 1) / factor.number) == 1; }))
            {
                return num;
            }
        }
        assert(false);
        return -1;
    }

private:
    long long mod_;
};

// }}}

// {{{ IsSqr
bool isSqr(long long num) {
    long long d = (long long)sqrt(double(num)) - 10;
    for (long long a = 0; a < 20; ++a) {
        if (d * d == num) return true;
        d += 1;
    }
    return false;
}
// }}}
