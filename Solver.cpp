/*
  ==============================================================================

    LWSolver.cpp
    Created: 28 Apr 2022 10:47:17am
    Author:  Riccardo Giampiccolo

  ==============================================================================
*/

#include "Solver.h"

float Solver::log2f_approx(float x) {
    union {
        int    i;
        float    f;
    } v;
    v.f = x;
    int ex = v.i & 0x7f800000;
    int e = (ex >> 23) - 127;
    v.i = (v.i - ex) | 0x3f800000;
    return (float)e - 2.213475204444817f + v.f * (3.148297929334117f + v.f * (-1.098865286222744f + v.f * 0.1640425613334452f));
}

float Solver::logf_approx(float x) {
    return 0.693147180559945f * log2f_approx(x);
}

float Solver::pow2f_approx(float x) {
    if (x < -126.f)
        return 0.f;
    union {
        int    i;
        float    f;
    } v;
    int xi = (int)x;
    int l = x < 0.0f ? xi - 1 : xi;
    float f = x - (float)l;
    v.i = (l + 127) << 23;
    return v.f * (1.0f + f * (0.6931471805599453f + f * (0.2274112777602189f + f * 0.07944154167983575f)));
}

float Solver::expf_approx(float x) {
    return pow2f_approx(1.442695040888963f * x);
}

float Solver::omega3(float x) {
    const float x1 = -3.341459552768620f;
    const float x2 = 8.f;
    const float a = -1.314293149877800e-3f;
    const float b = 4.775931364975583e-2f;
    const float c = 3.631952663804445e-1f;
    const float d = 6.313183464296682e-1f;
    return x < x1 ? 0.f : (x < x2 ? d + x * (c + x * (b + x * a)) : x - Solver::logf_approx(x));
}

float Solver::omega4(float x) {
    const float y = Solver::omega3(x);
    return y - (y - Solver::expf_approx(x - y)) / (y + 1.f);
}

