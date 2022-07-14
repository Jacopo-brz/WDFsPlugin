#ifndef OUTPUTSTAGE_H
#define OUTPUTSTAGE_H

#endif // OUTPUTSTAGE_H

#include "Eigen/Dense"
#include <stdio.h>
#include <iostream>

using Eigen::MatrixXd;
using namespace Eigen;

struct Output_Data
{
    double Ts = 1.0 / 192000.0;
    //------- Cirucit Parameters -------//

    double C15 = 4.7e-6;
    double R25 = 560;
    double R28 = 100e3;
    double R_pos = 5e3;
    double R_neg = 5e3;

    //--------- WDF Free Parameters ------//

    double Z5 = R_neg;
    double Z6 = R28;
    double Z4 = (Z5 * Z6) / (Z5 + Z6);
    double Z2 = Z4;
    double Z8 = Ts / (2 * C15);
    double Z11 = R_pos;
    double Z12 = R25;
    double Z10 = Z11 + Z12;
    double Z9 = Z10;
    double Z7 = Z9 + Z8;
    double Z3 = Z7;
    double Z1 = Z2 + Z3;


    //--------- Scattering Matrix Computation ------//

    // S1

    double alpha_S1 = 2 * Z3 / (Z1 + Z2 + Z3);

    RowVector3d Sser1_1 {0, -1, -1};
    RowVector3d Sser1_2 {-1 + alpha_S1, alpha_S1, -1 + alpha_S1};
    RowVector3d Sser1_3 {-alpha_S1, -alpha_S1, 1 - alpha_S1};

    // S2

    double alpha_S2 = 2 * Z9 / (Z7 + Z8 + Z9);

    RowVector3d Sser2_1 {0, -1, -1};
    RowVector3d Sser2_2 {-1 + alpha_S2, alpha_S2, -1 + alpha_S2};
    RowVector3d Sser2_3 {-alpha_S2, -alpha_S2, 1 - alpha_S2};

    // S3

    double alpha_S3 = 2 * Z12 / (Z10 + Z11 + Z12);

    RowVector3d Sser3_1  {0, -1, -1};
    RowVector3d Sser3_2  {-1 + alpha_S3, alpha_S3, -1 + alpha_S3};
    RowVector3d Sser3_3  {-alpha_S3, -alpha_S3, 1 - alpha_S3};

    // P1 (R_neg||R28)

    double alpha_P1 = 2 * 1 / Z6 / (1 / Z4 + 1 / Z5 + 1 / Z6);

    RowVector3d Spar1_1   {0, 1 - alpha_P1, alpha_P1};
    RowVector3d Spar1_2   {1, -alpha_P1, alpha_P1};
    RowVector3d Spar1_3   {1, 1 - alpha_P1, alpha_P1 - 1};

    Matrix<double, 12, 1> a {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    Matrix<double, 12, 1> b {0, 0, 0, 0, 0, 0, 0,  -126.2125, 0, 0, 0, 0};
    Matrix<double, 3, 1> adapt_par1;
    Matrix<double, 3, 1> adapt_ser1;
    Matrix<double, 3, 1> adapt_ser2;
    Matrix<double, 3, 1> adapt_ser3;

    Matrix<double, 3, 1> a_block1;
    Matrix<double, 3, 1> a_block2;
    Matrix<double, 3, 1> a_block3;
    Matrix<double, 3, 1> a_block4;
};

typedef Matrix<float,5,5> MyMat_OUT;
float OutputStageSample(const float inputSample, Output_Data& O_d);
void UpdateKnob_OutputStage(Output_Data& O_d, float out_knob);
