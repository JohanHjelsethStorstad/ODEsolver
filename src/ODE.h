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
            Structures::Array<double, order> result;
            for (int i = 0; i < order; i++) {
                result[i] = 0;
                for (int j = 0; j < order; j++) {
                    result[i] += A.get(i, j) * point[j];
                }
            }
            return result;
        }) {}
        inline Structures::Array<double, order> operator()(const Structures::Array<double, order>& x) const {
            return f(x);
        }

        /**
         * @brief Returns the ODE solved by the harmonic oscillator.
         * A = [
         * [ 0, 1 ],
         * [ -k, 0 ]
         * ]
         */
        static const ODE<2>& HarmonicOscillator(double k) {
            static ODE<2> harmonicOscillator(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {-k, 0}
            }}});
            return harmonicOscillator;
        }

        /**
         * @brief Returns the ODE solved by the circle function.
         * A = [
         * [ 0, 1 ],
         * [ -1, 0 ]
         * ]
         */
        static const ODE<2>& Circle() {
            static ODE<2> circle(Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {-1, 0}
            }}});
            return circle;
        }

        /**
         * @brief Returns the identity ODE.
         * A = [
         * [ 1, 0 ],
         * [ 0, 1 ]
         * ]
         */
        static const ODE<2>& Identity() {
            static ODE<2> identity (Structures::Matrix::Matrix<2> {{{
                {1, 0},
                {0, 1}
            }}});
            return identity;
        }

        /**
         * @brief Returns the cross identity ODE.
         * A = [
         * [ 0, 1 ],
         * [ 1, 0 ]
         * ]
         */
        static const ODE<2>& CrossIdentity() {
            static ODE<2> crossIdentity (Structures::Matrix::Matrix<2> {{{
                {0, 1},
                {1, 0}
            }}});
            return crossIdentity;
        }
    };
}