#include <iostream>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		int a, b, c, d;
		cin>>a>>b>>c>>d; long long int ans  = 0;
		int f[100000]={};
		 int pre[100000]={};
		for(int i = a; i<=b;i++){
			f[i+b]++;
			f[i+c+1]--;
		}
		for(int i = 1; i<= 100000;i++){
			f[i]+= f[i-1];
		}
		for(int i = 1;i<= 100000;i++){
			pre[i] = pre[i-1] + f[i];
		}
		for(int i =c;i<=d;i++){
			ans += pre[100000] - pre[i];
		}
		cout<<ans<<endl;

	}
}