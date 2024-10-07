#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>

using namespace std;

class Hasher {

public:
    const int64_t modul;
    const int64_t k;
    int64_t q = 1;
    Hasher(int64_t mod, int64_t k) : modul(mod), k(k) {}

    std::vector<int64_t> FindPatHashs(std::string pattern){
        int64_t hash_P = 0;

        for (int64_t i = 0; i < pattern.length(); ++i) {
            hash_P = (hash_P * k + (pattern[i]-'a' + 1)) % modul;
            if(i > 0){
                q*=k;
                q%=modul;
            }
        }

        vector<int64_t> hashes(pattern.length());
        hashes[0] = hash_P;
        for (int64_t i = 1; i < pattern.length(); ++i) {
            hashes[i] = ((hashes[i-1] - (pattern[i-1]-'a'+1) * q) * k + (pattern[i-1]-'a'+1)) % modul;
            if (hashes[i] < 0) hashes[i] += modul;
        }
        return hashes;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    
    string pattern, text;
    cin >> pattern >> text;

    Hasher hasher1(3036998183, 31);
    std::vector<int64_t> hashs = hasher1.FindPatHashs(pattern);
    std::unordered_map<int64_t,bool> hashes;
    for(size_t i = 0 ; i < hashs.size();++i){
        hashes[hashs[i]] = true;
    }

    Hasher hasher2(1e9+7, 29);
    std::vector<int64_t> hashs2 = hasher2.FindPatHashs(pattern);
    std::unordered_map<int64_t,bool> hashes2;
    for(size_t i = 0 ; i < hashs2.size();++i){
        hashes2[hashs2[i]] = true;
    }

    int64_t m = pattern.length();
    int64_t n = text.length();
    
    if(m > n){
        cout << 0 << endl;
        return 0;
    }
    
    int64_t count = 0;
    
    int64_t hash_T1 = 0, hash_T2=0;
    for (int64_t i = 0; i < n; ++i) {
        if (i >= m) {
            hash_T1 = ((hash_T1 - (text[i-m]-'a'+1) * hasher1.q) * hasher1.k + (text[i]-'a'+1)) % hasher1.modul;
            if (hash_T1 < 0) hash_T1 += hasher1.modul;
            hash_T2 = ((hash_T2 - (text[i-m]-'a'+1) * hasher2.q) * hasher2.k + (text[i]-'a'+1)) % hasher2.modul;
            if (hash_T2 < 0) hash_T2 += hasher2.modul;
        } else {
            
            hash_T1 = (hash_T1 * hasher1.k + (text[i]-'a'+1)) % hasher1.modul;
            hash_T2 = (hash_T2 * hasher2.k + (text[i]-'a'+1)) % hasher2.modul;
            
           
        }
        
        if(hashes.find(hash_T1) != hashes.end() && hashes2.find(hash_T2) != hashes2.end()){
            ++count;
        }
    }

    cout << count << endl;

    return 0;
}