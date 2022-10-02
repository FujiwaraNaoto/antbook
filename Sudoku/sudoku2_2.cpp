/*
解くための時間を図る処理も搭載させる

抽象クラスのインスタンスは作成むり

基底クラスのインスタンスは作成が可能.
*/
#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<tuple>
#include<cstdlib>
#include<chrono>
#include<functional>
#include<cstdio>
#include<thread>

//////////// 時間を計測する処理(使用しない)///////////
template<typename Time=std::chrono::microseconds,
    typename Clock=std::chrono::high_resolution_clock>
    struct perf_timer
    {
        template<typename F,typename... Args>
        static Time duration(F&& f,Args... args)
        {
            auto start=Clock::now();
            std::invoke(std::forward<F>(f),std::forward<Args>(args)...);
            auto end=Clock::now();

            return std::chrono::duration_cast<Time>(end-start);
        }
    };

using namespace std::chrono_literals;

//////////////////////////////////////////////////////////////////




//基底クラス
/*

Solve_Sudoku -> Solve_Sudoku_Recursive -> Solve_Sudoku_Recursive_Opt

*/
//抽象クラスにはしなかった..
class Solve_Sudoku{
     public:
        int back_tracks;
        std::vector<std::vector<int>> grid;
        //コンストラクタはvirtualにしない
        Solve_Sudoku(){
        }

        virtual ~Solve_Sudoku(){
            /*
            ここにvirtualをつけておくことで, Solve_Sudokuを継承しているSolve_Sudoku_Recursiveが自動的に仮想関数となり,
             Solve_Sudoku_Recursive を継承しているSolve_Sudoku_Recursive_Optのデストラクタでsectorsのメモリ解法が行われる
            */
            //virtualにしておかないと
            //std::vector<std::vector<int>>().swap(grid);
        }

        virtual std::pair<int,int> findNextCellToFill(){
            return std::make_pair(-1,-1);
        }

        virtual bool isValid(int y,int x,int e){
            return true;
        }
        virtual bool solveSudoku(int ,int ){
            //override される前提
            return true;
        }
    
};


//
class Solve_Sudoku_Recursive : public Solve_Sudoku{
    //基底クラスのコンストラクタは暗黙理裏に呼び出される
    //とデストラクタが呼ばれる?
    // P164かな

    public:
    //コンストラクタ
    Solve_Sudoku_Recursive(): Solve_Sudoku(){
        back_tracks=0;
        grid=std::vector<std::vector<int>>(9,std::vector<int>(9,0));
    };
     
     virtual ~Solve_Sudoku_Recursive() override {
         
         std::vector<std::vector<int>>().swap(grid);
     };
     //これでSolve_Sudokuの　デストラクタがoverrideされる
    // まあ,基底クラスの仮想関数と同一仕様のメンバ関数は自動的に仮想関数となるため,virtualをつける必要がなかったかも...

    

    std::pair<int,int> findNextCellToFill()override{
        for(int y=0;y<9;y++){
            for(int x=0;x<9;x++){
                if(grid[y][x]==0){
                    return std::make_pair(y,x);
                }
            }
        }

        return std::make_pair(-1,-1);
    }

    bool isValid(int y,int x,int e)override{
        int groupy=y/3;
            int groupx=x/3;
            std::set<int> st;
            for(int dy=0;dy<3;dy++){
                 for(int dx=0;dx<3;dx++){
                     st.insert(grid[groupy*3+dy][groupx*3+dx]);
            }
             }

             for(int d=0;d<9;d++){
                 st.insert(grid[d][x]);
                 st.insert(grid[y][d]);
             }

             return !st.count(e);//0ならtrue
        }


    bool solveSudoku(int i=0,int j=0) override{//一番左上のマスから行う
            auto [y,x]=findNextCellToFill();
            if(y==-1) return true;

            for(int e=1;e<=9;e++){
                if(isValid(y,x,e)){
                    grid[y][x]=e;
                    if(solveSudoku(y,x)){
                        return true;//解くことができた場合
                    }else{
                        back_tracks+=1;
                        grid[y][x]=0;//戻す
                    }
                }
            }
            return false;//解くことが無理な場合
        }

    
};


class Solve_Sudoku_Recursive_Opt : public Solve_Sudoku_Recursive{
    
    public: 

        std::vector<std::tuple<int,int,int,int>> sectors;

        Solve_Sudoku_Recursive_Opt():Solve_Sudoku_Recursive(){
            
            for(int y=0;y<9;y+=3){
                for(int x=0;x<9;x+=3){
                    //[y,y+3), [x,x+3)
                    sectors.emplace_back(y,y+3,x,x+3);
                }
            }
        }

        ~Solve_Sudoku_Recursive_Opt(){
            //sectorsのメモリを解法させる
            
            std::vector<std::tuple<int,int,int,int>>().swap(sectors);
        
            /*
            Solve_Sudoku_Recursive_Opt インスタンスを
            ポインタSolve_Sudoku_Recursiveで受けたとしても,
            Solve_Sudoku_Recursiveのデストラクタが仮想関数なので,
            std::vector<std::tuple<int,int,int,int>>().swap(sectors);
            が自動的に呼び出される.

            */
           
        }

        

        void undoImplications(std::vector<std::tuple<int,int,int>> impl){
            for(auto [y,x,_]:impl){
                grid[y][x]=0;
            }
        }

     
        std::vector<std::tuple<int,int,int>> makeImplications(int i,int j,int e){//xがj,yがi
            grid[i][j]=e;
            std::vector<std::tuple<int,int,int>> impl={std::make_tuple(i,j,e)};
            
            for(auto [b_up,b_bottom,b_left,b_right]:sectors){//各ブロック　合計9つのブロックを調べる
                //[b_left,b_right),[b_up,b_bottom)

                std::set<int> candidate={1,2,3,4,5,6,7,8,9};
                
                for(int y=b_up;y<b_bottom;y++){//[b_up,b_bottom)
                    for(int x=b_left;x<b_right;x++){//[block_left,block_right)

                        //blockの部分
                        if(grid[y][x]!=0){
                            candidate.erase(candidate.find(grid[y][x]));
                        }
                    }
                }

                std::vector<std::tuple<int,int,std::set<int>>> sectinfo;

                for(int y=b_up;y<b_bottom;y++){//[b_up,b_bottom)
                    for(int x=b_left;x<b_right;x++){//[block_left,block_right)

                        //blockの部分
                        if(grid[y][x]==0){
                            //(y,x)にはcandidateの要素が入りうることを示している
                            sectinfo.emplace_back(y,x,candidate);
                        }
                    }
                }

                for(auto [sin_y,sin_x,st]:sectinfo){//(siny,sinx)には,集合stの要素が入りうる
                    for(int y=0;y<9;y++){
                        if(st.count(grid[y][sin_x])){//ここのif大事 sin_x列目を見てみる
                            st.erase(st.find(grid[y][sin_x]));
                        }
                    }

                    for(int x=0;x<9;x++){
                        if(st.count(grid[sin_y][x])){//sin_y行目を見てみる
                            st.erase(st.find(grid[sin_y][x]));
                        }
                    }

                    if(st.size()==1){
                        int val=*st.begin();
                        
                        if(isValid(sin_y,sin_x,val)){
                            grid[sin_y][sin_x]=val;
                            impl.emplace_back(sin_y,sin_x,val);
                        }
                    }    
                }

            }

            return impl;
        }

        bool solveSudoku(int i=0,int j=0) override{//一番左上のマスから行う
                auto [y,x]=findNextCellToFill();
                if(y==-1) return true;

                for(int e=1;e<=9;e++){
                    if(isValid(y,x,e)){
                    
                        auto impl=makeImplications(y,x,e);
                    
                        if(solveSudoku(y,x)){
                            return true;//解くことができた場合
                        }else{
                            back_tracks+=1;
                            undoImplications(impl);
                            
                        }
                    }
                }

                return false;//解くことが無理な場合

            }
};


//これ,overrideするべきでは?
//is-Aの関係があるので　問題ない
void printSudoku(const Solve_Sudoku_Recursive& sudoku){
     std::cout<<"back track="<<sudoku.back_tracks<<std::endl;

    for(int y=0;y<9;y++){
        for(int x=0;x<9;x++){
                        
            std::cout<<sudoku.grid[y][x]<<(x%3==2 ? "|":" ");
        }
        std::cout<<std::endl;
            if(y%3==2){
                for(int x=0;x<9;x++){
                    std::cout<<"=";
                }
                std::cout<<std::endl;
            }
        }
}




int main(int argc,char* argv[]){
    std::string inputfile;
   
    if(argc==1){//引数が無しの場合
        inputfile="sudoku_sample1.txt";
        
    }else{
        inputfile=argv[1];

    }

    std::ifstream fis(inputfile);

    Solve_Sudoku_Recursive sudoku1;
    Solve_Sudoku_Recursive_Opt sudoku2;

    if(!fis){
        std::cerr<<inputfile<<" cannot be opened"<<std::endl;
    }else{
        int line=0;
        while(true){
            std::string text;
            getline(fis,text);
            if(!fis) break;
            for(int i=0;i<text.size();i++){
                sudoku1.grid[line][i]=text[i]-'0';
                sudoku2.grid[line][i]=text[i]-'0';
            }
            line++;
        }

    }
    auto tic1=std::chrono::steady_clock::now();
    bool flag1=sudoku1.solveSudoku();
    auto toc1=std::chrono::steady_clock::now();
    double  elapsed_time1 = std::chrono::duration<double>(toc1 - tic1).count();
    printf("msec = %20.10f\n",elapsed_time1);
  
    if(flag1){
       
        printSudoku(sudoku1);
    }else{
         std::cout<<"Unsolvable"<<std::endl;
        
    }

    auto tic2=std::chrono::steady_clock::now();
    bool flag2=sudoku2.solveSudoku();
    auto toc2=std::chrono::steady_clock::now();
    double  elapsed_time2 = std::chrono::duration<double>(toc2 - tic2).count();
    printf("msec = %20.10f\n",elapsed_time2);
  
    if(flag2){
       
        printSudoku(sudoku2);
    }else{
         std::cout<<"Unsolvable"<<std::endl;
        
    }

    printf("-----------For testing destructor-------------------\n");

    {

        Solve_Sudoku_Recursive *p = new Solve_Sudoku_Recursive_Opt();
        delete p;

    }
    printf("----------------------------------------------------\n");

}
    