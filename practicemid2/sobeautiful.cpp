#include <iostream>
#include <string>
#include <vector>
using namespace std;
int n, p,r,s;
vector< vector<int> > v(205, vector<int>(5,0));
int main(){
	int n;
	cin>>n;
	while(n--){
		string in;
		cin>>in;
		int cnt = 0; char ch;
		for(auto i : in){
			if(i == 'a' || i == 'e' || i == 'o' || i =='u' || i== 'i' ){
				cnt++; ch = i;
			}
		}
		int id = 0;
		if(ch == 'a'){ id = 0;}
		else if (ch == 'e') id = 1;
		else if (ch == 'i') id = 2;
		else if(ch == 'o')id = 3;
		else if(ch =='u') id = 4;
		v[cnt][id]++;
	}

	for(auto i : v){ int tmp = 0;
		for(auto j: i){	p += j/2; tmp += j%2;

		}
		s += tmp/2;
	}
	int res;
	res = (s>p) ? p : (s+p)/2;
	cout<<res<<endl;

}