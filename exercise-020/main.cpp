#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include "vehicle.hpp"

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
    fmt::print("{}\n", app.get_name());
    fmt::print("{}\n", std::string(60, '='));

    // Beispiel 1: Auto mit Verbrennungsmotor
    fmt::print("\n--- Beispiel 1: Auto mit Verbrennungsmotor ---\n");
    auto car1 = Car{"WVWZZZ3CZ9E123456", 1200.0, 
                    std::make_unique<CombustionEngine>(50.0, 8.5)};
    fmt::print("Auto VIN: {}\n", car1.vin());
    fmt::print("Typ: {}\n", car1.type());
    fmt::print("Motor: {}\n", car1.motor()->label());
    fmt::print("Anfängliche Reichweite: {:.2f} km\n", car1.range_km());
    car1.drive(100.0);
    fmt::print("Reichweite nach 100 km: {:.2f} km\n", car1.range_km());

    // Beispiel 2: Auto mit Elektromotor
    fmt::print("\n--- Beispiel 2: Auto mit Elektromotor ---\n");
    auto car2 = Car{"TMBSM53S002E06666", 1400.0, 
                    std::make_unique<ElectricMotor>(60.0, 22.0)};
    fmt::print("Auto VIN: {}\n", car2.vin());
    fmt::print("Typ: {}\n", car2.type());
    fmt::print("Motor: {}\n", car2.motor()->label());
    fmt::print("Anfängliche Reichweite: {:.2f} km\n", car2.range_km());
    car2.drive(150.0);
    fmt::print("Reichweite nach 150 km: {:.2f} km\n", car2.range_km());

    // Beispiel 3: Lastkraftwagen mit Verbrennungsmotor
    fmt::print("\n--- Beispiel 3: Lastkraftwagen mit Verbrennungsmotor ---\n");
    auto truck = Truck{"DAIMLER00000000001", 5000.0, 
                       std::make_unique<CombustionEngine>(150.0, 25.0)};
    fmt::print("Truck VIN: {}\n", truck.vin());
    fmt::print("Typ: {}\n", truck.type());
    fmt::print("Motor: {}\n", truck.motor()->label());
    fmt::print("Anfängliche Reichweite: {:.2f} km\n", truck.range_km());
    truck.drive(200.0);
    fmt::print("Reichweite nach 200 km: {:.2f} km\n", truck.range_km());

    // Beispiel 4: Motorrad mit Hybridmotor
    fmt::print("\n--- Beispiel 4: Motorrad mit Hybridmotor ---\n");
    auto motorcycle = Motorcycle{"HONDA00000000001", 200.0, 
                                 std::make_unique<HybridMotor>(15.0, 3.0)};
    fmt::print("Motorrad VIN: {}\n", motorcycle.vin());
    fmt::print("Typ: {}\n", motorcycle.type());
    fmt::print("Motor: {}\n", motorcycle.motor()->label());
    fmt::print("Anfängliche Reichweite: {:.2f} km\n", motorcycle.range_km());
    motorcycle.drive(50.0);
    fmt::print("Reichweite nach 50 km: {:.2f} km\n", motorcycle.range_km());

    fmt::print("\n" + std::string(60, '=') + "\n");
    fmt::print("Exercise 020 abgeschlossen!\n");

    return 0; /* exit gracefully*/
}
