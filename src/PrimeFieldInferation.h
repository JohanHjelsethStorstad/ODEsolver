#pragma once
#include <vector>
#include "structures/Arrow.h"
#include "structures/Point.h"
#include <string>

namespace ODE::PrimeFieldInferation {
    class PrimeFieldInferationScheme {
    public:
        virtual Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) = 0;
        virtual std::string getName() const = 0;
    };

    class PrimeFieldInferationSchemeNearest : public PrimeFieldInferationScheme {
    public:
        Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) override;
        inline std::string getName() const override { return "Nearest"; }
    };

    class PrimeFieldInferationSchemeWeightedAverage : public PrimeFieldInferationScheme {
    public:
        Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) override;
        inline std::string getName() const override { return "Weighted Average"; }
    };
};