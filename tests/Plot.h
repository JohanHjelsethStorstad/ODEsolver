#pragma once
#include "../lib/matplotlib-cpp/matplotlibcpp.h"
#include "../src/structures/Arrow.h"
#include "../src/structures/Point.h"

namespace ODE::Tests {
    class Plot {
    public:
        static void plotArrows(const std::vector<Structures::Arrow<double>>& arrows);
        static void plotArrow(const Structures::Arrow<double>& arrow);
        static void plotPoints(const std::vector<Structures::Point<double>>& points);
        static inline void show() {
            matplotlibcpp::show();
        }
    };
}