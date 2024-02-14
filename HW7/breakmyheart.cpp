#include <iostream>
#include <string>
#include <set> 
using namespace std;
typedef long long ll;

int main(){
	int n;
	cin>>n;
	ll sum = 0;
	set<int> ans;
	while(n--){
        string op;
   		 cin>>op;
		if(op == "print" && !ans.empty()){
			auto last = ans.end();
			last--;
			for(auto i = ans.begin(); i!=ans.end(); i++){
				cout<<*i<<((i == last) ? '\n' : ' ');
			}
		}
		if(op == "range_erase"){
			int a, b; cin>>a>>b;
			auto L = ans.lower_bound(a);
			auto R = ans.upper_bound(b);
			for(auto i = L ; i !=  R;i++) sum-=*i;
			ans.erase(L,R);

		}
		if(op == "min"){
            if(ans.empty()) continue;
			cout<<*ans.begin()<<'\n';

		}
		if(op == "insert"){
			int num; cin>>num;
			if(ans.find(num) == ans.end() ){ 
			ans.insert(num);
			sum+=num;
			}
		}
		if(op == "sum") cout<<sum<<'\n';
	}
}