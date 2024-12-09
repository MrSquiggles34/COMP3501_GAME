// noise.h
#ifndef NOISE_H
#define NOISE_H
#include <math.h>

class OpenSimplexNoise {
public:
    OpenSimplexNoise(int seed = 0) {
        this->seed = seed;
    }

    float get_noise_2d(float x, float y) {
        return generate_noise(x, y);
    }

private:
    int seed;
    float frequency = 16;
    float amplitude = 0.15;

    float generate_noise(float x, float y) {

        x *= frequency;
        y *= frequency;

        float n = (sin(x + seed) + cos(y + seed)) * 0.5f;

        n *= amplitude;

        return n;
    }
};

#endif