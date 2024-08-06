#pragma once

namespace Structures::Matrix {
    template<int order>
    class Matrix;

    template<int order>
    struct DiaonalizedReturn {
        Matrix<order> eigenvaluesmatrix;
        Matrix<order> eigenvectorsmatrix;
        Matrix<order> getOriginalMatrix() {
            return eigenvectorsmatrix * eigenvaluesmatrix * eigenvectorsmatrix.inverse();
        }
    };
};