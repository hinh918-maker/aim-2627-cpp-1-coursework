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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
// aim-cpp-cw-known
int select_target(const std::vector<Target>& targets, int max_range) {
    if (max_range<0){
        return -1;
    }
    long long max_d2=static_cast<long long>(max_range)*max_range;
    int best_id=-1;
    long long best_hp=0;
    long long best_d2=0;
    for(const auto& t:targets){
        if(!t.visible||t.hp<=0){
            continue;
        }
        long long d2=static_cast<long long>(t.x)*t.x+static_cast<long long>(t.y)*t.y;
        if(d2>max_d2){
            continue;
        }
        if (best_id==-1||t.hp<best_hp
            ||(t.hp==best_hp&&(d2<best_d2||(d2==best_d2&&t.id<best_id)))){
            best_id=t.id;
            best_hp=t.hp;
            best_d2=d2;
        }
    }
    return best_id;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
