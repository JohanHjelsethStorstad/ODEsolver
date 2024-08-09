#pragma once
#include <functional>
#include "structures/Point.h"
#include "structures/Matrix.h"

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
        DynamicalSystem() = default;
        DynamicalSystem(const DynamicalSystem& other) = default;
        DynamicalSystem& operator=(const DynamicalSystem& other) = default;
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

        static std::shared_ptr<DynamicalSystemKnownSoulution> Circle() { 
            static auto ds = std::make_shared<DynamicalSystemKnownSoulution>(
                [](Structures::Point<double> start, double t) {
                    return Structures::Point<double> {
                        start.y * std::sin(t) + start.x * std::cos(t),
                        -start.x * std::sin(t) + start.y * std::cos(t)
                    };
                }
            );
            return ds;
        }

        static std::shared_ptr<DynamicalSystemKnownSoulution> CrossIdentity() { 
            static auto ds = std::make_shared<DynamicalSystemKnownSoulution>(
                [](Structures::Point<double> start, double t) {
                    double c1 = ( start.x + start.y ) / 2;
                    double c2 = ( start.x - start.y ) / 2;
                    return Structures::Point<double> {
                        c1 * std::exp(t) + c2 * std::exp(-t),
                        c1 * std::exp(t) - c2 * std::exp(-t)
                    };
                }
            );
            return ds;
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
        Structures::Matrix::Matrix<order> A;
    public:
        LinearDynamicalSystem(Structures::Matrix::Matrix<order> A) : A(A) {}

        Structures::Point<double> soulution(Structures::Point<double> start, double t) const override {
            return Structures::Point<double>(0, 0);
        }
    };
};