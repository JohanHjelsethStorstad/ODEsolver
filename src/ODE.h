#pragma once
#include "./structures/Point.h"
#include "./structures/Matrix.h"
#include <functional>

namespace ODE {

    /**
     * @brief Represents a ordinary differential equation of the form x' = f(x)
     * of order 2.
    */
    class ODE {
    private:
        std::function<Structures::Point<double>(Structures::Point<double>)> f;
    public:
        ODE(std::function<Structures::Point<double>(Structures::Point<double>)> f) : f(f) {}
        ODE(Structures::Matrix::Matrix<2> A) : f([A](Structures::Point<double> point) {
            return Structures::Point<double> {
                A.get(0, 0) * point.x + A.get(0, 1) * point.y,
                A.get(1, 0) * point.x + A.get(1, 1) * point.y
            };
        }) {}
        inline Structures::Point<double> operator()(Structures::Point<double> x) const {
            return f(x);
        }
    };

    /**
     * @brief Contains predefined ODEs.
     */
    namespace PreDefinedODE {
        /**
         * @brief Returns the ODE for a harmonic oscillator with spring constant k.
         * A = [
         * [ 0, 1 ],
         * [ -k, 0 ]
         * ]
         */
        ODE harmonicOscillator(double k) {
            return ODE(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {-k, 0}
            }}});
        }

        /**
         * @brief Returns the ODE solved by the circle function.
         * A = [
         * [ 0, 1 ],
         * [ -1, 0 ]
         * ]
         */
        ODE circle() {
            return ODE(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {-1, 0}
            }}});
        }

        /**
         * @brief Returns the identity ODE.
         * A = [
         * [ 1, 0 ],
         * [ 0, 1 ]
         * ]
         */
        ODE identity() {
            return ODE(Structures::Matrix::Matrix<2> {{{
                {1, 0},
                {0, 1}
            }}});
        }

        /**
         * @brief Returns the cross identity ODE.
         * A = [
         * [ 0, 1 ],
         * [ 1, 0 ]
         * ]
         */
        ODE crossIdentity() {
            return ODE(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {1, 0}
            }}});
        }
    }
}