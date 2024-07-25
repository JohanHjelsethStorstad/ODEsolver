#include "IterationScheme.h"

Structures::Point<double> ODE::IterationScheme::prime(Structures::Point<double> point)  {
	Structures::Arrow<double> arrow = this->inferationScheme->infer(this->primeField, point).moveToOrigin();
	return arrow.end;
}

Structures::Point<double> ODE::IterationScheme::step(Structures::Point<double> prev, double dt) {
	const int order = this->butcherTableau->getOrder();
	std::vector<Structures::Point<double>> k;
	k.push_back(this->prime(prev));
	for (int i = 1; i < order; i++) {
		Structures::Point<double> sum = { 0, 0 };
		for (int j = 0; j < i; j++) {
			sum = sum + this->butcherTableau->getA(i, j) * k.at(j);
		}
		k.push_back(this->prime(prev + dt * sum));
	}
	Structures::Point<double> sum = { 0, 0 };
	for (int i = 0; i < order; i++) {
		sum = sum + this->butcherTableau->getB(i) * k.at(i);
	}
	const Structures::Point<double> next = prev + dt * sum;
	return next;
}