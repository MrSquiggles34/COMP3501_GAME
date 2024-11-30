#ifndef DEFS_H
#define DEFS_H

#include <random>
#include <godot_cpp/variant/packed_float32_array.hpp>
#include <godot_cpp/core/memory.hpp> 
#include <godot_cpp/variant/utility_functions.hpp> 

// easily toggle off the debug messages in the entire library
#define DEBUG true

// Define some numbers to check game state
#define PLAY 0
#define INV 1
#define JOURNAL 2

#define NOISE_WIDTH 1080
#define NOISE_HEIGHT 1080

// Stuff for generating custom meshes.
namespace godot {
    // page 328
    static float** generateNoise();
    static PackedFloat32Array* fillDataArray(float** noise);
    static float smoothNoise(float** noise, float zoom, float x1, float y1);
    static float turbulence(float** noise, float x, float y, float maxZoom);

    // page 329
    static float** generateNoise() {
        float** noise;
        noise = new float* [NOISE_WIDTH];
        for (int x = 0; x < NOISE_WIDTH; x++) {
            noise[x] = new float[NOISE_HEIGHT];
            for (int y = 0; y < NOISE_HEIGHT; y++) {
                noise[x][y] = (float)rand() / (RAND_MAX + 1.0f); // computes a float in [0, 1]
            }
        }
        return noise;
    }

    // page 330
    static PackedFloat32Array* fillDataArray(float** noise) {
        PackedFloat32Array* float_array = memnew(PackedFloat32Array);

        // page 333
        float maxZoom = 64.0f;
        for (int i = 0; i < NOISE_WIDTH; i++) {
            for (int j = 0; j < NOISE_HEIGHT; j++) {
                float_array->append(turbulence(noise, maxZoom, i, j)); // R
                float_array->append(turbulence(noise, maxZoom, i, j)); // G
                float_array->append(turbulence(noise, maxZoom, i, j)); // B
                float_array->append(1.0f); // A
            }
        }

        return float_array;
    }

    // page 331
    static float smoothNoise(float** noise, float zoom, float x1, float y1) {
        // fraction of x1, y1
        float fractX = x1 - (int)x1;
        float fractY = y1 - (int)y1;

        // indices for neighbouring values with wrapping at the ends
        float x2 = x1 - 1; if (x2 < 0) x2 = round(NOISE_WIDTH / zoom) - 1.0f;
        float y2 = y1 - 1; if (y2 < 0) y2 = round(NOISE_HEIGHT / zoom) - 1.0f;

        // smooth the noise by interpolating greyscale intensity along axes
        float value = 0.0;
        value += fractX * fractY * noise[(int)x1][(int)y1];
        value += (1 - fractX) * fractY * noise[(int)x2][(int)y1];
        value += fractX * (1 - fractY) * noise[(int)x1][(int)y2];
        value += (1 - fractX) * (1 - fractY) * noise[(int)x2][(int)y2];

        return value;
    }

    // page 332
    static float turbulence(float** noise, float maxZoom, float x, float y) {
        float sum = 0.0f, zoom = maxZoom;
        while (zoom >= 1.0f) {
            // compute weighted sum of smoothed noise maps
            sum = sum + smoothNoise(noise, zoom, x / zoom, y / zoom) * zoom;
            zoom = zoom / 2.0f; // for each zoom factor that is a power of two
        }
        sum = 0.5 * sum / maxZoom;
        return sum;
    }

    //page 335
    static PackedFloat32Array* fillDataArrayMarble(float** noise) {
        PackedFloat32Array* float_array = memnew(PackedFloat32Array);

        float vein_frequency = 2.0f;
        float turb_power = 1.5f;
        float max_zoom = 64.0f;

        for (int i = 0; i < NOISE_WIDTH; i++) {
            for (int j = 0; j < NOISE_HEIGHT; j++) {
                float xy_value = float(i) / NOISE_WIDTH + float(j) / NOISE_HEIGHT + turb_power * turbulence(noise, max_zoom, i, j);
                float sine_value = abs(sin(xy_value * 3.14159 * vein_frequency));

                float red_portion = sine_value;
                float green_portion = sine_value;
                float blue_portion = sine_value;

                float_array->append(red_portion);
                float_array->append(green_portion);
                float_array->append(blue_portion);
                float_array->append(1.0f);
            }
        }

        return float_array;
    }

    // page 343
    static PackedFloat32Array* fillDataArrayMistyClouds(float** noise) {
        PackedFloat32Array* float_array = memnew(PackedFloat32Array);

        float max_zoom = 16.0f;

        for (int i = 0; i < NOISE_WIDTH; i++) {
            for (int j = 0; j < NOISE_HEIGHT; j++) {
                float brightness = 1.0f - (float)turbulence(noise, max_zoom, i, j);

                float red_portion = brightness;
                float green_portion = brightness;
                float blue_portion = 1.0f;

                float_array->append(red_portion);
                float_array->append(green_portion);
                float_array->append(blue_portion);
                float_array->append(1.0f);
            }
        }

        return float_array;
    }

    // page 344
    static float logistic(float in) {
        float k = 0.5f;
        return (1.0f / (1.0f + pow(2.718, -k * in)));
    }
    // page 343
    static float turbulenceClouds(float** noise, float maxZoom, float x, float y) {
        float sum = 0.0f, zoom = maxZoom, cloudQuant;
        while (zoom >= 0.9f) {
            // compute weighted sum of smoothed noise maps
            sum = sum + smoothNoise(noise, zoom, x / zoom, y / zoom) * zoom;
            zoom = zoom / 2.0f; // for each zoom factor that is a power of two
        }
        sum = sum / maxZoom;
        cloudQuant = 0.3f;    // tunable quality of clouds
        sum = logistic(sum - cloudQuant);
        return sum;
    }

    static PackedFloat32Array* fillDataArrayClouds(float** noise) {
        PackedFloat32Array* float_array = memnew(PackedFloat32Array);

        float max_zoom = 16.0f;

        for (int i = 0; i < NOISE_WIDTH; i++) {
            for (int j = 0; j < NOISE_HEIGHT; j++) {
                float brightness = 1.0f - (float)turbulenceClouds(noise, max_zoom, i, j);

                float red_portion = brightness;
                float green_portion = brightness;
                float blue_portion = 1.0f;

                float_array->append(red_portion);
                float_array->append(green_portion);
                float_array->append(blue_portion);
                float_array->append(1.0f);
            }
        }

        return float_array;
    }

    // page 350 14.5
    static float turbulenceMarble(float** noise, float maxZoom, float x, float y) {
        float sum = 0.0f, zoom = maxZoom;
        while (zoom >= 1.0f) {
            // compute weighted sum of smoothed noise maps
            sum = sum + smoothNoise(noise, zoom, x / zoom, y / zoom) * zoom;
            zoom = zoom / 2.0f; // for each zoom factor that is a power of two
        }
        sum = 0.5 * sum / maxZoom;
        sum = logistic(sum - 0.45f);
        return sum;
    }

}

#endif // DEFS_H