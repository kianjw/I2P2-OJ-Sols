#include <iostream>
#define min(x,y) ((x) < (y) : (x) ? (y))
using namespace std;
int main(){
	int n, m;
	cin>>n>>m;
	int a[1005][1005];
	for(int i = 0; i<n;i++){
		for(int j = 0 ; j< m;j++){
			cin>>a[i][j];
		}
	}
	int ans = a[0][0];
	for(int i = 0 ; i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i][j] < ans){
				ans = a[i][j] ;
			}

		}
	}
	cout<<ans<<endl;




}