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
        std::string location;
        Store(const std::string& name, const std::string&& location);
    public:
        friend class Stores;
        void store(std::vector<Structures::Arrow<double>> arrows, const std::string& tag);
        void store(Structures::Arrow<double> arrow, const std::string& tag);
        void store(std::vector<Structures::Point<double>> points, const std::string& tag);
        void store(Structures::Point<double> point, const std::string& tag);
        void store(std::vector<ODE::Trajectory> trajectories, const std::string& tag);
        void store(ODE::Trajectory trajectory, const std::string& tag);
        void write(const std::string& data);
    };

    class Stores {
        public:
            static Store testStore(const std::string& name) {
                return Store(name, "./tests/out/");
            }
    };
};