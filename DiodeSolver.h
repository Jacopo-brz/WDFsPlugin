/*
  ==============================================================================

    DiodeLWSolver.h
    Created: 28 Apr 2022 10:45:52am
    Author:  Riccardo Giampiccolo

  ==============================================================================
*/

#pragma once
#include <cmath>
#include "Solver.h"

class DiodeSolver {

public:

    DiodeSolver();

    DiodeSolver(double eta, double Is, double Vt);

    ~DiodeSolver();

    double Solve(double a, double Z);

    float sgn(float val);


private:

    double eta;
    double Is;
    double Vt;

};
