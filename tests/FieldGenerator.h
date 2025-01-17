#pragma once
#include <vector>
#include "../src/structures/Arrow.h"
#include "../src/structures/Point.h"
#include "../src/structures/Array.h"
#include "../src/ODE.h"
#include <functional>
#include <string>

namespace ODE::Tests {
    struct FieldGeneratorWindow {
        double width = 20;
        double height = 20;
        double startx = -10;
        double starty = -10;
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
        virtual Structures::Arrow<double> generateArrowAtPoint(const Structures::Point<double>& point) const = 0;
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
        Structures::Arrow<double> generateArrowAtPoint(const Structures::Point<double>& point) const override;
    };

    class FieldGeneratorFunction : public FieldGeneratorFixedWindow {
    private:
        ODE<2> ode;
    public:
        FieldGeneratorFunction(
            double delta, 
            FieldGeneratorWindow window, 
            ODE<2> ode
        ) : FieldGeneratorFixedWindow(delta, window), ode(ode) {}
        Structures::Arrow<double> generateArrowAtPoint(const Structures::Point<double>& point) const override;
    };

    class FieldGeneratorFromFile : public FieldGenerator {
    private:
        std::string fileName;
    public:
        FieldGeneratorFromFile(const std::string& fileName) : fileName(fileName) {}
        std::vector<Structures::Arrow<double>> generateField() const override;
    };
}