#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;
const int64_t MOD = 3036998183;
const int64_t MOD2 = 1e9+7;
const int64_t p2 = 29;
const int64_t p = 31;
int64_t q = 1;
int64_t q2 = 1;
std::vector<int64_t> FindPatHashs(std::string pattern){
    int64_t hash_P = 0;
    
    for (int64_t i = 0; i < pattern.length(); ++i) {
        hash_P = (hash_P * p + (pattern[i]-'a' + 1)) % MOD;
        if(i > 0){
            q*=p;
            q%=MOD;
        }
    }

    vector<int64_t> hashes(pattern.length());
    hashes[0] = hash_P;
    for (int64_t i = 1; i < pattern.length(); ++i) {
        hashes[i] = ((hashes[i-1] - (pattern[i-1]-'a'+1) * q) * p + (pattern[i-1]-'a'+1)) % MOD;
        if (hashes[i] < 0) hashes[i] += MOD;
    }
    return hashes;
}

std::vector<int64_t> FindPatHashs2(std::string pattern){
    int64_t hash_P = 0;
    
    for (int64_t i = 0; i < pattern.length(); ++i) {
        hash_P = (hash_P * p2 + (pattern[i]-'a' + 1)) % MOD2;
        if(i > 0){
            q2*=p2;
            q2%=MOD2;
        }
    }

    vector<int64_t> hashes(pattern.length());
    hashes[0] = hash_P;
    for (int64_t i = 1; i < pattern.length(); ++i) {
        hashes[i] = ((hashes[i-1] - (pattern[i-1]-'a'+1) * q2) * p2 + (pattern[i-1]-'a'+1)) % MOD2;
        if (hashes[i] < 0) hashes[i] += MOD2;
    }
    return hashes;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    string P, T;
    cin >> P >> T;

    int64_t m = P.length();
    int64_t n = T.length();
    if(m > n){
        cout << 0 << endl;
        return 0;
    }

    std::vector<int64_t> hashs = FindPatHashs(P);
    std::unordered_map<int64_t,bool> hashes;
    for(size_t i = 0 ; i < hashs.size();++i){
        hashes[hashs[i]] = true;
    }
    std::vector<int64_t> hashs2 = FindPatHashs2(P);
    std::unordered_map<int64_t,bool> hashes2;
    for(size_t i = 0 ; i < hashs2.size();++i){
        hashes2[hashs2[i]] = true;
    }
    
    int64_t count = 0;
    int64_t hash_T = 0;
    int64_t hash_T2 = 0;
    for (int64_t i = 0; i < n; ++i) {
        if (i >= m) {
            hash_T = ((hash_T - (T[i-m]-'a'+1) * q) * p + (T[i]-'a'+1)) % MOD;
            if (hash_T < 0) hash_T += MOD;
            hash_T2 = ((hash_T2 - (T[i-m]-'a'+1) * q2) * p2 + (T[i]-'a'+1)) % MOD2;
            if (hash_T2 < 0) hash_T2 += MOD2;
        } else {
            
            hash_T = (hash_T * p + (T[i]-'a'+1)) % MOD;
            hash_T2 = (hash_T2 * p2 + (T[i]-'a'+1)) % MOD2;
        }
        if(hashes.find(hash_T) != hashes.end() && hashes2.find(hash_T2) != hashes2.end()){
            ++count;
        }
    }

    cout << count << endl;
    return 0;
}