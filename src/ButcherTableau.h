#pragma once
#include "Logger.h"
#include <array>
#include <string>

namespace ODE::BucherTableau {
	class ButcherTableau {
	protected:
		std::string name = "Butcher Tableau";
	public:
		virtual void logInfo() = 0;
		virtual inline double getA(int i, int j) const = 0;
		virtual inline double getB(int i) const = 0;
		virtual inline double getC(int i) const = 0;
		virtual inline int getOrder() const = 0;
		inline void setName(const std::string& name) {
			this->name = name;
		}
		inline std::string getName() const {
			return this->name;
		}
	};

	template<int order>
	class ExplicitButcherTableau : public ButcherTableau {
	private:
		std::array<std::array<double, order>, order> a;
		std::array<double, order> b;
		std::array<double, order> c;
		void makeExplicit() {
			for (int i = 0; i < order; i++) {
				for (int j = i; j < order; j++) {
					a[i][j] = 0;
				}
			}
			c[0] = 0;
		}
	public:
		ExplicitButcherTableau(
			std::array<std::array<double, order>, order> a,
			std::array<double, order> b,
			std::array<double, order> c
		) : a(a), b(b), c(c) {
			this->makeExplicit();
		}
		bool checkConsistency(float margin = 0.02) const {
			double sum = 0;
			for (int i = 0; i < order; i++) {
				sum += b[i];
			}
			//Must be close to 1
			return std::abs(sum - 1) < margin;
		}
		void logInfo() override {
			auto logger = Logger::Loggers::getLogger(Logger::LogFile::ODE);
			logger << "===========================================" << "\n";
			logger << "Butcher Tableau\n";
			logger << "Name: " << this->name << "\n";
			logger << "Order: " << std::to_string(order) << "\n";
			logger << "consistant?: " << (this->checkConsistency() ? "yes" : "no") << "\n";
			logger << "===========================================" << "\n";
		}
		inline double getA(int i, int j) const override {
			return a.at(i).at(j);
		}
		inline double getB(int i) const override {
			return b.at(i);
		}
		inline double getC(int i) const override {
			return c.at(i);
		}
		inline int getOrder() const override {
			return order;
		}
		static ExplicitButcherTableau<1> Euler() {
			std::array<std::array<double, 1>, 1> a = { { 0 } };
			std::array<double, 1> b = { 1 };
			std::array<double, 1> c = { 0 };
			ExplicitButcherTableau<1> tableau(a, b, c);
			tableau.setName("Euler");
			tableau.logInfo();
			return tableau;
		}

		static ExplicitButcherTableau<2> Heun() {
			std::array<std::array<double, 2>, 2> a = { { { 0, 0 }, { 1, 0 } } };
			std::array<double, 2> b = { 0.5, 0.5 };
			std::array<double, 2> c = { 0, 1 };
			ExplicitButcherTableau<2> tableau(a, b, c);
			tableau.setName("Heun");
			tableau.logInfo();
			return tableau;
		}

		static ExplicitButcherTableau<4> RungeKutta4() {
			std::array<std::array<double, 4>, 4> a = { { { 0, 0, 0, 0 }, { 0.5, 0, 0, 0 }, { 0, 0.5, 0, 0 }, { 0, 0, 1, 0 } } };
			std::array<double, 4> b = { 1.0 / 6, 1.0 / 3, 1.0 / 3, 1.0 / 6 };
			std::array<double, 4> c = { 0, 0.5, 0.5, 1 };
			ExplicitButcherTableau<4> tableau(a, b, c);
			tableau.setName("Runge-Kutta 4");
			tableau.logInfo();
			return tableau;
		}

		static ExplicitButcherTableau<4> RungeKutta3() {
			std::array<std::array<double, 4>, 4> a = { { { 0, 0, 0, 0 }, { 0.5, 0, 0, 0 }, { -1, 2, 0, 0 }, { 1, -2, 2, 0 } } };
			std::array<double, 4> b = { 1.0 / 6, 2.0 / 3, 1.0 / 6, 0 };
			std::array<double, 4> c = { 0, 0.5, 1, 1 };
			ExplicitButcherTableau<4> tableau(a, b, c);
			tableau.setName("Runge-Kutta 3");
			tableau.logInfo();
			return tableau;
		}
	};
}