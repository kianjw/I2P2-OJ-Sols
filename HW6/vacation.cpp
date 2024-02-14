#include <iostream>
#define max(x,y) ((x) > (y) ? (x) : (y))
using namespace std;

int main(){
	int n; cin>>n;
 int a[100002] = {};
int b[100002] ={};
int c[100002] = {};
	for(int i = 0; i<n;i++) cin>>a[i]>>b[i]>>c[i];
	for(int i = 1; i<n;i++) {
		a[i] = a[i] + max(b[i-1], c[i-1]);
		b[i] = b[i] + max(a[i-1], c[i-1]);
		c[i] = c[i] + max(a[i-1], b[i-1]);
	}
int ans;
	ans = max(a[n-1],b[n-1]);
	if(ans < c[n-1]) ans = c[n-1];
	cout<<ans<<'\n';
}