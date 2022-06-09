#ifndef TONECONTROLSTAGE_H
#define TONECONTROLSTAGE_H

#endif // TONECONTROLSTAGE_H

#include "Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;
struct TC_Data
{
private:
    float R21 = 1.8e3;
    float R23 = 4.7e3;
    float R_pos = 5e3;
    float R_neg = 5e3;
    float Z2_S1 = R21;
    float Z3_S1 = R_neg;
    float Z1_S1 = Z2_S1 + Z3_S1;
    float alpha_S1 = 2 * Z3_S1 / (Z1_S1 + Z2_S1 + Z3_S1);

    //Matrix<float,3,3> S_S1 << {0, -1, -1,
    //                   -1 + alpha_S1, alpha_S1, -1 + alpha_S1,
    //                    -alpha_S1, -alpha_S1, 1 - alpha_S1};


    // S2: R23 + R_pos

    float Z2_S2 = R23;
    float Z3_S2 = R_pos;
    float Z1_S2= Z2_S2 + Z3_S2;

    float alpha_S2 = 2 * Z3_S2 / (Z1_S2 + Z2_S2 + Z3_S2);

    //Matrix<float, 3,3> S_S2 << { 0, -1, -1,
    //                          -1 + alpha_S2, alpha_S2, -1 + alpha_S2,
    //                          -alpha_S2, -alpha_S2, 1 - alpha_S2};

public:
    RowVector3f S_S1_1 = {0, -1, -1};
    RowVector3f S_S1_2 = {-1 + alpha_S1, alpha_S1, -1 + alpha_S1};
    RowVector3f S_S1_3 = {-alpha_S1, -alpha_S1, 1 - alpha_S1};

    RowVector3f S_S2_1 = {0, -1, -1};
    RowVector3f S_S2_2 = {-1 + alpha_S2, alpha_S2, -1 + alpha_S2};
    RowVector3f S_S2_3 = { -alpha_S2, -alpha_S2, 1 - alpha_S2};

    //new
    Matrix<float, 7, 1> a = { 0,0,0,0,0,0,0 };
    Matrix<float, 7, 1> b = { 0,0,0,0,6.2007e+08,0,0 };
    Matrix<float, 3, 1> a_S1 = { 0,0,0 };
    Matrix<float, 3, 1> b_S1 = { 0,0,0 };
    Matrix<float, 3, 1> a_S2 = { 0,0,0 };
    Matrix<float, 3, 1> b_S2 = { 0,0,0 };

};
typedef Matrix<float,7,7> MyMat_TC;
MyMat_TC PrepareToneCTLStage(double sampleRate);
float ToneCTLStageSample(const float inputSample, const MyMat_TC& S, TC_Data& TC_d);

