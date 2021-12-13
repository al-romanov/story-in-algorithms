#include "count-inversions.h"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 4, 2, 8};
    std::cout << algos::CountInversions(v.begin(), v.end()) << std::endl;
    return 0;
}