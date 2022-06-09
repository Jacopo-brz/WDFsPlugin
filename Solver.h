/*
  ==============================================================================

    LWSolver.h
    Created: 28 Apr 2022 10:47:17am
    Author:  Riccardo Giampiccolo

  ==============================================================================
*/

#pragma once
class Solver {

public:

    static float omega3(float x);
    static float omega4(float x);
    static float logf_approx(float x);

private:

    Solver() {};
    static float log2f_approx(float x);
    static float pow2f_approx(float x);
    static float expf_approx(float x);


};
