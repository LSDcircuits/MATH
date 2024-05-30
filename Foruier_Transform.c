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
    
    // Perform Fourier transform on buffer using FFT algorithm
    float real[BUFFER_SIZE], imag[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
        real[i] = buffer[i];
        imag[i] = 0.0;
    }
    int log2n = log2(BUFFER_SIZE);
    result = PicoDrv_DSP_FFT(real, imag, log2n, PICO_DSP_FORWARD_FFT);
    if (result != PICO_OK) {
        printf("PicoDrv_DSP_FFT failed with error %d", result);
        return -1;
    }
    
    // Print frequency and amplitude of each component
    for (int i = 0; i < BUFFER_SIZE/2; i++) {
        float freq = i * (1.0/BUFFER_SIZE);
        float amp = sqrt(real[i]*real[i] + imag[i]*imag[i]) / BUFFER_SIZE;
        printf("Frequency: %f Hz, Amplitude: %f\n", freq, amp);
    }
    
    // Cleanup Pico driver
    PicoDrv_Deinit();
    
    return 0;
}