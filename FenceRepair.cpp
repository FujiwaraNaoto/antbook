/*
蟻本 P49 

ABC252Fを参考
証明については
HuffmanCoding.md参照
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<queue>
#include<cstdio>
#include<functional>

using namespace std;
typedef long long ll;
typedef pair<int,ll> P;
typedef pair<int,int> P2;
typedef pair<ll,P2> PP;
const ll INF = 1LL<<60;


int main(){
    int N;
    
    cin>>N;
    vector<ll> L(N);
    priority_queue<ll,vector<ll>,function<bool(const ll&,const ll &)>> pque(
        [](const ll& lhs,const ll &rhs){
            return lhs>rhs;
        }
    );
    
    //priority_queue<ll,vector<ll>,greater<ll>> pque;//これでもいい
    for(int i=0;i<N;i++){
        cin>>L[i];

        pque.push(L[i]);
    }
    ll ans=0;
   
    for(int i=0;i<N-1;i++){
        ll x=pque.top();
        
        pque.pop();
       
        ll y=pque.top();
        pque.pop();
        ans+=(x+y);
        pque.push(x+y);

    }

    cout<<ans<<endl;

}