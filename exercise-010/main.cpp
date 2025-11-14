#include <fmt/chrono.h>
#include <fmt/format.h>

#include "myvector.hpp"
#include <cassert>
#include <string>

int main() {
    using mystd::myvector;

    myvector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    assert(v.size() == 3);
    assert(v.at(0) == 1);
    assert(v[1] == 2);

    v.resize(10);
    v.clear();

    return 0;
}
