#include "FieldGenerator.h"
#include <random>
#include <nlohmann/json.hpp>
#include <fstream>

std::vector<Structures::Arrow<double>> ODE::Tests::FieldGeneratorFixedWindow::generateField() const {
    std::vector<Structures::Arrow<double>> field;
    for (double x = this->window.startx; x < this->window.endx(); x += this->delta) {
        for (double y = this->window.starty; y < this->window.endy(); y += this->delta) {
            field.push_back(this->generateArrowAtPoint({x, y}));
        }
    }
    return field;
}

double ODE::Tests::FieldGeneratorRandom::randomDouble() const {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(this->bounds.min, this->bounds.max);
    return distribution(generator);
}

Structures::Arrow<double> ODE::Tests::FieldGeneratorRandom::generateArrowAtPoint(const Structures::Point<double>& point) const {
    const Structures::Arrow<double> originArrow = { {0, 0}, { this->randomDouble(), this->randomDouble() } };
    return originArrow.moveBase(point);
}

Structures::Arrow<double> ODE::Tests::FieldGeneratorFunction::generateArrowAtPoint(const Structures::Point<double>& point) const {
    return { point, point + this->ode(point) };
}

std::vector<Structures::Arrow<double>> ODE::Tests::FieldGeneratorFromFile::generateField() const {
    std::ifstream file(this->fileName);
    nlohmann::json j;
    file >> j;
    file.close();
    std::vector<Structures::Arrow<double>> field;
    for (auto& element : j) {
        Structures::Point<double> start = {element["x"], element["y"]};
        Structures::Point<double> delta = {element["dx"], element["dy"]};
        field.push_back({start, start + delta});
    }
    return field;
}