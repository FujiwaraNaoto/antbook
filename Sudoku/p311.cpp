/*
数読パズル
完成
*/
#include<iostream>
#include<vector>
#include<set>
#include<fstream>
#include<tuple>
#include<chrono>

//再帰で探す
class Solve{
    public:
        int back_tracks=0;
        std::vector<std::vector<int>> grid;

        Solve(){
            int back_tracks=0;
            grid=std::vector<std::vector<int>>(9,std::vector<int>(9,0));
        }

        ~Solve(){
            std::vector<std::vector<int>>().swap(grid);
        }

        std::pair<int,int> findNextCellToFill(){
            for(int y=0;y<9;y++){
                for(int x=0;x<9;x++){
                    if(grid[y][x]==0){
                        return std::make_pair(y,x);
                    }
                }
            }

            return std::make_pair(-1,-1);
        }

        bool isValid(int y,int x,int e){
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


        bool solveSudoku(int i=0,int j=0){//一番左上のマスから行う
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



//再帰と推定で探し,余計な探索を避ける
class SolveOpt{
    public:
        int back_tracks=0;
        std::vector<std::vector<int>> grid;
        std::vector<std::tuple<int,int,int,int>> sectors;

        SolveOpt(){

            for(int y=0;y<9;y+=3){
                for(int x=0;x<9;x+=3){
                    //[y,y+3), [x,x+3)
                    sectors.emplace_back(y,y+3,x,x+3);
                }
            }

           
        


            int back_tracks=0;
            grid=std::vector<std::vector<int>>(9,std::vector<int>(9,0));
        }

        ~SolveOpt(){
            std::vector<std::vector<int>>().swap(grid);
        }

        std::pair<int,int> findNextCellToFill(){
            for(int y=0;y<9;y++){
                for(int x=0;x<9;x++){
                    if(grid[y][x]==0){
                        return std::make_pair(y,x);
                    }
                }
            }

            return std::make_pair(-1,-1);
        }

        bool isValid(int y,int x,int e){
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

        bool solveSudokuOpt(int i=0,int j=0){//一番左上のマスから行う
            auto [y,x]=findNextCellToFill();
            if(y==-1) return true;

            for(int e=1;e<=9;e++){
                if(isValid(y,x,e)){
                   
                    auto impl=makeImplications(y,x,e);
                   
                    if(solveSudokuOpt(y,x)){
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
void printSudoku(const Solve& sudoku){
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

void printSudoku(const SolveOpt& sudoku){
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

    Solve sudoku1;
    SolveOpt sudoku2;

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
    
    //printSudoku(sudoku);

    auto tic1 = std::chrono::steady_clock::now();
    bool flag1=sudoku1.solveSudoku();
    auto toc1 = std::chrono::steady_clock::now();
    double  elapsed_time1 = std::chrono::duration<double>(toc1 - tic1).count();
    //std::cout << msec << " msec" << std::endl;
    printf("msec1 = %20.10f\n",elapsed_time1);

    if(flag1){
       
        printSudoku(sudoku1);
    }else{
         std::cout<<"Unsolvable"<<std::endl;
        
    }

    auto tic2 = std::chrono::steady_clock::now();
    bool flag2=sudoku2.solveSudokuOpt();
    auto toc2 = std::chrono::steady_clock::now();
    double  elapsed_time2 = std::chrono::duration<double>(toc2 - tic2).count();
    //std::cout << msec << " msec" << std::endl;
    printf("msec2 = %20.10f\n",elapsed_time2);


    if(flag2){
       
        printSudoku(sudoku2);
    }else{
         std::cout<<"Unsolvable"<<std::endl;
        
    }


}
