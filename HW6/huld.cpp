#include <iostream>
using namespace std;
int a[100005] = {};
int n; 
int lb(int x){
	int l = 0;
	int r= n;
	while(l<r){
		int m = (l+r)/2;
		if(a[m] >= x) r= m;
		else l = m+1;
	}
	return r+1;

}
int ub(int x){
	int l = 0;
	int r= n;
	while(l<r){
		int m = (l+r)/2;
		if(a[m] > x) r = m;
		else l = m+1;
	}
	return r+1;
}

int cmp(const void*a, const void*b){
	int*aa = (int*)a;
	int*bb = (int*)b;
	return (*aa)-(*bb);
}

int main(){
 int q;
	cin>>n;
	for(int i = 0; i<n;i++) cin>>a[i];
	cin>>q;
	qsort(a,n,sizeof(a[0]), cmp);
	while(q--){
		int x;
		cin>>x;
		cout<<ub(x)-lb(x)<<endl;
	}
	

}