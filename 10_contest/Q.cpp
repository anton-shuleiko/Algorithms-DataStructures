#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <algorithm>

using complex = std::complex<long double>;
using std::vector;
using ll = long long;

const long double pi = acos(-1);

void FFT(std::vector<complex>& polinom, bool invert = false) {
    int sz = polinom.size();
    if (sz == 1) return;
 
    std::vector<complex> p1(sz / 2);
    std::vector<complex> p2(sz / 2);
    for (int i = 0, j = 0; i < sz; ++j, i += 2) {
        p1[j] = polinom[i];
        p2[j] = polinom[i + 1];
    }
 
    FFT(p1, invert);
    FFT(p2, invert);
 
    long double ang = 2 * std::acos(-1) / sz * (invert ? -1 : 1);
    complex pr_root(cos(ang), sin(ang));
    complex x(1);
    for (int i = 0; i < sz / 2; ++i) {
        polinom[i] = p1[i] + p2[i] * x;
        polinom[i + sz / 2] = p1[i] - p2[i] * x;
        if (invert) {
            polinom[i] /= 2;
            polinom[i + sz / 2] /= 2;
        }
        x *= pr_root;
    }
}

void mul(std::vector<complex>& p1, std::vector<complex>& p2, vector<ll>& res) {
    int n = 1;
    while (n < p1.size() || n < p2.size()) n *= 2;
    n *= 2;
 
    p1.resize(n, 0);
    p2.resize(n, 0);
 
    FFT(p1);
    FFT(p2);
 
    for (int i = 0; i < n; ++i) {
        p1[i] *= p2[i];
    }
    FFT(p1, true);

    res.resize(n);
    for (int i = 0; i < n; ++i) {
        res[i] = round(p1[i].real());
    }
}

int main() {
    int n;
    std::cin >> n;
    
    std::string m;
    std::cin >> m;
    int k;
    std::cin >> k;
    ll q = 1;
    ll x = 0;
    for (int i = 0; i < m.length(); ++i) {
        x += ((m[m.length()-i-1]-'0')*q);
        q*=n;
    }
    ll result = 0;
    ll r = 1;
    int reminder = 0;
    while(x > 0){
        result += (x%k)*r;
        r*=10;
        x/=k;
    }
    std::cout << result;
    return 0;
}