#include "ToneControlStage.h"

MyMat_TC PrepareToneCTLStage(double sampleRate)
{
    //parameters of circuit

    float Ts = 1 / sampleRate;

    //parameters of circuit

    float C14 = 3.9e-9;

    float Rs = 1e-3;
    float R21 = 1.8e3;
    float R22 = 100e3;
    float R23 = 4.7e3;
    float R24 = 100e3;
    float R_pos = 5e3;
    float R_neg = 5e3;

    //float V_gnd = 4.5;
    float R_gnd = 1e-3;



    //WDF analysis

    float Z_S1 = R21 + R_neg;
    float Z_S2 = R23 + R_pos;

    float Z1 = Rs;
    float Z2 = R22;
    float Z3 = Z_S1;
    float Z4 = Z_S2;
    float Z5 = Ts / (2 * C14);
    float Z6 = R24;
    float Z7 = R_gnd;

    Matrix<float, 3, 7> B_i;
    B_i << 1, 0, 1, -1, 0, 0, 0,
           0, -1, -1, 0, 1, 0, 0,
           0, 1, 1, -1, 0, 1, 0;
    std::cout << "B_i: " << B_i << std::endl;

    Matrix<float, 7, 3> B_i_T = B_i.transpose();
    std::cout << "B_i_T: " << B_i_T << std::endl;

    Matrix<float, 3, 7> B_v;
    B_v << 1,-1, 0, 0, 0, 0,-1,
           0,-1,-1, 0, 1, 0, 0,
           0, 1, 1,-1, 0, 1, 0;
    std::cout << "B_v: " << B_v << std::endl;

    Matrix<float, 7, 3> B_v_T = B_v.transpose();
    std::cout << "B_v_T: " << B_v_T << std::endl;


    //diagonal matrix
    //create a diagonal matrix out of a vector
    Matrix <float, 7, 1> vector1;
    vector1 << Z1, Z2, Z3, Z4, Z5, Z6, Z7;
    MatrixXf Z;
    Z = vector1.asDiagonal();
    std::cout << " Diagonal matrix is \n\n" << Z << std::endl;


    //identity matrix
    int rowNumber = 7;
    int columnNumber = 7;
    MatrixXf I;
    I = MatrixXf::Identity(rowNumber, columnNumber);
    std::cout << " Identity matrix is \n\n" << I << std::endl;


    Matrix<float, 7, 7> S;
    S = (I - 2 * Z * B_i_T * ((B_v * Z * B_i_T).inverse()) * B_v);
    std::cout << "S tone control: \n" << S << std::endl;
    return S;

}

float ToneCTLStageSample(const float inputSample, const MyMat_TC& S, TC_Data& TC_d)
{

    TC_d.a[0] = inputSample;
    TC_d.a[4] = TC_d.b[4];
    TC_d.a[6] = 4.5;

    // S1

    TC_d.b_S1[0] = TC_d.S_S1_1 * TC_d.a_S1;

    // S2

    TC_d.b_S2[0] = TC_d.S_S2_1 * TC_d.a_S2;


    //waves reflected from series adaptors, incident toward S

    TC_d.a[2] = TC_d.b_S1[0];
    TC_d.a[3] = TC_d.b_S2[0];

    // Scattering stage
    TC_d.b = S * TC_d.a;


    // Backward Scan

    // S1
    TC_d.a_S1[0] = TC_d.b[2]; // from S
    TC_d.b_S1[1] = TC_d.S_S1_2 * TC_d.a_S1;
    TC_d.b_S1[2] = TC_d.S_S1_3 * TC_d.a_S1;

    // S2
    TC_d.a_S2[0] = TC_d.b[3]; // from S
    TC_d.b_S2[1] = TC_d.S_S2_2 * TC_d.a_S2;
    TC_d.b_S2[2] = TC_d.S_S2_3 * TC_d.a_S2;

    double outputSample =(-(TC_d.a[5] + TC_d.b[5] - (TC_d.a[6] + TC_d.b[6])) / 2);
    return outputSample;

}
