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
    float Ts = 1.0 / 192000.0;
    float C14 = 3.9e-9;
    float Rs = 1e-3;
    float R22 = 100e3;
    float R24 = 100e3;

    //float V_gnd = 4.5;
    float R_gnd = 1e-3;

public:

    float R21 = 1.8e3;
    float R23 = 4.7e3;
    float R_pos = 5e3;
    float R_neg = 5e3;
    float Z2_S1 = R21;
    float Z3_S1 = R_neg;
    float Z1_S1 = Z2_S1 + Z3_S1;
    float alpha_S1 = 2 * Z3_S1 / (Z1_S1 + Z2_S1 + Z3_S1);
    float Z2_S2 = R23;
    float Z3_S2 = R_pos;
    float Z1_S2= Z2_S2 + Z3_S2;
    float alpha_S2 = 2 * Z3_S2 / (Z1_S2 + Z2_S2 + Z3_S2);

    //float Z_S1 = R21 + R_neg;
    //float Z_S2 = R23 + R_pos;
    float Z1 = Rs;
    float Z2 = R22;
    float Z3 = Z1_S1;
    float Z4 = Z1_S2;
    float Z5 = Ts / (2 * C14);
    float Z6 = R24;
    float Z7 = R_gnd;

    RowVector3f S_S1_1 = {0, -1, -1};
    RowVector3f S_S1_2 = {-1 + alpha_S1, alpha_S1, -1 + alpha_S1};
    RowVector3f S_S1_3 = {-alpha_S1, -alpha_S1, 1 - alpha_S1};

    RowVector3f S_S2_1 = {0, -1, -1};
    RowVector3f S_S2_2 = {-1 + alpha_S2, alpha_S2, -1 + alpha_S2};
    RowVector3f S_S2_3 = { -alpha_S2, -alpha_S2, 1 - alpha_S2};

    Matrix<float, 7, 1> a = { 0,0,0,0,0,0,0 };
    Matrix<float, 7, 1> b = { 0,0,0,0,14.5296,0,0 };
    //Matrix<float, 7, 1> b = { 0,0,0,0,-10.5262,0,0 };
    Matrix<float, 3, 1> a_S1 = { 0,0,0 };
    Matrix<float, 3, 1> b_S1 = { 0,0,0 };
    Matrix<float, 3, 1> a_S2 = { 0,0,0 };
    Matrix<float, 3, 1> b_S2 = { 0,0,0 };

    Matrix <float, 7, 1> vectorZ = {Z1, Z2, Z3, Z4, Z5, Z6, Z7};
    MatrixXf Z = vectorZ.asDiagonal();

    MatrixXf I = MatrixXf::Identity(7, 7);

};
typedef Matrix<float,7,7> MyMat_TC;

MyMat_TC PrepareToneCTLStage(double sampleRate);
MyMat_TC PrepareToneCTLStage_Knob(TC_Data& T_d, float treble_knob);
float ToneCTLStageSample(const float inputSample, const MyMat_TC& S, TC_Data& TC_d);

typedef Matrix<float, 9,9> MyMat_TC_9x9;
struct TC_Data_9x9
{
    Matrix<float, 9, 1> a = { 0,0,0,0,0,0,0,0,0};
    Matrix<float, 9, 1> b = { 0,0,0,0,0,0,14.5296,0,0};
   // Matrix<float, 9, 1> b = { 0,0,0,0,0,0,6.2007e+08,0,0};
};

MyMat_TC_9x9 PrepareToneCTLStage_Knob_9x9(const float treble_knob);
float ToneCTLStageSample_9x9(const float inputSample, const MyMat_TC_9x9& S, TC_Data_9x9& TC_d);
