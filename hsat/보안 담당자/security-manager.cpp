#include <iostream>
#include <string>

using namespace std;

int N;
string records;

int main() {
    cin >> N;
    cin >> records;

    if (N % 2 != 0){
        cout << "No";
        return 0;
    }

    int cnt_left = 0;

    for(char s : records){
        if (s == '(') cnt_left++;
    }

    int need = (N / 2) - cnt_left;

    if (need < 0){
        cout << "No";
        return 0;
    }

    for (int i = 0; i < N; i++){
        if (records[i] == '?'){
            if (need > 0){
                records[i] = '(';
                need--;
            }else{
                records[i] = ')';
            }
        }
    }

    int balance = 0;

    for (char c : records){
        if (c == '(') balance++;
        else balance--;

        if (balance < 0){
            cout << "No";
            return 0;
        }
    }

    cout << "Yes";
    return 0;
}
