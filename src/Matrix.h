#pragma once
#include <array>

namespace Matrix {
    template<int order>
    class Matrix {
    private:
        std::array<std::array<double, order>, order> matrix;
    public:
        Matrix<order> operator+(const Matrix<order>& other) {
            Matrix<order> result;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
                }
            }
            return result;
        }

        Matrix<order> operator-(const Matrix<order>& other) {
            Matrix<order> result;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
                }
            }
            return result;
        }

        Matrix<order> operator*(const Matrix<order>& other) {
            Matrix<order> result;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    double sum = 0;
                    for (int k = 0; k < order; k++) {
                        sum += matrix[i][k] * other.matrix[k][j];
                    }
                    result.matrix[i][j] = sum;
                }
            }
            return result;
        }
    };

    template<int order>
    struct DiaonalizedReturn {
        Matrix<order> eigenvaluesmatrix;
        Matrix<order> eigenvectorsmatrix;
        Matrix<order> getMatrix() {

        }
    };


}; 