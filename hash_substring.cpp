#include <iostream>
#include <string>
#include <vector>

//USE LONG LONG
//CHECK FOR NEGATIVE MODULO


using namespace std;
typedef long long ull;
ull p = 1000000007;
ull m = 15;

struct Data {
    string pattern, text;
};

size_t hashf(const string& s) {
    unsigned long long hash = 0;
    if (m > 1)
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i){
            hash = (hash * m + s[i]);
            hash %= p;
        }
    else
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i){
            hash += s[i];
            hash %= p;
        }
    return hash;
}
 
Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
}

vector<long long> precompute(const Data& d){
    int i = d.text.size() - d.pattern.size();
    vector<long long> H(i + 1);
    {
        string S = d.text.substr(i, d.pattern.size());
        H[i--] = hashf(S);
    }
    ull y = 1;
    for (int i = 0; i < d.pattern.size(); i++){
        y = y * m % p;
    }
    for (; i >= 0; i--) {
        H[i] = m * H[i + 1] - y * d.text[i + d.pattern.size()] + d.text[i];
        while (H[i] < 0) H[i] += p;
        H[i] %= p;
    }
    
    return H;
}

std::vector<long long> get_occurrences(const Data& input) {
    vector<long long> H = precompute(input);
    ull h = hashf(input.pattern);
    for (int i = 0; i < H.size(); i++){
        if (h == H[i]) 
        {    
            if(input.text.substr(i, input.pattern.size()) == input.pattern)
            {
                cout << i << ' ';
            }
        }
    }
    return H;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    // print_occurrences(get_occurrences(read_input()));
    get_occurrences(read_input());
    return 0;
}
