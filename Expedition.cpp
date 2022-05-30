#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<algorithm>
using namespace std;
typedef pair<int,int> P;//firstが距離 secondがガソリン量

int main(){
    int N,L,init_p;
    cin>>N>>L>>init_p;
    
    vector<P> gas_station(N+1);
    vector<int> A(N),B(N);
    for(int i=0;i<N;i++){
        cin>>A[i]>>B[i];
        gas_station[i]=P{A[i],B[i]};
    }
    gas_station[N]=P{L,0};

    
    sort(gas_station.begin(),gas_station.end(),
        [](const P&lhs,const P&rhs){
        if(lhs.first!=rhs.first){
            //距離が小さい方から
            return lhs.first<rhs.first;
        }else{
            return lhs.second>rhs.second;
        }
    });
    
    int pos=0,ans=0,tank=init_p;

    priority_queue<int,vector<int>,function<bool(int,int)>> que(
        [](const int &lhs,const int &rhs){
            return lhs<rhs;//降順
        }
    );


    for(int i=0;i<=N;i++){
        int d=gas_station[i].first-pos;

        while(tank-d<0 && !que.empty()){
            tank+=que.top();
            que.pop();
            ans++;
        }
        if((tank-d)<0){
            ans=-1;
            break;
        }

        tank-=d;
        pos+=d;
        que.push(gas_station[i].second);
    }

    cout<<ans<<endl;

}