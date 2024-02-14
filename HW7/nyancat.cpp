#include <iostream>
using namespace std;
int x[10004] = {};
int y[10004] ={};
int visited[10004] = {};
int n, r, k, t;
int count = 0;
int check(int i, int now){
	if(((x[i]-x[now])*(x[i]-x[now])) + (y[i] - y[now])*(y[i] - y[now]) <= r*r) return 1;
	else return 0;
}

void dfs(int now){
	if(visited[now] ==0) ::count++;
	visited[now] = 1; 
	for(int i = 0; i<n;i++){
		if(visited[i]) continue;
		if(check(i,now) == 0) continue;
		dfs(i);
	}


}
int main(){
	cin>>t;
	while(t--){ 
	cin>>n>>r>>k;
    for(int i = 0; i< n;i++) visited[i] = {};
	for(int i = 0; i<n;i++) cin>>x[i]>>y[i];
	int red = 0, blue = 0;
	for(int i = 0; i< n;i++){
		dfs(i);
		if(::count <k && ::count >=1) blue++;
		else if(::count >= k ) red++;
		::count = 0;

	} 
	cout<<blue<<" "<<red<<endl;

	}
}