#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q5; see 题面.pdf.
namespace aim::q5 {


// BEGIN IMPLEMENTATION
// aim-cpp-cw-known
std::vector<std::vector<int>> risk(const std::vector<std::string>& grid) {
    if(grid.empty()){
        return {};
    }
    std::size_t rows=grid.size();
    std::size_t cols=grid[0].size();
    if (cols==0){
        throw std::invalid_argument("Grid cannot have zero columns");
    }
    for (const auto& row : grid) {
        if (row.size()!=cols) {
            throw std::invalid_argument("Inconsistent row length");
        }
        for (char ch : row) {
            if (ch!='.'&&ch!='#') {
                throw std::invalid_argument("Invalid character in grid");
            }
        }
    }
    std::vector<std::vector<int>> out(rows,std::vector<int>(cols,0));
    const int dr[4]={-1,1,0,0};
    const int dc[4]={0,0,-1,1};
    for (std::size_t i=0;i<rows;i++){
        for (std::size_t c=0;c<cols;c++){
            if(grid[i][c]=='#'){
                out[i][c]=-1;
            }else{
                int count=0;
                for (int d=0;d<4;++d){
                    int nr = static_cast<int>(i)+dr[d];
                    int nc = static_cast<int>(c)+dc[d];
                    if(nr>=0&&nr< static_cast<int>(rows)&&nc>=0&&nc< static_cast<int>(cols)){
                        if(grid[nr][nc]=='#'){
                            ++count;
                        }
                    }
                }
                out[i][c]=count;
            }
        }
    }
    return out;
 }
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q5;
int main() {
    try {
        { CHECK((risk({".#",".."})==std::vector<std::vector<int>>{{1,-1},{0,1}})); }
        { CHECK(risk({}).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
