//AC
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
typedef pair<int,int> P;
typedef pair<int,P> PP;

int main(){
    int R,C;

    
    while(1){

        cin>>R>>C;
        if(R==0 && C==0)break;

        vector<vector<int> > osenbei(R,vector<int>(C));
        for(int y=0;y<R;y++){
            for(int x=0;x<C;x++){
                cin>>osenbei[y][x];
            }
        }

        int ans=0;
        for(int S=0;S<(1<<R);S++){
            int tmpSum=0;
            for(int x=0;x<C;x++){//x列目を変えるかどうかを考える
                int ansNormal=0;//x列目をひっくり返さない場合
                int ansReverse=0;//x列目をひっくり返す場合
                for(int y=0;y<R;y++){
                    if((S>>y)&1){//y行目がひっくり返されている状態
                        ansNormal +=(1-osenbei[y][x] ? 0:1);//0なら1になることがややこしい
                        ansReverse +=(osenbei[y][x] ? 0:1);

                    }else{
                        ansNormal += (osenbei[y][x]?0:1);
                        ansReverse +=(1-osenbei[y][x]?0:1);


                    }
                }

                tmpSum+=max(ansNormal,ansReverse);
            }
            ans=max(ans,tmpSum);

        }

        cout<<ans<<endl;
    }

}