#include <iostream>
#include <string>
#include <unordered_map>
#include <cctype>
using namespace std;

int n, m;
string words[100000];
string queries[100000];

int main() {
    cin >> n >> m;

    unordered_map<int, string> iw;
    unordered_map<string, int> wi;

    for (int i = 1; i <= n; i++) {
        cin >> words[i];
        iw[i] = words[i];
        wi[words[i]] = i;
    }

    for (int i = 0; i < m; i++) {
        cin >> queries[i];

        if (isdigit(queries[i][0])){
            int idx = stoi(queries[i]);
            cout << words[idx] << "\n";
        }else{
            cout << wi[queries[i]] << "\n";
        }
    }

    return 0;
}
