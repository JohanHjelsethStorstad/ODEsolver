#pragma once
#include <array>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "DiagonalizedReturn.h"

namespace Structures::Matrix {
    
    template<int order>
    class Matrix {
    private:
        std::array<std::array<double, order>, order> matrix;
    public:
        Matrix(std::array<std::array<double, order>, order> matrix) : matrix(matrix) {}
        Matrix() {
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    matrix[i][j] = 0;
                }
            }
        }
        Matrix(const Matrix<order>& other) {
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
        }
        Matrix<order> inverse() const {
            Matrix<order> result;
            Matrix<order> augmented;

            // Create the augmented matrix [matrix | I]
            for (size_t i = 0; i < order; ++i) {
                for (size_t j = 0; j < order; ++j) {
                    augmented.matrix[i][j] = matrix[i][j];
                    augmented.matrix[i][j + order] = (i == j) ? 1.0 : 0.0;
                }
            }

            // Apply Gaussian elimination
            for (size_t i = 0; i < order; ++i) {
                // Find the pivot
                double pivot = augmented.matrix[i][i];
                if (pivot == 0) {
                    throw std::runtime_error("Matrix is singular and cannot be inverted.");
                }

                // Normalize the pivot row
                for (size_t j = 0; j < 2 * order; ++j) {
                    augmented.matrix[i][j] /= pivot;
                }

                // Eliminate the current column in other rows
                for (size_t k = 0; k < order; ++k) {
                    if (k != i) {
                        double factor = augmented.matrix[k][i];
                        for (size_t j = 0; j < 2 * order; ++j) {
                            augmented.matrix[k][j] -= factor * augmented.matrix[i][j];
                        }
                    }
                }
            }

            // Extract the inverse matrix from the augmented matrix
            for (size_t i = 0; i < order; ++i) {
                for (size_t j = 0; j < order; ++j) {
                    result.matrix[i][j] = augmented.matrix[i][j + order];
                }
            }

            return result;
        }

        Matrix<order> operator+(const Matrix<order>& other) const {
            Matrix<order> result;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
                }
            }
            return result;
        }

        Matrix<order> operator-(const Matrix<order>& other) const {
            Matrix<order> result;
            for (int i = 0; i < order; i++) {
                for (int j = 0; j < order; j++) {
                    result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
                }
            }
            return result;
        }

        Matrix<order> operator*(const Matrix<order>& other) const {
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

        void set(int i, int j, double value) {
            matrix[i][j] = value;
        }

        double get(int i, int j) const {
            return matrix[i][j];
        }

        std::array<double, order> eigenvalues() const {
            std::array<double, order> result;
        }

        DiaonalizedReturn<order> diagonalize() {
            return {
                Matrix<order>(),
                Matrix<order>()
            };
        }
    };
}; 

template<int order>
std::ostream& operator<<(std::ostream& os, const Structures::Matrix::Matrix<order>& matrix) {
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            os << matrix.matrix[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}