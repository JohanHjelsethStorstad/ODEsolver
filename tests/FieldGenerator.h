#pragma once
#include <vector>
#include "../src/Structures.h"
#include <functional>

namespace ODE::Tests {
    struct FieldGeneratorWindow {
        double width;
        double height;
        double startx;
        double starty;
        inline double endx() const { return startx + width; }
        inline double endy() const { return starty + height; }
    };

    class FieldGenerator {
    private:
        double delta;
        FieldGeneratorWindow window;
    public:
        FieldGenerator(double delta, FieldGeneratorWindow window) : delta{delta}, window{window} {}
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
        FieldGeneratorRandom(double delta, FieldGeneratorWindow window, FieldGeneratorRandomBounds bounds) : FieldGenerator(delta, window), bounds(bounds) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };

    class FieldGeneratorFunction : public FieldGenerator {
    private:
        std::function<Structures::Point<double>(Structures::Point<double>)> functions;
        std::function<Structures::Point<double>(double)> exactSolution;
    public:
        FieldGeneratorFunction(
            double delta, 
            FieldGeneratorWindow window, 
            std::function<Structures::Point<double>(Structures::Point<double>)> functions,
            std::function<Structures::Point<double>(double)> exactSolution
        ) : FieldGenerator(delta, window), functions(functions), exactSolution(exactSolution) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };
}