#pragma once
#include "Structures.h"
#include "ButcherTableau.h"
#include "PrimeFieldInferation.h"
#include <vector>
#include <memory>

namespace ODE {
    class IterationScheme {
    private:
        std::vector<Structures::Arrow<double>> primeField;
        std::shared_ptr<BucherTableau::IButcherTableau> butcherTableau;
        std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme> inferationScheme;
    public:
        IterationScheme(
            const std::vector<Structures::Arrow<double>>& primeField, 
            std::shared_ptr<BucherTableau::IButcherTableau> butcherTableau,
            std::shared_ptr<PrimeFieldInferation::PrimeFieldInferationScheme> inferationScheme
        ) : primeField(primeField), butcherTableau(butcherTableau), inferationScheme(inferationScheme) {}
        inline void setPrimeField(const std::vector<Structures::Arrow<double>>& primeField) {
            this->primeField = primeField;
        }
        Structures::Point<double> prime(Structures::Point<double> point);
        Structures::Point<double> step(Structures::Point<double> prev, double dt);
    };
}