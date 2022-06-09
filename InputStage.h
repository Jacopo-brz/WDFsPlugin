#ifndef INPUTSTAGE_H
#define INPUTSTAGE_H

#endif // INPUTSTAGE_H

#include "Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;

struct Input_Data
{
    Matrix<float, 5, 1> a = {0,0,0,0,0};
    Matrix<float, 5, 1> b = {0,0,4.5,0,0};

};

typedef Matrix<float,5,5> MyMat_IN;
MyMat_IN PrepareInputStage(double sampleRate);
float InputStageSample(const float inputBuffer, const MyMat_IN& S, Input_Data& I_d);
