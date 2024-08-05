#pragma once
#include <vector>
#include "../src/structures/Arrow.h"
#include "../src/structures/Point.h"
#include <functional>
#include <string>

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
    public:
        FieldGenerator() = default;
        virtual std::vector<Structures::Arrow<double>> generateField() const = 0;
    };

    class FieldGeneratorFixedWindow : public FieldGenerator {
    private:
        double delta;
        FieldGeneratorWindow window;
    public:
        FieldGeneratorFixedWindow(double delta, FieldGeneratorWindow window) : delta{delta}, window{window} {}
        std::vector<Structures::Arrow<double>> generateField() const override;
        virtual Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const = 0;
    };

    struct FieldGeneratorRandomBounds {
        double min = 0;
        double max = 10;
    };

    class FieldGeneratorRandom : public FieldGeneratorFixedWindow {
    private:
        FieldGeneratorRandomBounds bounds;
        double randomDouble() const;
    public:
        FieldGeneratorRandom(double delta, FieldGeneratorWindow window, FieldGeneratorRandomBounds bounds) : FieldGeneratorFixedWindow(delta, window), bounds(bounds) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };

    class FieldGeneratorFunction : public FieldGeneratorFixedWindow {
    private:
        std::function<Structures::Point<double>(Structures::Point<double>)> functions;
    public:
        FieldGeneratorFunction(
            double delta, 
            FieldGeneratorWindow window, 
            std::function<Structures::Point<double>(Structures::Point<double>)> functions
        ) : FieldGeneratorFixedWindow(delta, window), functions(functions) {}
        Structures::Arrow<double> generateArrowAtPoint(Structures::Point<double> point) const override;
    };

    class FieldGeneratorFromFile : public FieldGenerator {
    private:
        std::string fileName;
    public:
        FieldGeneratorFromFile(double delta, FieldGeneratorWindow window, std::string fileName) : fileName(fileName) {}
        std::vector<Structures::Arrow<double>> generateField() const override;
    };
}