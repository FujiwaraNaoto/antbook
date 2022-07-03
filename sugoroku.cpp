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

