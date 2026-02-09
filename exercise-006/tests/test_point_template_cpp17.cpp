// Tests for Point<T> template class (C++17)
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../point.hpp"
#include <type_traits>

TEST_CASE("Point<T>: Construction & move (int)") {
  Point<int> p{2, 3};
  REQUIRE(p.x == 2);
  REQUIRE(p.y == 3);

  p.move(1, -4);
  REQUIRE(p.x == 3);
  REQUIRE(p.y == -1);
}

TEST_CASE("Point<T>: Construction & move (double)") {
  Point<double> p{2.5, -3.75};
  p.move(0.5, 0.25);
  REQUIRE(p.x == Catch::Approx(3.0));
  REQUIRE(p.y == Catch::Approx(-3.5));
}

TEST_CASE("Point<T>: distance_to – Type & Value") {
  Point<int> a{0, 0}, b{3, 4};
  typedef decltype(a.distance_to(b)) dist_t;
  static_assert(!std::is_same_v<dist_t, int>, "distance_to should not return int");
  REQUIRE(a.distance_to(b) == Catch::Approx(5.0).margin(1e-12));
  REQUIRE(b.distance_to(a) == Catch::Approx(5.0).margin(1e-12));
  REQUIRE(a.distance_to(a) == Catch::Approx(0.0).margin(1e-12));
}

TEST_CASE("Point<T>: fmt-Formatter") {
  Point<int> pi{1, 2};
  REQUIRE(fmt::format("{}", pi) == "(1, 2)");

  Point<double> pd{1.5, -2.7};
  REQUIRE(fmt::format("{}", pd) == "(1.5, -2.7)");
}

TEST_CASE("Point<T>: Equality Operators") {
  Point<int> p1{1, 2};
  Point<int> p2{1, 2};
  Point<int> p3{2, 3};

  REQUIRE(p1 == p2);
  REQUIRE(!(p1 != p2));
  REQUIRE(p1 != p3);
  REQUIRE(!(p1 == p3));
}

TEST_CASE("Point<T>: Default Constructor") {
  Point<int> p_int;
  REQUIRE(p_int.x == 0);
  REQUIRE(p_int.y == 0);

  Point<double> p_double;
  REQUIRE(p_double.x == Catch::Approx(0.0));
  REQUIRE(p_double.y == Catch::Approx(0.0));
}

TEST_CASE("Point<T>: Large and Negative Values") {
  Point<int> a{-1000000, 1000000};
  Point<int> b{1000000, -1000000};
  const auto dist = a.distance_to(b);
  REQUIRE(dist > 0);
  REQUIRE(dist == Catch::Approx(std::sqrt(8e12)).margin(1.0));
}

TEST_CASE("Point<T>: Multiple move operations") {
  Point<float> p{0.0f, 0.0f};
  p.move(1.5f, 2.5f);
  p.move(-0.5f, 0.5f);
  p.move(0.2f, -0.7f);
  REQUIRE(p.x == Catch::Approx(1.2f));
  REQUIRE(p.y == Catch::Approx(2.3f));
}
