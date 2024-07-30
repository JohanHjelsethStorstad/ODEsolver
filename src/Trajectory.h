#pragma once
#include "structures/Point.h"
#include <vector>

namespace ODE {
    class Trajectory {
    private:
        Structures::Point<double> start;
        std::vector<Structures::Point<double>> points;
    public:
        Trajectory(Structures::Point<double> start) : start(start), points{{start}} {}
        void addPoint(Structures::Point<double> point) { points.push_back(point); }
        const std::vector<Structures::Point<double>>& getPoints() const { return points; }
        const Structures::Point<double>& getStart() const { return start; }
    };
}