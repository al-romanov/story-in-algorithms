#ifndef STORY_IN_ALGORITHMS_INCLUDE_COUNT_INVERSIONS_H_
#define STORY_IN_ALGORITHMS_INCLUDE_COUNT_INVERSIONS_H_

#include <algorithm>
#include <cstddef>
#include <vector>

namespace algos {

template <typename T>
struct CountInversionsResult {
    std::vector<T> arr;
    size_t n_inversions = 0;
};

template <typename T>
CountInversionsResult<T>
CountInversionsSplit_(const std::vector<T> &arr1, const std::vector<T> &arr2) {
    CountInversionsResult<T> res;
    res.arr = std::vector<T>(arr1.size() + arr2.size());
    auto it1 = arr1.begin();
    auto it2 = arr2.begin();
    auto it = res.arr.begin();
    for (; it1 != arr1.end() && it2 != arr2.end(); ++it) {
        if (*it1 <= *it2) {
            *it = *it1++;
        }
        else {
            *it = *it2++;
            res.n_inversions += arr1.end() - it1;
        }
    }
    if (it1 == arr1.end()) {
        std::copy(it2, arr2.end(), it);
    }
    else {
        std::copy(it1, arr1.end(), it);
    }
    return res;
}

template <typename RandomAccessIt>
CountInversionsResult<typename RandomAccessIt::value_type>
CountInversions_(RandomAccessIt beg, RandomAccessIt end) {
    CountInversionsResult<typename RandomAccessIt::value_type> res;
    ptrdiff_t size = end - beg;
    if (size < 2) {
        std::copy(beg, end, std::back_inserter(res.arr));
        return res;
    }
    auto res1 = CountInversions_(beg, beg + size / 2);
    auto res2 = CountInversions_(beg + size / 2, end);
    auto res3 = CountInversionsSplit_(res1.arr, res2.arr);
    res.arr = res3.arr;
    res.n_inversions = res1.n_inversions + res2.n_inversions + res3.n_inversions;
    return res;
}

/*
    Counts inversions in sequence between random-access iterators [beg; end).
    Complexity O(n*log(n)).
*/
template <typename RandomAccessIter>
size_t CountInversions(RandomAccessIter beg, RandomAccessIter end) {
    return CountInversions_(beg, end).n_inversions;
}

}

#endif  // STORY_IN_ALGORITHMS_INCLUDE_COUNT_INVERSIONS_H_