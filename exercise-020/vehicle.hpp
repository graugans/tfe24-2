#pragma once

#include "motor.hpp"

#include <memory>
#include <string>

/**
 * @brief Abstrakte Basisklasse für Fahrzeuge
 */
class Vehicle
{
protected:
    std::string vin_;
    double mass_kg_;
    std::unique_ptr<IMotor> motor_;

public:
    /**
     * @brief Konstruktor
     * @param vin Fahrzeug-Identifikationsnummer
     * @param mass_kg Masse des Fahrzeugs in Kilogramm
     * @param motor Motor des Fahrzeugs
     */
    Vehicle(const std::string &vin, double mass_kg, std::unique_ptr<IMotor> motor)
        : vin_{vin}, mass_kg_{mass_kg}, motor_{std::move(motor)}
    {
    }

    virtual ~Vehicle() = default;

    /**
     * @brief Reichweite des Fahrzeugs
     * @return Reichweite in Kilometern
     */
    virtual auto range_km() const -> double = 0;

    /**
     * @brief Fahrt für eine bestimmte Strecke
     * @param km Strecke in Kilometern
     */
    virtual auto drive(double km) -> void = 0;

    /**
     * @brief Typ des Fahrzeugs
     * @return Fahrzeugtyp als String
     */
    virtual auto type() const -> std::string = 0;

    /**
     * @brief VIN des Fahrzeugs
     * @return VIN
     */
    auto vin() const -> std::string
    {
        return vin_;
    }

    /**
     * @brief Masse des Fahrzeugs
     * @return Masse in Kilogramm
     */
    auto mass() const -> double
    {
        return mass_kg_;
    }

    /**
     * @brief Motor des Fahrzeugs
     * @return Zeiger auf den Motor
     */
    auto motor() const -> IMotor *
    {
        return motor_.get();
    }
};

/**
 * @brief Personenkraftwagen
 */
class Car : public Vehicle
{
public:
    using Vehicle::Vehicle;

    auto range_km() const -> double override
    {
        return motor_->available_energy_kWh() / (0.20 * (1.0 + (mass_kg_ - 1000.0) / 10000.0));
    }

    auto drive(double km) -> void override
    {
        motor_->consume_for_distance(km, mass_kg_);
    }

    auto type() const -> std::string override
    {
        return "Car";
    }
};

/**
 * @brief Lastkraftwagen
 */
class Truck : public Vehicle
{
public:
    using Vehicle::Vehicle;

    auto range_km() const -> double override
    {
        return motor_->available_energy_kWh() / (0.35 * (1.0 + (mass_kg_ - 3000.0) / 10000.0));
    }

    auto drive(double km) -> void override
    {
        motor_->consume_for_distance(km, mass_kg_);
    }

    auto type() const -> std::string override
    {
        return "Truck";
    }
};

/**
 * @brief Motorrad
 */
class Motorcycle : public Vehicle
{
public:
    using Vehicle::Vehicle;

    auto range_km() const -> double override
    {
        return motor_->available_energy_kWh() / (0.08 * (1.0 + (mass_kg_ - 200.0) / 10000.0));
    }

    auto drive(double km) -> void override
    {
        motor_->consume_for_distance(km, mass_kg_);
    }

    auto type() const -> std::string override
    {
        return "Motorcycle";
    }
};
