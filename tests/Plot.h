#pragma once
#include "../lib/matplotlib-cpp/matplotlibcpp.h"
#include "../src/Structures.h"

namespace ODE::Tests {
    class Plot {
    public:
        static void plotArrows(const std::vector<Structures::Arrow<double>>& arrows);
        static void plotArrow(const Structures::Arrow<double>& arrow);
        static void plotPoints(const std::vector<Structures::Point<double>>& points) {
            std::vector<double> x;
            std::vector<double> y;
            for (const Structures::Point<double>& point : points) {
                x.push_back(point.x);
                y.push_back(point.y);
            }
            matplotlibcpp::plot(x, y);
        }
        static inline void show() {
            matplotlibcpp::show();
        }
    };
}