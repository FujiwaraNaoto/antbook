/*
漸化式は
dp[i]=i円支払う時の 買う品物の通り数
WA
*/
#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;

int main(){
    int N,K;
    cin>>N>>K;
    /*
    vector<vector<ll>> dp(K+2,vector<ll>(N+1,0));

    dp[1][1]=1;//1番目から考えた時に 価値が1となるものは1通り
    for(int i=1;i<=K;i++){
        for(int j=0;j<i;j++){
            for(int k=0;j-k*i>=0;k++){
                dp[i+1][j]=max(dp[i][j-k*i]+k*i ,dp[i+1][j]);
            }
        }
        
    }

    cout<<dp[K+1][N]<<endl;
    */

    vector<ll> dp(N+1,0);
    dp[0]=1;
    /*
    //もらうDP
    for(int c=1;c<=K;c++){
        for(int i=c;i<=N;i++){
            dp[i]+=dp[i-c];
        }
    }
    */
    //配るDP
    for(int c=1; c<=K; c++) {
        for(int i=0; i+c<=N; i++) {
            dp[i+c] += dp[i];
        }

    }

    cout<<dp[N]<<endl;


}