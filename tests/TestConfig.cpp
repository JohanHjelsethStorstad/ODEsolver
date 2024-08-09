#include "TestConfig.h"
#include <fstream>
#include <nlohmann/json.hpp>

const std::map<std::string, std::shared_ptr<ODE::BucherTableau::ButcherTableau>> ODE::Tests::Config::TestConfig::availableTableaus = {
    {"Euler", std::make_shared<BucherTableau::ExplicitButcherTableau<1>>(BucherTableau::ExplicitButcherTableau<1>::Euler())},
    {"RK4", std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta4())},
    {"RK3", std::make_shared<BucherTableau::ExplicitButcherTableau<4>>(BucherTableau::ExplicitButcherTableau<4>::RungeKutta3())},
    {"Heun", std::make_shared<BucherTableau::ExplicitButcherTableau<2>>(BucherTableau::ExplicitButcherTableau<2>::Heun())}
};
const std::map<std::string, std::shared_ptr<ODE::PrimeFieldInferation::PrimeFieldInferationScheme>> ODE::Tests::Config::TestConfig::availableInferationSchemes = {
    {"Nearest", std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeNearest>(PrimeFieldInferation::PrimeFieldInferationSchemeNearest())},
    {"Weighted Average", std::make_shared<PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage>(PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage())}
};
const std::map<std::string, std::shared_ptr<ODE::DynamicalSystem::DynamicalSystemKnownSoulution>> ODE::Tests::Config::TestConfig::availableKnownSolutions = {
    {"Circle", DynamicalSystem::DynamicalSystemKnownSoulution::Circle()},
    {"CrossIdentity", DynamicalSystem::DynamicalSystemKnownSoulution::CrossIdentity()}
};


const std::map<std::string, ODE::Tests::Config::FieldGeneratorType> ODE::Tests::Config::FieldGeneratorInfo::FieldGeneratorTypeMap = {
    {"RANDOM", Tests::Config::FieldGeneratorType::RANDOM},
    {"FUNCTION", Tests::Config::FieldGeneratorType::FUNCTION},
    {"LOAD_FROM_FILE", Tests::Config::FieldGeneratorType::LOAD_FROM_FILE}
};
const std::map<std::string, ODE::ODE<2>> ODE::Tests::Config::FieldGeneratorInfo::PreProgrammedODEMap = {
    {"HarmonicOcillator", ODE<2>::HarmonicOscillator(1)},
    {"Circle", ODE<2>::Circle()},
    {"Identity", ODE<2>::Identity()},
    {"CrossIdentity", ODE<2>::CrossIdentity()}
};


using json = nlohmann::json;

const ODE::Tests::Config::TestConfig& ODE::Tests::Config::TestConfig::loadFromFile(std::string configFileName) {
    std::ifstream file{"./tests/configs/" + configFileName + ".json"};
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file: " + configFileName);
    }
    json jsonConfig = json::parse(file);
    auto config = jsonConfig["test"];
    std::cout << config << std::endl;
    
    this->iterations = config["iterations"];
    this->dt = config["dt"];
    this->fieldDelta = config["fieldDelta"];

    for (auto& start : config["startPoints"]) {
        this->startPoints.push_back(Structures::Point<double>{start["x"], start["y"]});
    }
    for (auto& scheme : config["schemes"]) {
        this->schemes.push_back(availableTableaus.at(scheme));
    }
    for (auto& inferationScheme : config["inferationSchemes"]) {
        this->inferationSchemes.push_back(availableInferationSchemes.at(inferationScheme));
    }
    auto fieldGeneratorInfo = config["fieldGeneratorInfo"];
    switch (FieldGeneratorInfo::FieldGeneratorTypeMap.at(fieldGeneratorInfo["type"])) {
        case FieldGeneratorType::RANDOM:
            this->fieldGeneratorInfo.type = FieldGeneratorType::RANDOM;
            this->fieldGeneratorInfo.bounds = FieldGeneratorRandomBounds{
                fieldGeneratorInfo["bounds"]["min"],
                fieldGeneratorInfo["bounds"]["max"]
            };
            break;
        case FieldGeneratorType::FUNCTION:
            std::cout << fieldGeneratorInfo << std::endl;
            this->fieldGeneratorInfo.type = FieldGeneratorType::FUNCTION;
            this->fieldGeneratorInfo.preProgrammedODE = FieldGeneratorInfo::PreProgrammedODEMap.at(fieldGeneratorInfo["preProgrammedODE"]);
            break;
        case FieldGeneratorType::LOAD_FROM_FILE:
            this->fieldGeneratorInfo.type = FieldGeneratorType::LOAD_FROM_FILE;
            this->fieldGeneratorInfo.fileName = fieldGeneratorInfo["fileName"];
            break;
    }
    if (config.contains("knownSolution")) {
        this->knownSolution = availableKnownSolutions.at(config["knownSolution"]);
    }

    return *this;
}