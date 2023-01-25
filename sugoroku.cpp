/*
p109 双六
*/

#include<iostream>
using namespace std;
int extgcd(int a,int b,int &x,int &y){
    if(b==0){
        x=1,y=0;
        return a;
    }
    int xp=0,yp=0;
    int ret = extgcd(b,a%b,xp,yp);
    x=yp;
    y=xp-(a/b)*yp;
    return ret;
}

int main(){
    //int a=512,b=27;
    int a=120,b=7253;
    int x,y;
    extgcd(a,b,x,y);
    cout<<"x="<<x<<",y="<<y<<endl;

    return 0;
}


/*
P108
https://qiita.com/KowerKoint/items/870ea9ef7a39f3fe4ce3
https://noshi91.hatenablog.com/entry/2019/04/01/184957

*/
/*
#include<iostream>
#include<tuple>
using namespace std;
typedef long long ll;

ll extgcd(ll a,ll b,ll& x,ll& y){
    if(b==0){ x=1;y=0;return a;}
    
    ll d=extgcd(b,a%b,x,y);
    ll t=y;
    y=x-(a/b)*y;
    x=t;
    return d;
}


ll extGCD(ll a,ll b,ll& x,ll& y){
    x=1;y=0;
    ll nx=0,ny=1;
    //a*x+b*y=a においてx=1, y=0 が初期条件
    // a*nx+b*ny=b 

    while(b){
        ll q=a/b;
        std::tie(a,b) = std::make_pair(b,a%b);
        std::tie(x,nx) = std::make_pair(nx,x-nx*q);
        std::tie(y,ny) = std::make_pair(ny,y-ny*q);

    }

    return a;
}


// a*xs + b*ys=s
// a*first + b*second=gcd(a,b)
std::pair<ll,ll> extGCD(ll a,ll b){
    ll s=a,xs=1,ys=0;
    ll t=b,xt=0,yt=1;

    while(s%t!=0){
        ll tmp=s/t;
        ll u=s-t*tmp;
        ll xu=xs - xt*tmp;
        ll yu=ys - yt*tmp;

    //s<-t へ置き換え
    //t<-u　へ置き換え

        s=t;
        xs=xt;
        ys=yt;
        t=u;
        xt=xu;
        yt=yu;
    }

    return std::make_pair(xt,yt);
}

int main(){

}
*/