#include <iostream>
#include <vector>
#include <bitset>
#include<string>
using namespace std;

void dfs(int idx, int*in, vector< bitset<2005> > v){
    in[idx] = 1;
    for(int i = 0; i< 26;i++){
        if(in[i] || v[i].none()) continue;
        if((v[idx] & v[i]) != 0) dfs(i,in,v);
    }
}

int main(){
    int t;
    cin>>t; 
    while(t--){
        int n;
        vector < bitset <2005> > v(26);
        cin>>n;
		 string a;	
        int in[26] = {};
        for(int i = 0;i<n;i++){
            cin>>a;
            for(auto j :a) v[j-'a'][i] = 1;
        }
        int res = 0;
        for(int i = 0; i< 26;i++){
            if(in[i]|| v[i].none()) continue;
            dfs(i,in,v);
            res++;
        }
        cout<<res<<endl;
    }
}