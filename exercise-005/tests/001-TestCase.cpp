// 001-TestCase.cpp
// And write tests in the same file:
#include <catch2/catch_test_macros.hpp>
#include <algorithm>
static auto factorial(int number) -> int
{
    // return number <= 1 ? number : Factorial( number - 1 ) * number;  // fail
    return number <= 1 ? 1 : factorial(number - 1) * number;  // pass
}

class Triangle
{
   public:
    Triangle(double a, double b, double c) : sideA(a), sideB(b), sideC(c) {}
    auto isRectangular() const -> bool
    {
        double sides[3] = {sideA, sideB, sideC};
        std::sort(sides, sides + 3);
        return (sides[0] * sides[0] + sides[1] * sides[1]) == (sides[2] * sides[2]);
    }

   private:
    double sideA;
    double sideB;
    double sideC;
};

class TriangleFixture
{
   protected:
    Triangle t1{3.0, 4.0, 5.0};
    Triangle t2{2.0, 2.0, 3.0};
    void setup()
    {
        // Vorbereitung (z. B. Ressourcen initialisieren)
    }
    void teardown()
    {
        // Aufräumarbeiten (z. B. Dateien schließen)
    }
};
TEST_CASE_METHOD(TriangleFixture, "Prüfung auf rechtwinkliges Dreieck", "[triangle]")
{
    setup();
    REQUIRE(t1.isRectangular());
    teardown();
}

TEST_CASE_METHOD(TriangleFixture, "Prüfung auf ungleichseitiges Dreieck", "[triangle]") 
{
setup();
REQUIRE_FALSE(t2.isRectangular());
teardown();
}

TEST_CASE("Factorial of 0 is 1 (fail)", "[single-file]")
{
    REQUIRE(factorial(0) == 1);
}

TEST_CASE("Factorials of 1 and higher are computed (pass)", "[single-file]")
{
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}

// Compile & run:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -o 010-TestCase 010-TestCase.cpp && 010-TestCase --success
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% 010-TestCase.cpp && 010-TestCase --success

// Expected compact output (all assertions):
//
// prompt> 010-TestCase --reporter compact --success
// 010-TestCase.cpp:14: failed: Factorial(0) == 1 for: 0 == 1
// 010-TestCase.cpp:18: passed: Factorial(1) == 1 for: 1 == 1
// 010-TestCase.cpp:19: passed: Factorial(2) == 2 for: 2 == 2
// 010-TestCase.cpp:20: passed: Factorial(3) == 6 for: 6 == 6
// 010-TestCase.cpp:21: passed: Factorial(10) == 3628800 for: 3628800 (0x375f00) == 3628800 (0x375f00)
// Failed 1 test case, failed 1 assertion.