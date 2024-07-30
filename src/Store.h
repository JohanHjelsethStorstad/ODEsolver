#pragma once
#include "Structures.h"
#include <vector>
#include <fstream>
#include <string>

namespace Store {
    class Store {
    private:
        std::string name;
        std::ofstream file;
        static constexpr const char* STORE_LOCATION = "./store/";
    public:
        Store(const std::string& name);
        void store(std::vector<Structures::Arrow<double>> arrows);
        void store(Structures::Arrow<double> arrow);
        void store(std::vector<Structures::Point<double>> points);
        void store(Structures::Point<double> point);
        void write(const std::string& data);
    };
};