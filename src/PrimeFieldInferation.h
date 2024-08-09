#pragma once
#include <vector>
#include "structures/Arrow.h"
#include "structures/Point.h"
#include <string>
#include <algorithm>

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

    template <int NUMBER_ARROWS_TO_CONSIDER>
    class PrimeFieldInferationSchemeWeightedAverageN : public PrimeFieldInferationScheme {
    public:
        virtual inline double weightOfLength(double length) = 0;
        Structures::Arrow<double> infer(const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point) override {
            if (discreetField.size() == 0) return { {0, 0}, {1, 1} };
            std::vector<std::pair<Structures::Arrow<double>, double>> arrowsWithWeights;
            for (const auto& arrow : discreetField) {
                const double distance = point.distanceTo(arrow.start);
                arrowsWithWeights.push_back({arrow, distance});
            }
            // Grab the first NUMBER_ARROWS_TO_CONSIDER arrows (the once with shortest distance)
            std::sort(arrowsWithWeights.begin(), arrowsWithWeights.end(), [](const auto& a, const auto& b) { return a.second < b.second; });
            arrowsWithWeights.resize(NUMBER_ARROWS_TO_CONSIDER);

            return {{0, 0}, {0, 0}};
        }
        inline std::string getName() const override { return "Nearest " + std::to_string(NUMBER_ARROWS_TO_CONSIDER); }
    };

    template <int NUMBER_ARROWS_TO_CONSIDER>
    class PrimeFieldInferationSchemeWeightedAverageNInverseLinear : public PrimeFieldInferationSchemeWeightedAverageN<NUMBER_ARROWS_TO_CONSIDER> {
    public:
        inline double weightOfLength(double length) override {
            return 1 / length;
        }
    };

    template <int NUMBER_ARROWS_TO_CONSIDER>
    class PrimeFieldInferationSchemeWeightedAverageNInverseSquare : public PrimeFieldInferationSchemeWeightedAverageN<NUMBER_ARROWS_TO_CONSIDER> {
    public:
        inline double weightOfLength(double length) override {
            return 1 / (length * length);
        }
    };
};