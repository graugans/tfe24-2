// 001-TestCase.cpp
#include <catch2/catch_test_macros.hpp>

// For approximate floating-point comparisons
#include <catch2/catch_approx.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// Include the Point class header
#include "point/point.hpp"

TEST_CASE("Point: Konstruktoren") {
    SECTION("Init mit Werten") {
        Point<double> p{2, 3};
        REQUIRE(p.getX() == 2);
        REQUIRE(p.getY() == 3);
    }
    SECTION("Default-Konstruktor") {
        Point<int> p;
        REQUIRE(p.getX() == 0);
        REQUIRE(p.getY() == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ") {
    Point<double> p{1, 1};
    p.move(2, -3);
    REQUIRE(p.getX() == 3);
    REQUIRE(p.getY() == -2);
}

TEST_CASE("Printing of the point in a testcase") {
    Point<double> p{1, 1};
    p.move(2, -3);
    REQUIRE(p.getX() == 3);
    REQUIRE(p.getY() == -2);
    //fmt::println("Point p after move: {}", p);
}

TEST_CASE("Point: distance_to – euklidisch & robust") {
    Point a{0, 0};
    Point b{3, 4};

    // Zum Vergleich von Gleitkommazahlen
    // https://github.com/catchorg/Catch2/blob/devel/docs/comparing-floating-point-numbers.md#comparing-floating-point-numbers-with-catch2

    // See: https://github.com/catchorg/Catch2/blob/devel/docs/comparing-floating-point-numbers.md#approx
    REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( b.distance_to(a) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( a.distance_to(a) == Catch::Approx(0.0).margin(1e-12) );

    // Alternative mit Matchern
    REQUIRE_THAT(a.distance_to(b),  Catch::Matchers::WithinRel(5.0, 1e-12));
    REQUIRE_THAT(b.distance_to(a),  Catch::Matchers::WithinRel(5.0, 1e-12));
    REQUIRE_THAT(a.distance_to(a),  Catch::Matchers::WithinRel(0.0, 1e-12));
}