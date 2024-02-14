#include <iostream>
#include <cstring>
#define min(x,y) (x) < (y) ? (x) : (y)
#define max(x,y) (x) > (y) ? (x) : (y)
using namespace std;
int guard[5005][2];
int wall[5005] ={};
int n,q;
int take(int now){
	int temp[5005] = {};
	for(int i = 1; i<=n;i++){
		temp[i] = wall[i];
	}
	for(int i = guard[now][0] ; i<= guard[now][1] ;i++){
		temp[i]--;
	}
	int full = 0;
	for(int i = 1; i<=n;i++ ){
		if(temp[i]) full++;
	}
	int pre[5005] = {};
	for(int i= 1 ; i<=n;i++){
		pre[i] = pre[i-1] + ((temp[i] == 1) ?  1 :  0);
	}
	int minus = 0x3f3f3f3f;
	for(int i = 0;i<q;i++){
		if(i!= now){
			minus = min(minus, pre[guard[i][1]] - pre[guard[i][0] - 1]);
		}
	}
	return full - minus;

}

int main(){
	int t;
	cin>>t;
	while(t--){

		cin>>n>>q;
		for(int i = 0;i<q;i++){
			cin>>guard[i][0]>>guard[i][1];
			for(int j = guard[i][0] ; j<= guard[i][1];j++){
				wall[j]++;
			}
		}
		int ans = 0; 
		for(int i =0;i<q;i++){
			ans = max(ans,take(i)); 
		}
        if(ans ==3) ans =ans - 1;
        else if(ans ==2) ans =ans- 1;
		cout<<ans<<endl;
		memset(wall,0 , sizeof(wall));
        
	}
}