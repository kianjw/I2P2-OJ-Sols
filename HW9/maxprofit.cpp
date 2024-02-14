#include <iostream>

using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int d; cin>>d; long long int maxprofit = 0;
		int a[1000005] ={}; 
		for(int i = 0;i<d;i++) cin>>a[i];
		int first; int numf;
		for(int i = 0; i<d;i++){
			if(a[i+1] >a[i]){
				first = a[i];
				numf = i;
				break;
			}
		}
		for(int i = numf;i<d;i++){
			if(a[i] > a[i-1]) maxprofit+= a[i] - a[i-1]; 
		}
		cout<<maxprofit<<endl;
	}
}