#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>
#include <string>


const int maxn = (1 << 18);
const long double pi = acos(-1);

std::complex<long double> roots[maxn];
int rev[maxn];

void Furye(std::vector<std::complex<long double>>& a)
{
    int n = a.size();
    for (int i = 0; i < n; ++i)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (int len = 1, step = n / 2; len < n; len <<= 1, step >>= 1)
        for (int st = 0; st < n; st += len + len)
            for (int i = 0, root = 0; i < len; ++i, root += step)
            {
                std::complex<long double> u = a[st + i], v = roots[root] * a[st + len + i];
                a[st + i] = u + v;
                a[st + i + len] = u - v;
            }
}
std::vector<int> FurMult(std::vector<int>& a_)
{
    std::vector<std::complex<long double>> a(a_.size());
    for (size_t i = 0; i < a_.size(); ++i) {
        a[i] = a_[i];
    }
    int n = 1, h = 0;
    while (n < a.size() + a.size())
        n *= 2, ++h;
    while (a.size() < n)
        a.push_back(0);

    rev[0] = 0;
    for (int i = 1, high = -1; i < n; ++i) {
        high += !(i & (i - 1));
        rev[i] = rev[i ^ (1 << high)] | (1 << (h - high - 1));
    }
    long double sector = 2. * pi / n;
    for (int i = 0; i < n; ++i) {
        roots[i] = std::complex<long double>(cos(sector * i), sin(sector * i));
    }
    Furye(a);
    for (int i = 0; i < n; ++i)
        a[i] *= a[i];

    Furye(a);
    reverse(a.begin() + 1, a.end());
    for (std::complex<long double>& x : a)
        x /= n;
    std::vector<int> ansik;
    for (int i = 0; i < n; i++) {
        ansik.push_back(a[i].real() + 0.5);
    }
    return ansik;
}

int main() {
    std::string a;
    std::cin >> a;
    std::vector<int> a_(a.size());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == '1') {
            a_[i] = 1;
        } else {
            a_[i] = 0;
        }
    }
    std::vector<int> ansik = FurMult(a_);
    int64_t res = 0;
    for (int i = 0; i < ansik.size(); i++) 
    {
        if (ansik[i] % 2 == 1) {
            res += ansik[i] / 2;
        }
    }
    std::cout << res << std::endl;
}