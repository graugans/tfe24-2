#include <catch2/catch_test_macros.hpp>
#include "point.hpp"

TEST_CASE("Point: Constructors", "[point]") {
    SECTION("Init with values") {
        Point p{2, 3};
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 3);
    }
    SECTION("Default constructor") {
        Point p;
        REQUIRE(p.x == 0);
        REQUIRE(p.y == 0);
    }
}

TEST_CASE("Point: move works with positive and negative offsets", "[point]") {
    Point p{1, 1};
    p.move(2, -3);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == -2);

    SECTION("Consecutive moves are additive") {
        p.move(-1, 4);
        REQUIRE(p.x == 2); // 3 + (-1)
        REQUIRE(p.y == 2); // -2 + 4
    }
}

TEST_CASE("Point: distance_to correctness and properties", "[point]") {
    Point a{0, 0};
    Point b{3, 4};
    REQUIRE( a.distance_to(b) == Approx(5.0).margin(1e-12) );
    REQUIRE( b.distance_to(a) == Approx(5.0).margin(1e-12) );
    REQUIRE( a.distance_to(a) == Approx(0.0).margin(1e-12) );

    SECTION("Symmetry") {
        REQUIRE(a.distance_to(b) == b.distance_to(a));
    }
}

TEST_CASE("Point: edge cases", "[point]") {
    SECTION("Large coordinates") {
        Point p1{1000000, -1000000};
        Point p2{-1000000, 1000000};
        auto d = p1.distance_to(p2);
        REQUIRE(d >= 0.0);
    }

    SECTION("Many consecutive moves stability") {
        Point p{0,0};
        for (int i = 0; i < 10000; ++i) {
            p.move(1, -1);
        }
        REQUIRE(p.x == 10000);
        REQUIRE(p.y == -10000);
    }
}
