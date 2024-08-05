#pragma once
#include "./structures/Point.h"
#include "./structures/Matrix.h"
#include "./structures/Array.h"
#include <functional>
#include <array>

namespace ODE {
    template<int order>
    class ODE {
    private:
        std::function<Structures::Array<double, order>(Structures::Array<double, order>)> f;
    public:
        ODE(std::function<Structures::Array<double, order>(Structures::Array<double, order>)> f) : f(f) {}
        ODE(Structures::Matrix::Matrix<order> A) : f([A](Structures::Array<double, order> point) {
            Structures::array<double, order> result;
            for (int i = 0; i < order; i++) {
                result[i] = 0;
                for (int j = 0; j < order; j++) {
                    result[i] += A.get(i, j) * point[j];
                }
            }
            return result;
        }) {}
        inline Structures::Array<double, order> operator()(Structures::Array<double, order> x) const {
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
        ODE<2> harmonicOscillator(double k) {
            return ODE<2>(Structures::Matrix::Matrix<2> {{{
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
        ODE<2> circle() {
            return ODE<2>(Structures::Matrix::Matrix<2> {{{
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
        ODE<2> identity() {
            return ODE<2>(Structures::Matrix::Matrix<2> {{{
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
        ODE<2> crossIdentity() {
            return ODE<2>(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {1, 0}
            }}});
        }
    }
}