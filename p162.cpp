/*
あり本p162
バブルソートの交換回数
*/

#include<iostream>
#include<bit>
#include<string>
#include<vector>
//using namespace std;
typedef long long ll;


template<class Type> struct binary_indexed_tree{
    int N;
    std::vector<Type> bit;
    
  

    binary_indexed_tree(int n,Type v):N(n+1){
        bit = std::vector<Type>(n+1,v);
        N=n+1;
    }

    ~binary_indexed_tree(){
        std::vector<Type>().swap(bit);
    }



    void add(int x,Type a){
        x++;//1から始めるための補正
        //for(int i=x; i<=N; i+=(i&-i)) bit[i] = addition(bit[i],a);
        while(x<=N){
            //bit[x] = addition(bit[x],a);
            bit[x] =bit[x]+a;
            x += x&-x;
        }
    }

    
    Type sum(int x){
        x++;//1から始まることに注意
        Type ret=0;
        //for(int i=x; i>0; i-=(i&-i)) ret = addition(ret,bit[i]);
        while(x>0){
            ret = ret+bit[x];
            x -= x&-x;
        }
        
        return ret;
    }

    //[l,r]の範囲
    // rはN-1以下
    Type get(int l,int r){
        if(r>N) return 0;//配列の外へのアクセス
        if(l>r) return 0;//本来は l<=r となるのでおかしい
        if(l==0) return sum(r);//[0,r]//ここでoutなわけか
        else return (sum(r) - sum(l-1));
    }
};

int main(){

    int n=4;
    std::vector<int> a={3,1,4,2};   
    binary_indexed_tree<ll> BIT(n+1,0);

    ll ans=0;
    for(int j=0;j<n;j++){
        ans+= j-BIT.sum(a[j]);
        BIT.add(a[j],1);
    }
    std::cout<<ans<<std::endl;

    /*
    //O(N^2)
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            ans++;
        }
    }
    */

}