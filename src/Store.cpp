#include "Store.h"

Store::Store::Store(const std::string& name, const std::string&& location) : name(name), location(location), file(location + name + ".txt") {
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + this->name);
    }
}

void Store::Store::write(const std::string& data) {
    file << data << "\n";
}

void Store::Store::store(std::vector<Structures::Arrow<double>> arrows, const std::string& tag) {
    for (const auto& arrow : arrows) {
        store(arrow, tag);
        file << std::endl;
    }
}

void Store::Store::store(Structures::Arrow<double> arrow, const std::string& tag) {
    file << "Arrow" << "[" << tag << "]" << "(" << arrow.start.x << "," << arrow.start.y << "," << arrow.end.x << "," << arrow.end.y << ")\n";
}

void Store::Store::store(std::vector<Structures::Point<double>> points, const std::string& tag) {
    for (const auto& point : points) {
        store(point, tag);
        file << std::endl;
    }
}

void Store::Store::store(Structures::Point<double> point, const std::string& tag) {
    file << "Point" << "[" << tag << "]" << "(" << point.x << "," << point.y << ")\n";
}

void Store::Store::store(std::vector<ODE::Trajectory> trajectories, const std::string& tag) {
    for (const auto& trajectory : trajectories) {
        store(trajectory, tag);
        file << std::endl;
    }
}
    
void Store::Store::store(ODE::Trajectory trajectory, const std::string& tag) {;
    Structures::Point<double> start = trajectory.getStart();
    for (const auto& point : trajectory.getPoints()) {
        file << "Point" << "[" << tag << "]" << "{" << start.x << "," << start.y << "}" << "(" << point.x << "," << point.y << ")\n";
    }
}