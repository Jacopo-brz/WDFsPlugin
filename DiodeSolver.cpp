
/*
  ==============================================================================

    DiodeLWSolver.cpp
    Created: 28 Apr 2022 10:45:52am
    Author:  Riccardo Giampiccolo

  ==============================================================================
*/

#include "DiodeSolver.h"
DiodeSolver::DiodeSolver()
{
}

DiodeSolver::DiodeSolver(double eta, double Is, double Vt) {
    this->eta = eta;
    this->Is = Is;
    this->Vt = Vt;

}

float DiodeSolver::sgn(float val) {
    return (0.0 < val) - (val < 0.0);
}

DiodeSolver::~DiodeSolver() {}

double DiodeSolver::Solve(double a, double Z) {
    double mod_a = std::abs(a);
    double alpha = 1 / (2 * eta * Vt);
    double beta = mod_a / (2 * eta * Vt);
    double gamma = -1 / (2 * Z * Is);
    double delta = 1 + mod_a / (2 * Z * Is);

    double x = -(Solver::omega4(beta - alpha * (delta / gamma) + Solver::logf_approx(-alpha / gamma))) / alpha - delta / gamma;

    return sgn(a) * x;
}

