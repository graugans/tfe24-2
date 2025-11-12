// Catch2 tests for exercise-010: basic myvector behaviour
#include <catch2/catch_test_macros.hpp>
#include "../myvector.hpp"

TEST_CASE("basic operations on tfe24::myvector<int>", "[myvector][basic]") {
    tfe24::myvector<int> v;
    REQUIRE(v.size() == 0);

    SECTION("push_back grows size") {
        v.push_back(42);
        v.push_back(7);
        REQUIRE(v.size() == 2);
        REQUIRE(v[0] == 42);
        REQUIRE(v.at(1) == 7);
    }

    SECTION("resize larger fills with default values") {
        v.resize(5);
        REQUIRE(v.size() == 5);
        for (size_t i = 0; i < v.size(); ++i) {
            REQUIRE(v[i] == int{});
        }
    }

    SECTION("at throws on out of range") {
        v.push_back(1);
        REQUIRE_THROWS_AS(v.at(5), std::out_of_range);
    }
}

TEST_CASE("copy semantics (Rule of Three)", "[myvector][copy]") {
    tfe24::myvector<int> a;
    for (int i = 0; i < 3; ++i) a.push_back(i + 10);
    tfe24::myvector<int> b = a;          // Copy-Konstruktor
    tfe24::myvector<int> c; c = a;       // Copy-Zuweisung

    REQUIRE(b.size() == a.size());
    REQUIRE(c.size() == a.size());

    a[0] = 99; // Änderungen dürfen Kopien nicht beeinflussen
    REQUIRE(b[0] != a[0]);
    REQUIRE(c[0] != a[0]);
}
// End of tests