#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <catch2/catch_approx.hpp>
#include "point.hpp"

TEST_CASE("Point: Konstruktoren") {
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

TEST_CASE("Point: move verschiebt relativ") {
    Point p{1, 1};
    p.move(2, -3);
    REQUIRE(p.x == 3);
    REQUIRE(p.y == -2);
}

TEST_CASE("Point: distance_to – euklidisch & robust") {
    Point a{0, 0};
    Point b{3, 4};
	REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
	REQUIRE( b.distance_to(a) == Catch::Approx(5.0).margin(1e-12) );
	REQUIRE( a.distance_to(a) == Catch::Approx(0.0).margin(1e-12) );
}

TEST_CASE("Point: Edge-Cases – große/negative Werte und Stabilität") {
	SECTION("Große und negative Koordinaten") {
		Point large{INT32_MAX, INT32_MIN};
		Point other{-1000000, 1000000};
		// distance_to sollte keine Integer-Überläufe haben (interne Verwendung von double)
		double d = large.distance_to(other);
		REQUIRE( d >= 0.0 );
	}

	SECTION("Stabilität bei vielen aufeinanderfolgenden move-Aufrufen") {
		Point p{0, 0};
		const int N = 10000;
		for (int i = 0; i < N; ++i) p.move(1, -1);
		REQUIRE(p.x == N);
		REQUIRE(p.y == -N);
	}

	SECTION("Dreiecksungleichung (sanity check)") {
		Point a{0,0};
		Point b{1,1};
		Point c{4,5};
		double ac = a.distance_to(c);
		double ab = a.distance_to(b);
		double bc = b.distance_to(c);
	REQUIRE( ac <= Catch::Approx(ab + bc).margin(1e-12) );
	}
}
