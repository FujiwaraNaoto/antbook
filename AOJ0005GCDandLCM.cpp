/*
標準入力でつまずく
AC
*/
#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<queue>
using namespace std;
typedef long long ll;

ll gcd(ll x,ll y){
    return y?gcd(y,x%y):x;
}

ll lcm(ll x,ll y){
    ll g = gcd(x,y);
    return (x/g)*y;
}

int main(){
    ll a,b;
    while( cin>>a>>b && !cin.eof()){
        
        cout<<gcd(a,b)<<' '<<lcm(a,b)<<endl;
        
    }
}