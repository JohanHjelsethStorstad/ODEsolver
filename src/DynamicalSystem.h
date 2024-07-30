#pragma once
#include <functional>
#include "Structures.h"

namespace ODE::DynamicalSystem {
    class DynamicalSystem {
    
    }; 

    /**
     * @brief Represents the dynamical system solving x' = Ax (x has dimention order)
     * i.e the soulution is the system e^(At) * x(0)
     */
    template<int order>
    class LinearDynamicalSystem : public DynamicalSystem {
    private:
        std::array<std::array<double, order>, order> A;
    public:
        std::function<Structures::Point<double>(double)> getExactTrajectorySolution(Structures::Point<double> start) const {
            return [this, start](double t) {
                Structures::Point<double> result;
                for (int i = 0; i < order; i++) {
                    double sum = 0;
                    for (int j = 0; j < order; j++) {
                        sum += A[i][j] * start[j];
                    }
                    result[i] = std::exp(A[i][i] * t) * sum;
                }
                return result;
            };
        }
    };
};