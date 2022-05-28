/*
AC
POJ2229
xが奇数の時 1+(x-1)となるしかないので
dp[x]=dp[x-1]

xが偶数の時
1+(x-1)と 2*(x/2) という手段があるので

dp[x] = dp[x-1] + dp[x/2]

*/
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<cstdio>
using namespace std;
typedef long long ll;
const int MOD = 1e9;//ラスト9桁のみ考える
map<int,ll> memo;

//このdfsを使うとTLE
ll dfs(int x){
    if(x<0) return 0;
    if(x==0) return 1;

    if(memo.count(x)) return memo[x];

    if(x%2==1){
        // 1 + dfs(x-1)となるしかない
        return memo[x]=dfs(x-1);
    }else{
        ll ret=0;
        
        ret+=dfs(x-1);
        ret%=MOD;
        ret+=dfs(x/2);
        ret%=MOD;
        return memo[x]=ret;
    }    
}

int main(){
    int N;
    cin>>N;
    //cout<<dfs(N)<<endl;//TLE

    vector<ll> dp(N+1,0);
    dp[1]=1;
    dp[2]=2;//1+1 と 2
    for(int i=3;i<=N;i++){
        if(i%2==1){
            dp[i]=dp[i-1];
        }else{
            dp[i]=(dp[i-1]+dp[i/2])%MOD;
        }
    }
    cout<<dp[N]<<endl;

}