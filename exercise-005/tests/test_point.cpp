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
    SECTION("Negative Koordinaten") {
        Point p{-5, -10};
        REQUIRE(p.x == -5);
        REQUIRE(p.y == -10);
    }
    SECTION("Eine Koordinate null") {
        Point p1{0, 42};
        Point p2{42, 0};
        REQUIRE(p1.x == 0);
        REQUIRE(p1.y == 42);
        REQUIRE(p2.x == 42);
        REQUIRE(p2.y == 0);
    }
}

TEST_CASE("Point: move verschiebt relativ", "[point]") {
    SECTION("Positive Verschiebung") {
        Point p{1, 1};
        p.move(2, 3);
        REQUIRE(p.x == 3);
        REQUIRE(p.y == 4);
    }

    SECTION("Negative Verschiebung") {
        Point p{5, 5};
        p.move(-2, -3);
        REQUIRE(p.x == 3);
        REQUIRE(p.y == 2);
    }

    SECTION("Gemischte positive und negative Verschiebung") {
        Point p{1, 1};
        p.move(2, -3);
        REQUIRE(p.x == 3);
        REQUIRE(p.y == -2);
    }

    SECTION("Verschiebung um null ändert nichts") {
        Point p{5, 10};
        p.move(0, 0);
        REQUIRE(p.x == 5);
        REQUIRE(p.y == 10);
    }

    SECTION("Mehrere aufeinanderfolgende Moves sind assoziativ") {
        Point p{0, 0};
        p.move(1, 2);
        p.move(3, 4);
        p.move(-2, 1);
        REQUIRE(p.x == 2);
        REQUIRE(p.y == 7);
    }

    SECTION("Move von negativem Punkt zu positivem") {
        Point p{-5, -3};
        p.move(8, 5);
        REQUIRE(p.x == 3);
        REQUIRE(p.y == 2);
    }
}

TEST_CASE("Point: distance_to – euklidisch & robust", "[point]") {
    SECTION("Klassisches 3-4-5 Dreieck") {
        Point a{0, 0};
        Point b{3, 4};
        REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
        REQUIRE( b.distance_to(a) == Catch::Approx(5.0).margin(1e-12) );
    }

    SECTION("Distanz zu sich selbst ist null") {
        Point p{7, 11};
        REQUIRE( p.distance_to(p) == Catch::Approx(0.0).margin(1e-12) );
    }

    SECTION("Symmetrie: dist(a, b) == dist(b, a)") {
        Point a{1, 2};
        Point b{4, 6};
        REQUIRE( a.distance_to(b) == Catch::Approx(b.distance_to(a)).margin(1e-12) );
    }

    SECTION("Distanz auf x-Achse") {
        Point a{0, 0};
        Point b{5, 0};
        REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    }

    SECTION("Distanz auf y-Achse") {
        Point a{0, 0};
        Point b{0, 7};
        REQUIRE( a.distance_to(b) == Catch::Approx(7.0).margin(1e-12) );
    }

    SECTION("Negative Koordinaten") {
        Point a{-3, -4};
        Point b{0, 0};
        REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    }

    SECTION("Beide Punkte mit negativen Koordinaten") {
        Point a{-1, -1};
        Point b{-4, -5};
        REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    }

    SECTION("Große Koordinaten") {
        Point a{1000000, 1000000};
        Point b{1000003, 1000004};
        REQUIRE( a.distance_to(b) == Catch::Approx(5.0).margin(1e-12) );
    }

    SECTION("Sehr große Koordinaten mit Cast zu double") {
        Point a{1000000, 2000000};
        Point b{1000001, 2000001};
        REQUIRE( a.distance_to(b) == Catch::Approx(std::sqrt(2.0)).margin(1e-12) );
    }
}

TEST_CASE("Point: Edge cases", "[point]") {
    SECTION("Große negative zu große positive Koordinaten") {
        Point a{INT_MIN/2, INT_MIN/2};
        Point b{INT_MAX/2, INT_MAX/2};
        // only check that function returns a finite positive number and is symmetric
        double d1 = a.distance_to(b);
        double d2 = b.distance_to(a);
        REQUIRE( d1 == Catch::Approx(d2).margin(1e-12) );
        REQUIRE( d1 > 0.0 );
    }

    SECTION("Stabilität bei vielen aufeinanderfolgenden Moves") {
        Point p{0, 0};
        for (int i = 0; i < 1000; ++i) {
            p.move(1, -1);
        }
        REQUIRE(p.x == 1000);
        REQUIRE(p.y == -1000);
    }

    SECTION("Dreiecksungleichung: dist(a,c) ≤ dist(a,b) + dist(b,c)") {
        Point a{0, 0};
        Point b{3, 4};
        Point c{6, 0};
        
        double dist_ac = a.distance_to(c);
        double dist_ab = a.distance_to(b);
        double dist_bc = b.distance_to(c);
        
        // Dreiecksungleichung: die direkte Distanz sollte ≤ Umweg sein
        REQUIRE(dist_ac <= dist_ab + dist_bc + 1e-9);
    }

    SECTION("Collineare Punkte (auf einer Linie)") {
        Point a{0, 0};
        Point b{2, 2};
        Point c{4, 4};
        
        // a -> b -> c sollten auf einer Linie sein
        // dist(a, c) sollte == dist(a, b) + dist(b, c) sein
        double dist_ac = a.distance_to(c);
        double dist_ab = a.distance_to(b);
        double dist_bc = b.distance_to(c);
        
        REQUIRE(dist_ac == Catch::Approx(dist_ab + dist_bc).margin(1e-12));
    }
}
