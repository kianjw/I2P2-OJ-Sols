#include <iostream>
#include <string>
#include <set> 
using namespace std;
typedef long long ll;

int main(){
	int n;
	cin>>n;
	set<int> ans; ll sum = 0;
	while(n--){
		string a;
        cin>>a;
		if(a == "insert"){
			int num;
			cin>>num;
			ans.insert(num);
		}
		else if(a == "print" && ans.begin() != ans.end()){
			auto last = ans.end();
			last--;
			for(auto it = ans.begin(); it != ans.end(); it++)
			cout<<(*it)<< ((it == last) ? '\n' : ' ');

		}
		else if(a == "min"){
			if(ans.empty()) continue;
			else cout<<*ans.begin()<<endl;	
		}
		else if(a == "range_erase"){
			int l, r;
			cin>>l>>r;
			auto L = ans.lower_bound(l);
			auto R = ans.upper_bound(r);
			ans.erase(L,R);
		}
		

		
	}
}