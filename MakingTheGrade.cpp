/*
TLE
合ってるのかさえわからない

*/
#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1LL<<60;

int main(){
    int N;
    cin>>N;
    vector<ll> A(N);
    for(int i=0;i<N;i++) cin>>A[i];

    vector<ll> ordA=A;
    sort(ordA.begin(),ordA.end());

    vector<vector<ll>> dp(N+1,vector<ll>(N,INF));

    dp[0]=vector<ll>(N,0);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=j;k<N;k++){
                dp[i+1][k]=min(dp[i][j]+abs(A[i]-ordA[k]),dp[i+1][k]);
            }
        }
    }    

   

    vector<ll> ordA2=A;
    /*
    sort(ordA2.begin(),ordA2.end(),
    [](const ll& lhs,const ll &rhs){
        return lhs>rhs;
    });
    */
   sort(ordA2.begin(),ordA2.end());
   reverse(ordA2.begin(),ordA2.end());


    vector<vector<ll>> dp2(N+1,vector<ll>(N,INF));

    dp2[0]=vector<ll>(N,0);

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=j;k<N;k++){
                dp2[i+1][k]=min(dp2[i][j]+abs(A[i]-ordA2[k]),dp2[i+1][k]);
            }
        }
    }

    ll ans=min(dp[N][N-1],dp2[N][N-1]);
    cout<<ans<<endl;


}