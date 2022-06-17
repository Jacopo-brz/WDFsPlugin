#ifndef SUMMING_STAGE_H
#define SUMMING_STAGE_H

#endif // SUMMING_STAGE_H

#include "Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;

struct Summing_Data
{
    Matrix<float, 4, 1> a = { 0,0,0,0};
    //Matrix<float, 4, 1> b = { 0,0,-3.5280e+09,0};
    Matrix<float, 4, 1> b = { 0,0,82.5576,0};
    //double M = 2.15685e+09;
    //double m = 1.3711e+09;
};

typedef Matrix<float,4,4> MyMat_SS;
MyMat_SS PrepareSummingStage(double sampleRate);
float SummingStageSample(const float inputSample, const MyMat_SS& S, Summing_Data& S_s);
