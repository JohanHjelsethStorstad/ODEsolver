#include "PrimeFieldInferation.h"

Structures::Arrow<double> ODE::PrimeFieldInferation::PrimeFieldInferationSchemeNearest::infer(
    const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point
) {
    if (discreetField.size() == 0) return { {0, 0}, {1, 1} };
    Structures::Arrow<double> closestArrow = discreetField.at(0);
    float closestDistance = (std::numeric_limits<float>::max)();
    for (const auto& arrow : discreetField) {
        float distance = sqrt(pow(arrow.start.x - point.x, 2) + pow(arrow.start.y - point.y, 2));
        if (distance < closestDistance) {
            closestDistance = distance;
            closestArrow = arrow;
        }
    }
    return closestArrow;
}

Structures::Arrow<double> ODE::PrimeFieldInferation::PrimeFieldInferationSchemeWeightedAverage::infer(
    const std::vector<Structures::Arrow<double>>& discreetField, Structures::Point<double> point
) {
    if (discreetField.size() == 0) return { {0, 0}, {1, 1} };
    Structures::Arrow<double> arrowSum = { {0, 0}, {0, 0} };
    double weightSum = 0;
    for (Structures::Arrow<double> arrow : discreetField) {
        const float distance = point.distanceTo(arrow.start);
        if (distance == 0) return arrow;
        const double weight = 1 / distance;
        arrow = arrow.moveToOrigin();
        arrowSum += weight * arrow;
        weightSum += weight;
    }
    Structures::Arrow<double> atOriginArrow = (1 / weightSum) * arrowSum;
    return atOriginArrow.moveBase(point);
}