#pragma once
#include "FieldGenerator.h"
#include "../src/structures/Point.h"
#include "../src/ButcherTableau.h"
#include "../src/PrimeFieldInferation.h"
#include "../src/ODE.h"
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <optional>
#include "../src/DynamicalSystem.h"

namespace ODE::Tests::Config {
    enum class FieldGeneratorType {
        RANDOM,
        FUNCTION,
        LOAD_FROM_FILE
    };
    struct FieldGeneratorInfo {
    private:
        static const std::map<std::string, FieldGeneratorType> FieldGeneratorTypeMap;
        static const std::map<std::string, ODE<2>> PreProgrammedODEMap;
    public:
        friend class TestConfig;

        FieldGeneratorInfo() = default;

        FieldGeneratorType type = FieldGeneratorType::RANDOM;

        //For RANDOM
        FieldGeneratorRandomBounds bounds = {};

        //For FUNCTION
        ODE<2> preProgrammedODE = FieldGeneratorInfo::PreProgrammedODEMap.at("Circle");

        //For LOAD_FROM_FILE
        std::string fileName = "example";
    };

    class TestConfig {
    private:
        static const std::map<std::string, std::shared_ptr<BucherTableau::ButcherTableau>> availableTableaus;
        static const std::map<std::string, std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> availableInferationSchemes;
        static const std::map<std::string, std::shared_ptr<DynamicalSystem::DynamicalSystemKnownSoulution>> availableKnownSolutions;
    public:
        int iterations = 1000;
        double dt = 0.2;
        double fieldDelta = 0.1;
        FieldGeneratorWindow window = {};
        std::string name = "Test";
        std::vector<Structures::Point<double>> startPoints = {};
        std::vector<std::shared_ptr<BucherTableau::ButcherTableau>> schemes = {};
        std::vector<std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme>> inferationSchemes = {};
        FieldGeneratorInfo fieldGeneratorInfo = {};
        std::optional<std::shared_ptr<DynamicalSystem::DynamicalSystem>> knownSolution = std::nullopt;
        TestConfig() = default;
        const TestConfig& loadFromFile(std::string configFileName);
    };
}