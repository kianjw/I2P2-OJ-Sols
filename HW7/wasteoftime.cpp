#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

vector <int> G[300001];
priority_queue<int, vector<int>, greater<int> > pq;

void solve(){
	int n, m;
	cin>>n>>m;
	int in[300005] ={};
	for(int i=0,u,v; i<m;i++){
		cin>>u>>v;
		G[u].emplace_back(v);
		in[v] +=1;
	}

	for(int i = 0; i< n;i++){
		if(in[i] == 0)
		pq.push(i);
	}
	vector<int>ans;
	while(!pq.empty()){
		int now = pq.top(); pq.pop();
		ans.emplace_back(now);
		for(int &i : G[now]){
			in[i]--;
			if(in[i] == 0) pq.push(i);
		}
	}
	for(int i = 0; i<n;i++){
		cout<<ans[i] << ((i == n-1) ? "\n" : " ");
	}
    for(int i=0; i<n; ++i) G[i].clear();
	memset(in, 0, sizeof(in));
}

int main(){
	int t;
	cin>>t;
    while(t--){
	solve();
    }
}