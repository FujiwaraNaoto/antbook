/*
あり本 p187
*/
#include<iostream>
#include<vector>
using namespace std;
const int INF=1<<30;

// Typeにはソートの基準が必要
template<class Type> class segment_tree{
    public:
        
        vector<Type> dat;
        int n=1;
        segment_tree(int n_){    
            while(n < n_){
                n*=2;
            }
            dat = vector<Type>(2*n-1,INF);// 0,1,2,...,2*n-1,2*n-2
        }

        ~segment_tree(){
            vector<Type>().swap(dat);
        }


        void update(int k,Type a){
            k+=n-1;
            dat[k] = a;
            while(k>0){
                k = (k-1)/2;
                dat[k]=min(dat[2*k+1],dat[2*k+2]);
            }
        }

        //[a,b)
        Type query(int a,int b,int k,int l,int r){
            if(r<=a || b<=l) return INF;
            if(a<=l && r<=b) return dat[k];
            else{
                Type vl = query(a,b,2*k+1,l,(l+r)/2);
                Type vr = query(a,b,2*k+2,(l+r)/2,r);
                return min(vl,vr);
            }
        }

        //[a,b)の範囲でのmin
        Type query(int a,int b){
            return query(a,b,0,0,n);
        }

        Type operator[](int index){
            index += n-1;
            return dat[index];
        }
};



int main(){
    int N=40;
    int M=6;
    vector<int> s(M),t(M);
    s={20,1,10,20,15,30};
    t={30,10,20,30,25,40};
    /*
    for(int i=0;i<M;i++){
        cin>>s[i]>>t[i];
    }
    */

   vector<int> dp(N+10,INF);
   segment_tree<int> seg(N+10);

   dp[1]=0;//便宜上i=0から
   seg.update(1,0);//1番目の要素を0にする
   for(int i=0;i<M;i++){
        //[s[i],t[i]+1)
        int v=min(dp[t[i]],seg.query(s[i],t[i]+1)+1);
        dp[t[i]]=v;
        seg.update(t[i],v);
    }
    cout<<dp[N]<<endl;



    //O(NM)の解法
    vector<vector<int>> dp2(M+1,vector<int>(N+10,INF));

    segment_tree<int> seg2(N+10);

    dp2[0][1]=0;
    seg2.update(1,0);//1番目の要素が0
    //O(NM)
    for(int i=0;i<M;i++){//i=0~M-1の M個
        dp2[i+1]=dp2[i];//コピーでO(N)
        
        int v = min(dp2[i+1][t[i]],seg2.query(s[i],t[i]+1)+1);
        dp2[i+1][t[i]]=v;
        seg2.update(t[i],v);
    }

    cout<<dp2[M][N]<<endl;
   

}