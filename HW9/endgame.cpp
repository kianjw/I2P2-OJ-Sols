#include <iostream>
#include<vector>
#include <queue>
#include<string>
using namespace std;

class Point{
    public:
    int x, y, z;
    Point(int xx , int yy, int zz) : x(xx), y(yy), z(zz){}
};

int main(){
    int n,m; int cnt = 0; int x, y; int res = -1;
    cin>>n>>m;
    int used[1005][1005] = {};
    int dx[] = {-1,1,0,0};
    int dy[] ={0,0,-1,1};
    vector<string> v(m); queue<Point> pq;
    for(int i =0;i<n;i++) cin>>v[i];
    for(int i  = 0;i<n;i++){
        for(int j =0; j<m;j++){
            if(v[i][j] == 'T') cnt++;
            else if(v[i][j] == 'I') {
                x = i; y = j;
            }
        }
    }
    pq.push(Point(x,y,0));
    used[x][y]= 1;
    while(!pq.empty()){
        Point now = pq.front();
        pq.pop();
        if(v[now.x][now.y] == 'T') cnt--;
        if(cnt == 0){
            res = now.z; break;
        }
        for(int i = 0;i<4;i++){
            int nx = now.x + dx[i];
            int ny = now.y  +dy[i];
            if(nx<0 ||  ny<0 || nx>=n || ny>=m|| used[nx][ny] || v[nx][ny] == 'C' ) continue;
            pq.push(Point(nx,ny,now.z+1));
            used[nx][ny] = 1;
        }
    }
    cout<<res<<endl;
    


}