#pragma once
#include "structures/Arrow.h"
#include "structures/Point.h"
#include <vector>
#include <fstream>
#include <string>
#include "Trajectory.h"

namespace Store {
    class Store {
    private:
        std::string name;
        std::ofstream file;
        static constexpr const char* STORE_LOCATION = "./store/";
    public:
        Store(const std::string& name);
        void store(std::vector<Structures::Arrow<double>> arrows, const std::string& tag);
        void store(Structures::Arrow<double> arrow, const std::string& tag);
        void store(std::vector<Structures::Point<double>> points, const std::string& tag);
        void store(Structures::Point<double> point, const std::string& tag);
        void store(std::vector<ODE::Trajectory> trajectories, const std::string& tag);
        void store(ODE::Trajectory trajectory, const std::string& tag);
        void write(const std::string& data);
    };
};