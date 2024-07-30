#include "Store.h"

Store::Store::Store(const std::string& name) : name(name), file(STORE_LOCATION + name + ".txt") {
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + this->name);
    }
}

void Store::Store::write(const std::string& data) {
    file << data << "\n";
}

void Store::Store::store(std::vector<Structures::Arrow<double>> arrows) {
    for (const auto& arrow : arrows) {
        store(arrow);
        file << std::endl;
    }
}

void Store::Store::store(Structures::Arrow<double> arrow) {
    file << "Arrow" << "(" << arrow.start.x << "," << arrow.start.y << "," << arrow.end.x << "," << arrow.end.y << ")\n";
}

void Store::Store::store(std::vector<Structures::Point<double>> points) {
    for (const auto& point : points) {
        store(point);
        file << std::endl;
    }
}

void Store::Store::store(Structures::Point<double> point) {
    file << "Point" << "(" << point.x << "," << point.y << ")\n";
}