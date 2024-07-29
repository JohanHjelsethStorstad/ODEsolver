#include "Plot.h"

void ODE::Tests::Plot::plotArrows(const std::vector<Structures::Arrow<double>>& arrows) {
    for (const Structures::Arrow<double>& arrow : arrows) {
        plotArrow(arrow);
    }
}

void ODE::Tests::Plot::plotArrow(const Structures::Arrow<double>& arrow) {
    matplotlibcpp::arrow(arrow.start.x, arrow.start.y, arrow.end.x, arrow.end.y);
}

void ODE::Tests::Plot::plotPoints(const std::vector<Structures::Point<double>>& points) {
    std::vector<double> x;
    std::vector<double> y;
    for (const Structures::Point<double>& point : points) {
        x.push_back(point.x);
        y.push_back(point.y);
    }
    matplotlibcpp::plot(x, y);
}