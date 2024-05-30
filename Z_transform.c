#include <stdio.h>
#include <math.h>
#include <picodrv.h>

#define BUFFER_SIZE 1024 // Define buffer size

int main() {

    // Initialize Pico driver and ADC
    int result = PicoDrv_Init();
    if (result != PICO_OK) {
        printf("PicoDrv_Init failed with error %d", result);
        return -1;
    }
    result = PicoDrv_ADC_Setup(0, PICO_ADC_RANGE_5V, PICO_ADC_SAMPLING_RATE_1MS);
    if (result != PICO_OK) {
        printf("PicoDrv_ADC_Setup failed with error %d", result);
        return -1;
    }
    
    // Create buffer for storing ADC samples
    float buffer[BUFFER_SIZE];
    
    // Read ADC samples into buffer
    result = PicoDrv_ADC_Capture(0, buffer, BUFFER_SIZE);
    if (result != PICO_OK) {
        printf("PicoDrv_ADC_Capture failed with error %d", result);
        return -1;
    }
    
    // Perform Z-transform on buffer using direct method
    float real[BUFFER_SIZE], imag[BUFFER_SIZE];
    for (int k = 0; k < BUFFER_SIZE; k++) {
        real[k] = 0.0;
        imag[k] = 0.0;
        for (int n = 0; n < BUFFER_SIZE; n++) {
            real[k] += buffer[n] * cos(2*M_PI*k*n/BUFFER_SIZE);
            imag[k] -= buffer[n] * sin(2*M_PI*k*n/BUFFER_SIZE);
        }
    }
    
    // Print frequency and amplitude of each component
    for (int k = 0; k < BUFFER_SIZE; k++) {
        float freq = (2*M_PI*k) / BUFFER_SIZE;
        float mag = sqrt(real[k]*real[k] + imag[k]*imag[k]);
        printf("Frequency: %f rad/s, Magnitude: %f\n", freq, mag);
    }
    
    // Cleanup Pico driver
    PicoDrv_Deinit();
    
    return 0;
}