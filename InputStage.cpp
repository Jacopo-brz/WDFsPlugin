#include "InputStage.h"

MyMat_IN PrepareInputStage(double sampleRate)
{
    //parameters of circuit

        //double V_gnd = -4.5; non useful here
        float R_gnd = 1e-3;
        float Rs = 1e-3;
        float R1 = 1e4;
        float C1 = 0.1e-6;
        float R2 = 1e6;
        float Ts = 1/sampleRate;
        //WDF analysis
        float Z1 = Rs;
        float Z2 = R1;
        float Z3 = Ts/(2*C1);
        float Z4 = R2;
        float Z5 = R_gnd;


        Matrix<float, 5, 1> Bt = {1, 1, 1, 1, 1};
        Matrix<float, 1,5> B = Bt.transpose();
        Matrix <float, 5, 1> vector1;
        vector1 << Z1, Z2, Z3, Z4, Z5;
        MatrixXf Z;
        Z = vector1.asDiagonal();
        int rowNumber = 5;
        int columnNumber = 5;
        MatrixXf I;
        I = MatrixXf::Identity(rowNumber,columnNumber);

        MyMat_IN S;
        S << (I-2*Z*Bt*((B*Z*Bt).inverse())*B);
        //std::cout << "S input: \n" << S << std::endl;
        return S;

}

float InputStageSample(const float inputSample, const MyMat_IN& S, Input_Data& I_d)
{
    //outputBuffer[i] = inputBuffer[i] * 0.1;
    I_d.a[0] = inputSample;
    I_d.a[2] = I_d.b[2];
    I_d.a[4] = -4.5; //V_gnd
    I_d.b = S*I_d.a;
    double outputSample = (-(I_d.a[3]+I_d.b[3] + I_d.a[4]+I_d.b[4])/2);// - 4.5;
    return outputSample;

}

