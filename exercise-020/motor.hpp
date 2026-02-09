#pragma once

#include <string>

/**
 * @brief Abstrakte Basisklasse für Antriebe
 */
class IMotor
{
public:
    virtual ~IMotor() = default;

    /**
     * @brief Verfügbare Energie des Motors
     * @return Energie in kWh
     */
    virtual auto available_energy_kWh() const -> double = 0;

    /**
     * @brief Energieverbrauch für eine bestimmte Strecke
     * @param km Strecke in Kilometern
     * @param mass_kg Fahrzeugmasse in Kilogramm
     * @return Verbrauchte Energie in kWh
     */
    virtual auto consume_for_distance(double km, double mass_kg) -> double = 0;

    /**
     * @brief Beschriftung des Motors
     * @return Typ des Motors als String
     */
    virtual auto label() const -> std::string = 0;
};

/**
 * @brief Verbrennungsmotor
 */
class CombustionEngine : public IMotor
{
private:
    double fuel_l_{0.0};
    double l_per_100km_{8.0};

public:
    explicit CombustionEngine(double fuel_l = 50.0, double l_per_100km = 8.0)
        : fuel_l_{fuel_l}, l_per_100km_{l_per_100km}
    {
    }

    auto available_energy_kWh() const -> double override
    {
        // 1 Liter Diesel ≈ 9,6 kWh, 1 Liter Benzin ≈ 8,9 kWh
        return fuel_l_ * 8.9;
    }

    auto consume_for_distance(double km, double mass_kg) -> double override
    {
        // Verbrauch erhöht sich leicht mit Fahrzeugmasse
        double consumption = (km / 100.0) * l_per_100km_ * (1.0 + (mass_kg - 1000.0) / 10000.0);
        fuel_l_ -= consumption;
        return consumption * 8.9; // in kWh
    }

    auto label() const -> std::string override
    {
        return "Combustion Engine";
    }
};

/**
 * @brief Elektromotor
 */
class ElectricMotor : public IMotor
{
private:
    double battery_kwh_{60.0};
    double kwh_per_100km_{20.0};

public:
    explicit ElectricMotor(double battery_kwh = 60.0, double kwh_per_100km = 20.0)
        : battery_kwh_{battery_kwh}, kwh_per_100km_{kwh_per_100km}
    {
    }

    auto available_energy_kWh() const -> double override
    {
        return battery_kwh_;
    }

    auto consume_for_distance(double km, double mass_kg) -> double override
    {
        // Verbrauch erhöht sich leicht mit Fahrzeugmasse
        double consumption =
            (km / 100.0) * kwh_per_100km_ * (1.0 + (mass_kg - 1000.0) / 10000.0);
        battery_kwh_ -= consumption;
        return consumption;
    }

    auto label() const -> std::string override
    {
        return "Electric Motor";
    }
};

/**
 * @brief Hybridmotor (vereinfacht)
 */
class HybridMotor : public IMotor
{
private:
    double fuel_l_{40.0};
    double battery_kwh_{15.0};
    double l_per_100km_{5.5};
    double kwh_per_100km_{8.0};

public:
    explicit HybridMotor(double fuel_l = 40.0, double battery_kwh = 15.0)
        : fuel_l_{fuel_l}, battery_kwh_{battery_kwh}
    {
    }

    auto available_energy_kWh() const -> double override
    {
        return fuel_l_ * 8.9 + battery_kwh_;
    }

    auto consume_for_distance(double km, double mass_kg) -> double override
    {
        // Hybrid nutzt zuerst die Batterie, dann den Verbrennungsmotor
        double consumption_kwh = (km / 100.0) * kwh_per_100km_ * (1.0 + (mass_kg - 1000.0) / 10000.0);
        double consumption_l = (km / 100.0) * l_per_100km_ * (1.0 + (mass_kg - 1000.0) / 10000.0);

        if (battery_kwh_ >= consumption_kwh)
        {
            battery_kwh_ -= consumption_kwh;
            return consumption_kwh;
        }
        else
        {
            double remaining_kwh = consumption_kwh - battery_kwh_;
            double fuel_for_remaining = remaining_kwh / 8.9;
            battery_kwh_ = 0.0;
            fuel_l_ -= fuel_for_remaining;
            return consumption_kwh;
        }
    }

    auto label() const -> std::string override
    {
        return "Hybrid Motor";
    }
};
