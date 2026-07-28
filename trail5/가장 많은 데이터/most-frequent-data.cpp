#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    // Please write your code here.
    int N; cin >> N;

    unordered_map<string, int> cnt;

    while (N--){
        string color; cin >> color;
        cnt[color]++;
    }

    int max_val = 0;

    for (auto entry : cnt){
        max_val = max(max_val, entry.second);
    }

    cout << max_val;

    return 0;
}