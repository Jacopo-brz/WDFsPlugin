#include "OutputStage.h"

float OutputStageSample(const float inputSample, Output_Data& O_d)
{
    //Manage Dynamic Elements

    O_d.a[7] = O_d.b[7];

    //Forward Scan

    O_d.adapt_par1 = {0, O_d.a[4], O_d.a[5]};

    O_d.b[3] = O_d.Spar1_1 * O_d.adapt_par1;

    O_d.adapt_ser2 = {0, O_d.a[7], O_d.a[8]};

    O_d.b[6] = O_d.Sser2_1 * O_d.adapt_ser2;

    O_d.adapt_ser3 << 0, O_d.a[10], O_d.a[11];

    O_d.b[9] = O_d.Sser3_1 * O_d.adapt_ser3;

    O_d.a[1] = O_d.b[3];
    O_d.a[2] = O_d.b[6];

    O_d.adapt_ser1 << 0, O_d.a[1], O_d.a[2];

    O_d.b[0] = O_d.Sser1_1 * O_d.adapt_ser1;


    //Scattering stage

    O_d.a[0] = 2 * inputSample - O_d.b[0];


    //Backward Scan

    O_d.a_block1 << O_d.a.block(0, 0, 3, 1);

    O_d.b[1] = O_d.Sser1_2 * O_d.a_block1;
    O_d.b[2] = O_d.Sser1_3 * O_d.a_block1;

    O_d.a_block2 << O_d.a.block(3, 0, 3, 1);

    O_d.a[3] = O_d.b[1];
    O_d.b[4] = O_d.Spar1_2 * O_d.a_block2;
    O_d.b[5] = O_d.Spar1_3 * O_d.a_block2;

    O_d.a_block3 << O_d.a.block(6, 0, 3, 1);

    O_d.a[6] = O_d.b[2];
    O_d.b[7] = O_d.Sser2_2 * O_d.a_block3;
    O_d.b[8] = O_d.Sser2_3 * O_d.a_block3;

    O_d.a_block4 << O_d.a.block(9, 0, 3, 1);

    O_d.a[9] = O_d.b[8];
    O_d.b[10] = O_d.Sser3_2 * O_d.a_block4;
    O_d.b[11] = O_d.Sser3_3 * O_d.a_block4;


    // Read Output
    double out_sample = (-(O_d.a[5] + O_d.b[5]) / 2);
    double out_normie = (out_sample-(-1.1149e7))/(1.1149e7-(-1.1149e7)) -0.5; //normalize wrt matlab max, min
    return out_normie;
}

void UpdateKnob_OutputStage(Output_Data& O_d, float out_knob)
{
    O_d.Z5 = O_d.R_neg * (out_knob); //R-
    O_d.Z4 = (O_d.Z5 * O_d.Z6) / (O_d.Z5 + O_d.Z6);
    O_d.Z2 = O_d.Z4;
    O_d.Z11 = O_d.R_pos * (1-out_knob); //R+
    O_d.Z10 = O_d.Z11 + O_d.Z12;
    O_d.Z9 = O_d.Z10;
    O_d.Z7 = O_d.Z9 + O_d.Z8;
    O_d.Z3 = O_d.Z7;
    O_d.Z1 = O_d.Z2 + O_d.Z3;


    // S1

    O_d.alpha_S1 = 2 * O_d.Z3 / (O_d.Z1 + O_d.Z2 + O_d.Z3);


    O_d.Sser1_2 = {-1 + O_d.alpha_S1, O_d.alpha_S1, -1 + O_d.alpha_S1};
    O_d.Sser1_3 = {-O_d.alpha_S1, -O_d.alpha_S1, 1 - O_d.alpha_S1};

    // S2

    O_d.alpha_S2 = 2 * O_d.Z9 / (O_d.Z7 + O_d.Z8 + O_d.Z9);

    O_d.Sser2_2 = {-1 + O_d.alpha_S2, O_d.alpha_S2, -1 + O_d.alpha_S2};
    O_d.Sser2_3 = {-O_d.alpha_S2, -O_d.alpha_S2, 1 - O_d.alpha_S2};

    // S3

    O_d.alpha_S3 = 2 * O_d.Z12 / (O_d.Z10 + O_d.Z11 + O_d.Z12);

    O_d.Sser3_2 =  {-1 + O_d.alpha_S3, O_d.alpha_S3, -1 + O_d.alpha_S3};
    O_d.Sser3_3 = {-O_d.alpha_S3, -O_d.alpha_S3, 1 - O_d.alpha_S3};

    // P1 (R_neg||R28)

    O_d.alpha_P1 = 2 * 1 / O_d.Z6 / (1 / O_d.Z4 + 1 / O_d.Z5 + 1 / O_d.Z6);

    O_d.Spar1_1 =  {0, 1 - O_d.alpha_P1, O_d.alpha_P1};
    O_d.Spar1_2 =  {1, -O_d.alpha_P1, O_d.alpha_P1};
    O_d.Spar1_3 =  {1, 1 - O_d.alpha_P1, O_d.alpha_P1 - 1};
}
