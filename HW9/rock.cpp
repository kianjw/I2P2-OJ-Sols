
#include <iostream>

using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		int m, n;
		cin>>m>>n;
		int a[505][505];
		for(int i = 1;i<=m;i++) {
			for(int j = 1; j<=n;j++) cin>>a[i][j];
		}
      
		for( int i = 1;i<=m;i++){
			for(int j= 1; j<=n;j++){
                
				a[i][j] = a[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
                
			}
            
		}
		int q;
		cin>>q;
		while(q--){
			int x1, y1, x2, y2;
			cin>>x1>>y1>>x2>>y2;
			int ans = a[x2][y2] - a[x2][y1-1] - a[x1-1][y2] + a[x1-1][y1-1];
			cout<<ans<<endl; 

		}
	}
}