#include <iostream>
#include <map>
using namespace std;

int main() {
    // Please write your code here.
    int N; cin >> N;
    map<int, int> m;

    for (int i = 1; i <= N; i++){
        int num; cin >> num;

        if (m.find(num) == m.end()){
            m[num] = i;
        }
    }

    for (auto it = m.begin(); it != m.end(); it++){
        cout << it->first << " " << it->second << "\n";
    }
    return 0;
}