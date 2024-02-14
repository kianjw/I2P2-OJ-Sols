#include <iostream>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int f[100001] = {};
        int pre[100001] = {};
        for(int i =a;i<=b;i++){
            f[i+b]++;
            f[i+c+1]--;
        } long long int ans = 0;
        for(int i =1;i<=100000;i++) f[i]+= f[i-1];
        for(int i =1;i<=100000;i++) pre[i] = pre[i-1] + f[i]; int limit = 0;
        for(int i =c;i<=d;i++){
            limit = (i%2 == 0) ? 1.5*i - 1: 1.5*i;
            ans += pre[limit]- pre[i];
        }
        cout<<ans<<endl;
    }
}