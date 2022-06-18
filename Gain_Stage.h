/*
  ==============================================================================

    Gain_Stage.h
    Created: 20 May 2022 10:58:20am
    Author:  franc

  ==============================================================================
*/

#pragma once

#ifndef GAIN_STAGE_H
#define GAIN_STAGE_H

#endif 

#include "Eigen/Dense"
#include <stdio.h>
#include <iostream>
#include "DiodeSolver.h"

using Eigen::MatrixXd;
using namespace Eigen;

struct Gain_Data
{
private:
    double Ts = 1.0 / 192000.0;
    //double Ts = 0.520833333332e-5;

    //parameters of circuit
    double C3 = 0.1e-6;
    double C4 = 68e-9;
    double C5 = 68e-9;
    double C6 = 390e-9;
    double C7 = 82e-9;
    double C8 = 390e-12;
    double C9 = 1e-6;
    double C10 = 1e-6;
    double C16 = 1e-6;
    double C11 = 2.2e-9;
    double C12 = 27e-9;


    double Rs = 1e-3;
    double R5 = 5.1e3;
    double R8 = 1.5e3;
    double R9 = 1e3;

    double R15 = 22e3;
    double R17 = 27e3;
    double R18 = 12e3;
    double R16 = 47e3;
    double R13 = 1e3;
    double R12 = 422e3;
    double R11 = 15e3;

    double R6 = 10e3;
    double R7 = 1.5e3;
    double R19 = 15e3;
    double R_gnd = 1e-3;
    //double V_gnd = -4.5;


    // WDF setting of free parameters(adaptation conditions)

    double ZS1 = R15 + Ts / (2 * C11);
    double ZS2 = R13 + Ts / (2 * C9);

    double ZP1 = (R5 * Ts / (2 * C4)) / (R5 + Ts / (2 * C4));

    double ZS_P2 = R9 + Ts / (2 * C6);
    double ZP2 = (R8 * ZS_P2) / (R8 + ZS_P2);

    //double ZP3 = (R11 * Ts / (2 * C7)) / (R11 + Ts / (2 * C7));
    double ZP4 = (R12 * Ts / (2 * C8)) / (R12 + Ts / (2 * C8));

    double ZS_P5 = R18 + Ts / (2 * C12);
    double ZP5 = (R17 * ZS_P5) / (R17 + ZS_P5);


    double ZP6 = (R6 * Ts / (2 * C5)) / (R6 + Ts / (2 * C5));

    //WDF analysis


//    double z21 = 964.6072;

    //-------- Series Scattering Matrixes ---------//

    // S1: C11 + R15

    double Z2_S1 = Ts / (2 * C11);
    double Z3_S1 = R15;
    double Z1_S1 = Z2_S1 + Z3_S1;

    double alpha_S1 = 2 * Z3_S1 / (Z1_S1 + Z2_S1 + Z3_S1);

    // S2: C9 + R13

    double Z2_S2 = Ts / (2 * C9);
    double Z3_S2 = R13;
    double Z1_S2 = Z2_S2 + Z3_S2;

    double alpha_S2 = 2 * Z3_S2 / (Z1_S2 + Z2_S2 + Z3_S2);


    // S_P2: R9 + C6

    double Z2_S_P2 = Ts / (2 * C6);
    double Z3_S_P2 = R9;
    double Z1_S_P2 = Z2_S_P2 + Z3_S_P2;

    double alpha_S_P2 = 2 * Z3_S_P2 / (Z1_S_P2 + Z2_S_P2 + Z3_S_P2);

    // S_P5: C12+R18

    double Z2_S_P5 = Ts / (2 * C12);
    double Z3_S_P5 = R18;
    double Z1_S_P5 = Z2_S_P5 + Z3_S_P5;

    double alpha_S_P5 = 2 * Z3_S_P5 / (Z1_S_P5 + Z2_S_P5 + Z3_S_P5);

    //---------- Parallel scattering junctions ----------//

    //P1: R5//C4

    double Z2_P1 = Ts / (2 * C4);
    double Z3_P1 = R5;
    double Z1_P1 = Z2_P1 * Z3_P1 / (Z2_P1 + Z3_P1);

    double alpha_P1 = (2 * (1 / Z3_P1)) / (1 / Z1_P1 + 1 / Z2_P1 + 1 / Z3_P1);

    // P2: R8 // (C6 + R9)

    double Z2_P2 = R8;
    double Z3_P2 = Z1_S_P2;
    double Z1_P2 = (Z2_P2 * Z3_P2) / (Z2_P2 + Z3_P2);

    double alpha_P2 = (2 * 1 / Z3_P2) / (1 / Z1_P2 + 1 / Z2_P2 + 1 / Z3_P2);

    // P3: R11//C7

    double Z2_P3 = Ts / (2 * C7);
    double Z3_P3 = R11;
    double Z1_P3 = Z2_P3 * Z3_P3 / (Z2_P3 + Z3_P3);

    double alpha_P3 = 2 * 1 / Z3_P3 / (1 / Z1_P3 + 1 / Z2_P3 + 1 / Z3_P3);

    // P4: R12//C8

    double Z2_P4 = Ts / (2 * C8);
    double Z3_P4 = R12;
    double Z1_P4 = Z2_P4 * Z3_P4 / (Z2_P4 + Z3_P4);

    double alpha_P4 = (2 * 1 / Z3_P4) / (1 / Z1_P4 + 1 / Z2_P4 + 1 / Z3_P4);

    // P5: R17//C12+R18

    double Z2_P5 = R17;
    double Z3_P5 = Z1_S_P5;
    double Z1_P5 = (Z2_P5 * Z3_P5) / (Z2_P5 + Z3_P5);

    double alpha_P5 = (2 * 1 / Z3_P5) / (1 / Z1_P5 + 1 / Z2_P5 + 1 / Z3_P5);

    // P6: C5//R6

    double Z2_P6 = Ts / (2 * C5);
    double Z3_P6 = R6;
    double Z1_P6 = (Z2_P6 * Z3_P6) / (Z2_P6 + Z3_P6);

    double alpha_P6 = (2 * 1 / Z3_P6) / (1 / Z1_P6 + 1 / Z2_P6 + 1 / Z3_P6);



public:

    //resistances associated with potentiometer values, initialized at 0.5
    double Rb_neg = 50e3;
    double Rb_pos = 50e3;
    double Ra_neg = 50e3;
    double Ra_pos = 50e3;
    double R10 = 2e3; //this affects ZS3

    double Z1 = Rs;
    double Z2 = ZP1;
    double Z3 = Ts / (2 * C3);
    double Z4 = Rb_pos;
    double Z5 = Rb_neg;
    double Z6 = ZP2;
    double Z7 = R_gnd;
    double Z8 = ZS1;
    double Z9 = ZP5;
    double Z10 = R16;
    double Z11 = R19;
    double Z12 = R7;
    double Z13 = Ts / (2 * C16);
    double Z14 = ZP6;
    double Z15 = Ra_pos;
    double Z16 = R_gnd;
    // Z17->series btw ZS3and ZP3

    double ZS3 = Ra_neg + R10;
    double ZP3 = (R11 * Ts / (2 * C7)) / (R11 + Ts / (2 * C7));

    double Z17 = ZS3 + ZP3;
    double Z18 = ZP4;
    double Z19 = ZS2;
    double Z20 = Ts / (2 * C10);




    //all Z depending on potentiometers are here:




    double Z21_99_pot[99] = {946.214449213152,	948.278467952844,	950.020876565131,	951.510494343247,	952.797781360266,	953.920577666227,	954.907815390418,	955.781993217046,	956.560869352618,
                             957.258646552570,	957.886818536016,	958.454785535998,	958.970309252039,	959.439854047947,	959.868846247091,	960.261873576142,	960.622840274241,	960.955088950876,
                             961.261497218071,	961.544554982181,	961.806426761646,	962.049002305334,	962.273937992151,	962.482690908748,	962.676547068518,	962.856644909744,	963.023994964643,
                             963.179496403138,	963.323951010693,	963.458075047494,	963.582509348806,	963.697827957638,	963.804545526422,	963.903123681195,	963.993976507112,	964.077475286199,
                             964.153952595724,	964.223705857111,	964.287000410338,	964.344072176316,	964.395129959536,	964.440357434704,	964.479914853962,	964.513940505230,	964.542551947101,
                             964.565847041314,	964.583904800000,	964.596786061583,	964.604534006230,	964.607174519037,	964.604716406695,	964.597151471026,	964.584454440531,	964.566582758892,
                             964.543476227096,	964.515056493569,	964.481226384182,	964.441869061344,	964.396846998436,	964.346000752491,	964.289147514249,	964.226079410333,	964.156561527195,
                             964.080329620478,	963.997087466343,	963.906503802823,	963.808208799074,	963.701789978121,	963.586787503698,	963.462688723597,	963.328921839453,	963.184848545267,
                             963.029755442562,	962.862843997159,	962.683218748637,	962.489873415385,	962.281674451472,	962.057341500523,	961.815424048597,	961.554273391957,	961.272008791869,
                             960.966476366558,	960.635198841286,	960.275313699940,	959.883496496431,	959.455865004998,	958.987858387804,	958.474083444418,	957.908116989648,	957.282249032270,
                             956.587144985085,	955.811395479902,	954.940907602004,	953.958068315644,	952.840574015055,	951.559759675728,	950.078158875256,	948.345847313554,	946.294798120955};
    double z21 = 964.6072; //knob = 0.5

    MatrixXd I = MatrixXd::Identity(21, 21);

    //scattering matrices depending on potentiometer value
    // S3: Ra_neg + R10
    double Z2_S3 = Ra_neg;
    double Z3_S3 = R10;
    double Z1_S3 = Z2_S3 + Z3_S3;

    double alpha_S3 = 2 * Z3_S3 / (Z1_S3 + Z2_S3 + Z3_S3);

    // S3P3 : S3 (Ra_neg + R10)  + P3 (R11//C7)
    double  Z2_S3P3 = Z1_P3;
    double Z3_S3P3 = Z1_S3;
    double Z1_S3P3 = Z2_S3P3 + Z3_S3P3;

    double alpha_S3P3 = (2 * Z3_S3P3) / (Z1_S3P3 + Z2_S3P3 + Z3_S3P3);

    //-------- Series Scattering Matrixes ---------//

    // S1: C11 + R15

    RowVector3d S_S1_1 = { 0, -1, -1 };
    RowVector3d S_S1_2 = { -1 + alpha_S1, alpha_S1, -1 + alpha_S1 };
    RowVector3d S_S1_3 = { -alpha_S1, -alpha_S1, 1 - alpha_S1 };

    // S2: C9 + R13

    RowVector3d S_S2_1 = { 0, -1, -1 };
    RowVector3d S_S2_2 = { -1 + alpha_S2, alpha_S2, -1 + alpha_S2 };
    RowVector3d S_S2_3 = { -alpha_S2, -alpha_S2, 1 - alpha_S2 };

    // S3: Ra_neg + R10

    RowVector3d S_S3_1 = { 0, -1, -1 };
    RowVector3d S_S3_2 = { -1 + alpha_S3, alpha_S3, -1 + alpha_S3 };
    RowVector3d S_S3_3 = { -alpha_S3, -alpha_S3, 1 - alpha_S3 };

    // S_P2: R9 + C6

    RowVector3d S_S_P2_1 = { 0, -1, -1 };
    RowVector3d S_S_P2_2 = { -1 + alpha_S_P2, alpha_S_P2, -1 + alpha_S_P2 };
    RowVector3d S_S_P2_3 = { -alpha_S_P2, -alpha_S_P2, 1 - alpha_S_P2 };

    // S_P5: C12+R18

    RowVector3d S_S_P5_1 = { 0, -1, -1 };
    RowVector3d S_S_P5_2 = { -1 + alpha_S_P5, alpha_S_P5, -1 + alpha_S_P5 };
    RowVector3d S_S_P5_3 = { -alpha_S_P5, -alpha_S_P5, 1 - alpha_S_P5 };

    //---------- Parallel scattering junctions ----------//

    //P1: R5//C4

    RowVector3d S_P1_1 = { 0, 1 - alpha_P1, alpha_P1 };
    RowVector3d S_P1_2 = { 1, -alpha_P1, alpha_P1 };
    RowVector3d S_P1_3 = { 1, 1 - alpha_P1, alpha_P1 - 1 };

    // P2: R8 // (C6 + R9)

    RowVector3d S_P2_1 = { 0, 1 - alpha_P2, alpha_P2 };
    RowVector3d S_P2_2 = { 1, -alpha_P2, alpha_P2 };
    RowVector3d S_P2_3 = { 1, 1 - alpha_P2, alpha_P2 - 1 };

    // P3: R11//C7

    RowVector3d S_P3_1 = { 0, 1 - alpha_P3, alpha_P3 };
    RowVector3d S_P3_2 = { 1, -alpha_P3, alpha_P3 };
    RowVector3d S_P3_3 = { 1, 1 - alpha_P3, alpha_P3 - 1 };

    // P4: R12//C8

    RowVector3d S_P4_1 = { 0, 1 - alpha_P4, alpha_P4 };
    RowVector3d S_P4_2 = { 1, -alpha_P4, alpha_P4 };
    RowVector3d S_P4_3 = { 1, 1 - alpha_P4, alpha_P4 - 1 };

    // P5: R17//C12+R18

    RowVector3d S_P5_1 = { 0, 1 - alpha_P5, alpha_P5 };
    RowVector3d S_P5_2 = { 1, -alpha_P5, alpha_P5 };
    RowVector3d S_P5_3 = { 1, 1 - alpha_P5, alpha_P5 - 1 };

    // P6: C5//R6

    RowVector3d S_P6_1 = { 0, 1 - alpha_P6, alpha_P6 };
    RowVector3d S_P6_2 = { 1, -alpha_P6, alpha_P6 };
    RowVector3d S_P6_3 = { 1, 1 - alpha_P6, alpha_P6 - 1 };

    // S3P3 : S3 (Ra_neg + R10)  + P3 (R11//C7)

    RowVector3d S_S3P3_1 = { 0, -1, -1 };
    RowVector3d S_S3P3_2 = { -1 + alpha_S3P3, alpha_S3P3, -1 + alpha_S3P3 };
    RowVector3d S_S3P3_3 = { -alpha_S3P3, -alpha_S3P3, 1 - alpha_S3P3 };

    // VALORI CHE VENGONO MODIFICATI RUNTIME

    Matrix<double, 21, 1> a = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    Matrix<double, 21, 1> b = { 0, 0, -1.7205e-07, 0, 0, 0, 0, 0, 0, 0, 0, 0, -4.5, 0, 0, 0, 0, 0, 0,  4.5, 0 };


    // S1: C11 + R15

    Matrix<double, 3, 1> a_S1 = { 0,0,0 };
    Matrix<double, 3, 1> b_S1 = { 0,3.6603e-07,0 };

    // S2: C9 + R13

    Matrix<double, 3, 1> a_S2 = { 0,0,0 };
    Matrix<double, 3, 1> b_S2 = { 0,4.5,0 };

    // S3: Ra_neg + R10

    Matrix<double, 3, 1> a_S3 = { 0,0,0 };
    Matrix<double, 3, 1> b_S3 = { 0,0,0 };

    //-------- Series inside parallel ---------//

    // S_P2: R9 + C6

    Matrix<double, 3, 1> a_S_P2 = { 0,0,0 };
    Matrix<double, 3, 1> b_S_P2 = { 0,-4.8241e-09,0 };

    // S_P5: C12+R18

    Matrix<double, 3, 1> a_S_P5 = { 0,0,0 };
    Matrix<double, 3, 1> b_S_P5 = { 0,1.0847e-07,0 };

    //---------- Parallel scattering junctions ----------//

    //P1: R5//C4

    Matrix<double, 3, 1> a_P1 = { 0,0,0 };
    Matrix<double, 3, 1> b_P1 = { 0,6.3830e-09,0 };

    // P2: R8 // (C6 + R9)

    Matrix<double, 3, 1> a_P2 = { 0,0,0 };
    Matrix<double, 3, 1> b_P2 = { 0,0,0 };


    // P3: R11//C7

    Matrix<double, 3, 1> a_P3 = { 0,0,0 };
    Matrix<double, 3, 1> b_P3 = { 0,3.4408e-08,0 };

    // P4: R12//C8

    Matrix<double, 3, 1> a_P4 = { 0,0,0 };
    Matrix<double, 3, 1> b_P4 = { 0,-9.6015e-07,0 };

    // P5: R17//C12+R18

    Matrix<double, 3, 1> a_P5 = { 0,0,0 };
    Matrix<double, 3, 1> b_P5 = { 0,0,0 };

    // P6: C5//R6

    Matrix<double, 3, 1> a_P6 = { 0,0,0 };
    Matrix<double, 3, 1> b_P6 = { 0,3.0673e-08,0 };

    // S3P3 : S3 (Ra_neg + R10)  + P3 (R11//C7)

    Matrix<double, 3, 1> a_S3P3 = { 0,0,0 };
    Matrix<double, 3, 1> b_S3P3 = { 0,0,0 };

    //DIODO
    double eta = 1.6;
    double Is = 2.6e-6;
    double Vt = 25.8e-3;
    DiodeSolver diode = DiodeSolver(eta, Is, Vt);
};

typedef Matrix<double, 21, 21> MyMat_G;
MyMat_G PrepareGainStage(double sampleRate);
MyMat_G PrepareGainStage_Knob(float gain_pot, Gain_Data& G_d);
float GainStageSample(const float input, const MyMat_G& S_g, Gain_Data& G_d);

