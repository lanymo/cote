#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    // Please write your code here.
    map<string, int> m;
    int N; cin >> N;

    for (int i = 0; i < N; i++){
        string s; cin >> s;
        m[s]++;
    }

    cout << fixed << setprecision(4);

    for (auto it = m.begin(); it != m.end(); it++){
        double ratio = (double)it->second / N * 100;
        cout << it->first << " " << ratio << "\n";
    }
    return 0;
}