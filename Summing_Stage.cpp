#include "Summing_Stage.h"

MyMat_SS PrepareSummingStage(double sampleRate)
{
    float Ts = 1 / sampleRate;

    // Parameters of circuit

    float C13 = 820e-12;
    float Rs = 1e-3;
    float R20 = 392e3;
    float R_g = 1e-3;
    //float V_gnd = 4.5;


    // WDF analysis


    float Z1 = Rs;
    float Z2 = R20;
    float Z3 = Ts / (2 * C13);
    float Z4 = R_g;

    // Computation of Scattering Matrixes

    Matrix<float, 4, 2> B_v_T;
    B_v_T << 1, 0,
             0,-1,
             0, 1,
             -1, 0; // 1 0

    Matrix<float, 2, 4> B_v = B_v_T.transpose();

    Matrix<float, 4, 2> B_i_T;
    B_i_T << 1, 0,
             1, -1,
             0, 1,
             0, 0;

    //Matrix<float, 2, 4> B_i = B_i_T.transpose();

    //diagonal matrix
    //create a diagonal matrix out of a vector
    Matrix <float, 4, 1> vector1;
    vector1 << Z1, Z2, Z3, Z4;
    MatrixXf Z;
    Z = vector1.asDiagonal();

    //identity matrix
    int rowNumber = 4;
    int columnNumber = 4;
    MatrixXf I;
    I = MatrixXf::Identity(rowNumber, columnNumber);

    MyMat_SS S;
    S << I - (2 * Z * (B_i_T * ((B_v * Z * B_i_T).inverse()) * B_v));

    //std::cout << "S matrix: \n\n" << S << std::endl;
    return S;
}

float SummingStageSample(const float inputSample, const MyMat_SS& S, Summing_Data& S_d)
{

    S_d.a[0] = inputSample;
    S_d.a[2] = S_d.b[2];
    S_d.a[3] = 4.5;
    S_d.b = S * S_d.a;
    double outputSample = (((S_d.a[1] + S_d.b[1]) + (S_d.a[0] + S_d.b[0])) / 2);
    return outputSample;
}
