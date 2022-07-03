/*
Bのそれぞれの要素は Aのどれかの要素に一致する時が最適
*/
#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const ll INF = 1LL<<60;

ll solve(const vector<ll>& a,const vector<ll>& ord ){
    int N=(int)ord.size();

    /*
    dp[i][j] = i番目まで見た時に
    sortされたordのj番目を考える
    */

    vector<vector<ll>> dp(N+1,vector<ll>(N,INF));

    dp[0][0]=0;

    for(int i=0;i<N;i++){
        ll mi=INF;
        for(int j=0;j<N;j++){
            mi = min(mi,dp[i][j]);
            dp[i+1][j]=mi+abs(a[i]-ord[j]);
        }
    }    
    ll ret=INF;
    for(int j=0;j<N;j++){
        ret = min(ret,dp[N][j]);
    }

    return ret;
}


int main(){
    int N;
    cin>>N;
    vector<ll> A(N);
    for(int i=0;i<N;i++) cin>>A[i];

    vector<ll> ordA=A;
    sort(ordA.begin(),ordA.end());

  
    
    vector<ll> ordA2=ordA;
    /*
    sort(ordA2.begin(),ordA2.end(),
    [](const ll& lhs,const ll &rhs){
        return lhs>rhs;
    });
    */
   
   reverse(ordA2.begin(),ordA2.end());


    ll ans=min(solve(A,ordA),solve(A,ordA2));
    cout<<ans<<endl;


}