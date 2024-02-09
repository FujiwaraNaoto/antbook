/*
AC
*/
#include<iostream>
#include<set>
#include<algorithm>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<numeric>
#include<queue>
#include<cmath>
#include<cassert>
#include<unordered_map>
#include<optional>
#include<tuple>
using namespace std;
typedef long long ll;
const ll INF=1LL<<60;
typedef pair<int,int> P;
typedef pair<int,P> PP;
const ll MOD=998244353;


struct Aho_Corasick{
    typedef std::unordered_map<char,int> MP;

    std::vector<MP> trie;
    std::vector<int> cnt;//cnt,treeの大きさは同じ
    const int root=0;
    
    Aho_Corasick(){
        trie.push_back(MP());
        cnt.push_back(0);
    }

    std::unordered_map<int,std::vector<std::string>> output;

    void add(const std::vector<std::string>& terms){
        for(const std::string& term:terms){
            add(term);
        }
    }

    //計算量は挿入する文字列の長さの和
    int add(const std::string& string){
        int now=root;//根
        for(char c:string){
            if(trie[now].count(c)){
                now=trie[now][c];
            }else{
                int pre=now;
                now=trie.size();
                cnt.push_back(0);
                trie.push_back(MP());
                trie[pre][c]=now;
            }
        }

        cnt[now]++;//終端文字列

        output[now].push_back(string);//終端ノードに対してsを入れる
        

        return now;
    }

    void match(const std::string& string){

        cout<<"target: string="<<string<<endl;
       
        int now=0;
        
        for(int i=0;i<string.size();i++){
            char c=string[i];
            //今の状態nowからcを用いて遷移する場所を探す.
            while(!go(now,c)){
                now=failure[now];
            }
            //go(now,string[i]).firstがtrue
            now=*go(now,c);

            for(const auto& x:output[now]){
                //ノードnowで終わる場合
                cout<<"start="<<i-x.size()+1<<",goal="<<i<<",string:"<<x<<endl;
            }
        }
        
    }

    std::vector<int> failure;
    std::vector<int> dist;
    

    //ノードnowから文字列cをうけていく場所
    std::optional<int> go(int now,char c){
        
        if(trie[now].count(c)){
            return trie[now][c];
        }else if(now==root) return root;
        else return {};
        
    }

    void bfs(){
      
      failure=std::vector<int>(trie.size(),0);
      dist=std::vector<int>(trie.size(),-1);
      std::queue<int> que;
      
      dist[root]=0;
      que.push(root);

      while(!que.empty()){
        int now=que.front();
        que.pop();
        
        for(auto [c,to]:trie[now]){
          //nowのキーc,toを取り出す
          //trie[now][c]=toとなる
         
            if(now!=root){
                int f=failure[now];//nowで失敗した場合に行きつく場所
                
                while(!go(f,c)){
                    f=failure[f];
                }
                //go(f,c).firstがtrueつまり状態fの次に文字cで行ける場所がある　もしくはfがroot
                failure[to]=*go(f,c);

                for(const auto& string:output[failure[to]]){
                    //ノードfailure[to]で終わる文字列たちをtoにもいれる
                    output[to].push_back(string);
                }
               
            }

            que.push(to);
            dist[to]=dist[now]+1;
            
        }

      }
      

    }
    
};

struct State{
    
    P pos;
    int node;
    int dist;
    string str;//デバッグのために使用
    State(P pos_,int node_,int dist_):pos(pos_),node(node_),dist(dist_){str="";};
};


//U,R,D,L
const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
const string dir="URDL";

vector<int> ans;

bool solve(){
    int n,m;
    cin>>n>>m;
    if(n==0 && m==0)return false;

    P start,goal;
    vector<string> s(n);
    for(int i=0;i<n;i++){
        cin>>s[i];
        for(int j=0;j<m;j++){
            if(s[i][j]=='S'){
                start={i,j};
            }
            if(s[i][j]=='G'){
                goal={i,j};
            }
        }
    }
    int p;
    cin>>p;

    Aho_Corasick trie;
    vector<string> terms(p);
    for(int i=0;i<p;i++){
        cin>>terms[i];
        trie.add(terms[i]);
    }
    trie.bfs();
    int sz=trie.trie.size();
    
    using TP=tuple<int,int,int>;
    queue<State> que;
    map<TP,int> used;//同じ状態を二度と踏まないようにするため
    que.push(State{start,trie.root,0});
    used[make_tuple(start.first,start.second,trie.root)]=0;
    const int inf=1<<30;
    int res=inf;

    while(!que.empty()){
        State now_state=que.front();
        P pos=now_state.pos;
        int node=now_state.node;
        int d=now_state.dist;
        
        que.pop();
        if(pos==goal){
           //cout<<now_state.str<<endl;
            res=d;
            break;
               
        }

        for(int k=0;k<4;k++){
            int nx = pos.second + dx[k];
            int ny = pos.first + dy[k];

            if(nx<0 || m<=nx || ny<0 || n<=ny) continue;
            if(s[ny][nx]=='#') continue;

            //いまいるnodeからdir[k]をつけ足す場合にどこへいくか
            optional<int> res=trie.go(node,dir[k]);
          
            int next_node=0;
            if(!trie.go(node,dir[k])){
                //失敗した場合に,そこから文字dir[k]を用いて次に行くべき場所
                int f=trie.failure[node];
                while(!trie.go(f,dir[k])){
                    f=trie.failure[f];
                }
                next_node=*trie.go(f,dir[k]);


            }else{
                //次に行くべき場所.確実にわかっている
                next_node=*trie.go(node,dir[k]);
            }
            
            if(trie.output[next_node].size()==0){
                //next_nodeは終端文字でない
                State next_state{P{ny,nx},next_node,d+1};
                
                next_state.str=now_state.str+dir[k];//debugの際に使用

                if(!used.count(make_tuple(ny,nx,next_node))){
                    used[make_tuple(ny,nx,next_node)]=d+1;
                    que.push(next_state);
                   
                }
            }
            


        }
    }

    res=(res==inf?-1:res);
    ans.push_back(res);

    return true;

}


int main(){
    
    while(1){
       if(!solve()){
        break;
       }
    }
    

    for(int v:ans){
        cout<<v<<endl;
    }



}
