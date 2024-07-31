#pragma once
#include <functional>
#include "structures/Point.h"

namespace ODE::DynamicalSystem {
    /**
     * @brief Represents a dynamical system solving some arbitrary diff. equation.
     */
    class DynamicalSystem {
    public:
        virtual Structures::Point<double> soulution(Structures::Point<double> start, double t) const = 0;
        std::function<Structures::Point<double>(double)> getExactTrajectorySolution(Structures::Point<double> start) const {
            return [this, start](double t) {
                return this->soulution(start, t);
            };
        }
    }; 

    /**
     * @brief Represents the dynamical system solving some arbitrary diff. equation. Use
     * This class when you have a known soulution to the diff. equation before hand.
     */
    class DynamicalSystemKnownSoulution : public DynamicalSystem {
    private:
        std::function<Structures::Point<double>(Structures::Point<double>, double)> knownSoulution;
    public:
        DynamicalSystemKnownSoulution(std::function<Structures::Point<double>(Structures::Point<double>, double)> knownSoulution) : knownSoulution(knownSoulution) {}

        Structures::Point<double> soulution(Structures::Point<double> start, double t) const override {
            return knownSoulution(start, t);
        }
    };

    /**
     * @brief Represents the dynamical system solving x' = Ax (x has dimention order)
     * i.e the soulution is the system e^(At) * x(0)
     * This functionality is not fully implemented.
     */
    template<int order>
    class LinearDynamicalSystem : public DynamicalSystem {
    private:
        std::array<std::array<double, order>, order> A;
    public:
        LinearDynamicalSystem(std::array<std::array<double, order>, order> A) : A(A) {}

        Structures::Point<double> soulution(Structures::Point<double> start, double t) const override {
            return Structures::Point<double>(0, 0);
        }
    };
};