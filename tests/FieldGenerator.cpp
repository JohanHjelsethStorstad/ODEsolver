#include "FieldGenerator.h"
#include <random>

std::vector<Structures::Arrow<double>> ODE::Tests::FieldGenerator::generateField() const {
    std::vector<Structures::Arrow<double>> field;
    for (double x = 0; x < this->width; x += this->delta) {
        for (double y = 0; y < this->height; y += this->delta) {
            field.push_back(this->generateArrowAtPoint({x, y}));
        }
    }
    return field;
}

double ODE::Tests::FieldGeneratorRandom::randomDouble() const {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(this->bounds.min, this->bounds.max);
    return distribution(generator);
}

Structures::Arrow<double> ODE::Tests::FieldGeneratorRandom::generateArrowAtPoint(Structures::Point<double> point) const {
    const Structures::Arrow<double> originArrow = { {0, 0}, { this->randomDouble(), this->randomDouble() } };
    return originArrow.moveBase(point);
}

Structures::Arrow<double> ODE::Tests::FieldGeneratorFunction::generateArrowAtPoint(Structures::Point<double> point) const {
    const Structures::Point<double> end_point = this->functions(point);
    return { point, end_point };
}