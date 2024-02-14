#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#define N 2005
using namespace std;
void dfs(int idx, vector<bitset<N> >& v, int*in){
    in[idx] = 1;
    for(int i = 0; i < 26; i++){
        if(in[i] || v[i].none()) continue;
        if((v[idx]&v[i]) != 0) dfs(i, v, in);
    }
}
int main(void){

    int t, n;
    string s;
    cin >> t;
    while(t--){
        int res = 0;
        int in[26] = {};
        vector< bitset<N> > v(26);
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> s;
            for(auto c : s) v[c-'a'][i] = 1;
        }
        for(int i = 0; i < 26; i++){
            if(in[i] || v[i].none()) continue;
            dfs(i, v, in);
            res++;
        }
        cout << res << "\n";
    }
    return 0;
}