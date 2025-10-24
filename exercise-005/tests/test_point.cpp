// tests/test_point.cpp
#include <catch2/catch_test_macros.hpp>
#include <climits>
#include <catch2/catch_approx.hpp>
#include "../point.hpp"

TEST_CASE("Point: Konstruktoren", "[point]") {
    SECTION("Init mit Werten") {
        Point p{2, 3};
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 3);
    }
    SECTION("Default-Konstruktor") {
        Point p;
        REQUIRE(p.x == 0);
        REQUIRE(p.y == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ", "[point]") {
    Point p{1, 1};
    p.move(2, -3);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == -2);

    SECTION("Mehrere verschiebungen aufsummiert") {
        p.move(1, 1);
        REQUIRE(p.x == 4);
        REQUIRE(p.y == -1);
    }
}

TEST_CASE("Point: distance_to – euklidisch & robust", "[point]") {
    Point a{0, 0};
    Point b{3, 4};
    REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( b.distance_to(a) == Catch::Approx(5.0).margin(1e-12) );
    REQUIRE( a.distance_to(a) == Catch::Approx(0.0).margin(1e-12) );
}

TEST_CASE("Point: Edge cases", "[point]") {
    SECTION("Große negative Koordinaten") {
        Point a{INT_MIN/2, INT_MIN/2};
        Point b{INT_MAX/2, INT_MAX/2};
        // only check that function returns a finite positive number and is symmetric
        double d1 = a.distance_to(b);
        double d2 = b.distance_to(a);
    REQUIRE( d1 == Catch::Approx(d2).margin(1e-12) );
        REQUIRE( d1 > 0.0 );
    }

    SECTION("Stabil bei vielen Moves") {
        Point p{0,0};
        for (int i=0;i<1000;++i) p.move(1,-1);
        REQUIRE(p.x == 1000);
        REQUIRE(p.y == -1000);
    }
}
