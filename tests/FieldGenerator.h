#pragma once
#include <vector>
#include "../src/Structures.h"
#include <functional>

namespace ODE::Tests {
    class FieldGenerator {
    private:
        double delta;
        double width;
        double height;
    public:
        FieldGenerator(double delta, double width, double height) : delta{delta}, width{width}, height{height} {}
        virtual Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const = 0;
        std::vector<Structures::Arrow<double>> generateField() const;
    };

    struct FieldGeneratorRandomBounds {
        double min = 0;
        double max = 10;
    };

    class FieldGeneratorRandom : public FieldGenerator {
    private:
        FieldGeneratorRandomBounds bounds;
        double randomDouble() const;
    public:
        FieldGeneratorRandom(double delta, double width, double height, FieldGeneratorRandomBounds bounds) : FieldGenerator(delta, width, height), bounds(bounds) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };

    class FieldGeneratorFunction : public FieldGenerator {
    private:
        std::function<Structures::Point<double>(Structures::Point<double>)> functions;
    public:
        FieldGeneratorFunction(double delta, double width, double height, std::function<Structures::Point<double>(Structures::Point<double>)> functions) : FieldGenerator(delta, width, height), functions(functions) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };
}