#include <iostream>
#include <set>
#include <string>
using namespace std;
int main(void){
    int n, x;
    string s;
    set<pair<int, string> > S;
    cin >> n;
    while(n--){
        cin >> s;
        if(s == "born"){
            cin >> s >> x;
            S.insert({x, s});
        }
        else if(s == "find"){
            cin >> s >> x;
            cout << (S.count({x, s})?"YES":"NO") << "\n";
        }
        else if(s == "kill"){
            cin >> s >> x;
            S.erase({x, s});
        }
        else if(s == "young"){
            if(S.empty()) continue;
            cout << S.begin()->second << " " << S.begin()->first << "\n";
        }
    }
    return 0;
}