#include <iostream>
#include <cstring>
using namespace std;
int n, r, k;
int x[505];
int y[505];
int visited[505]={};
int count = 0;

int check(int i, int now){
	if(((x[now] - x[i])* (x[now] - x[i]) + (y[now] - y[i])* (y[now] - y[i])) <= r*r) return  1;
	else return 0;
}

void dfs(int now){
	if(visited[now] == 0)::count++;
	visited[now] = 1;
	for(int i =0; i<n;i++){
		if(visited[i]) continue;
		if(check(i,now) == 0) continue;
		dfs(i);
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
		cin>>n>>r>>k;
		for(int i =0;i<n;i++) cin>>x[i]>>y[i];
		int red = 0;
		int blue = 0;
		for(int i = 0; i<n;i++){
			dfs(i);
			if(::count >=1 &&  ::count < k) blue++;
			else if( ::count >=k) red++;
			::count = 0;
		}
		memset(visited, 0, sizeof(visited));
		cout<<blue<<' '<<red<<endl;
	}
}