#include <fmt/chrono.h>
#include <fmt/format.h>
#include <cassert>
#include <string>

#include "CLI/CLI.hpp"
#include "config.h"
#include "myvector.hpp"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    // Test 1: Default constructor
    {
        mystd::myvector<int> v;
        assert(v.size() == 0);
        assert(v.capacity() == 0);
        fmt::println("✓ Test 1: Default constructor passed");
    }

    // Test 2: Constructor with size
    {
        mystd::myvector<int> v(5);
        assert(v.size() == 5);
        assert(v.capacity() >= 5);
        fmt::println("✓ Test 2: Constructor with size passed");
    }

    // Test 3: push_back
    {
        mystd::myvector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        assert(v.size() == 3);
        assert(v[0] == 1);
        assert(v[1] == 2);
        assert(v[2] == 3);
        fmt::println("✓ Test 3: push_back passed");
    }

    // Test 4: at() with bounds checking
    {
        mystd::myvector<int> v;
        v.push_back(10);
        v.push_back(20);
        assert(v.at(0) == 10);
        assert(v.at(1) == 20);
        
        try {
            v.at(5);
            assert(false); // Should not reach here
        } catch (const std::out_of_range&) {
            fmt::println("✓ Test 4: at() bounds checking passed");
        }
    }

    // Test 5: Copy constructor
    {
        mystd::myvector<int> v1;
        v1.push_back(100);
        v1.push_back(200);
        
        mystd::myvector<int> v2 = v1;
        assert(v2.size() == 2);
        assert(v2[0] == 100);
        assert(v2[1] == 200);
        fmt::println("✓ Test 5: Copy constructor passed");
    }

    // Test 6: Copy assignment operator
    {
        mystd::myvector<int> v1;
        v1.push_back(42);
        
        mystd::myvector<int> v2;
        v2 = v1;
        assert(v2.size() == 1);
        assert(v2[0] == 42);
        fmt::println("✓ Test 6: Copy assignment operator passed");
    }

    // Test 7: resize()
    {
        mystd::myvector<int> v;
        v.push_back(1);
        v.resize(5);
        assert(v.size() == 5);
        assert(v[0] == 1);
        assert(v[1] == 0);  // Default initialized
        fmt::println("✓ Test 7: resize() passed");
    }

    // Test 8: reserve()
    {
        mystd::myvector<int> v;
        size_t old_cap = v.capacity();
        v.reserve(100);
        assert(v.capacity() >= 100);
        fmt::println("✓ Test 8: reserve() passed");
    }

    // Test 9: clear()
    {
        mystd::myvector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.clear();
        assert(v.size() == 0);
        fmt::println("✓ Test 9: clear() passed");
    }

    // Test 10: Template with strings
    {
        mystd::myvector<std::string> sv;
        sv.push_back("hello");
        sv.push_back("world");
        assert(sv.size() == 2);
        assert(sv[0] == "hello");
        assert(sv[1] == "world");
        fmt::println("✓ Test 10: Template with strings passed");
    }

    fmt::println("\n✓ All tests passed!");

    return 0; /* exit gracefully*/
}
