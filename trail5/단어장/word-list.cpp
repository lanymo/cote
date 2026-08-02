#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    // Please write your code here.
    int N; cin >> N;
    map<string, int> m;

    for (int i = 0; i < N; i++){
        string s; cin >> s;
        m[s]++;
    }

    for (auto it = m.begin(); it != m.end(); it++){
        cout << it->first << " " << it->second << "\n";
    }

    return 0;
}