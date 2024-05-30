#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <picodrv.h>

#define BUFFER_SIZE 1024 // Define buffer size
#define PWM_PERIOD 20000 // Define PWM period in microseconds
#define PWM_RANGE 1000 // Define PWM range in microseconds
#define KP 1.0 // Define proportional gain
#define KI 0.5 // Define integral gain
#define KD 0.2 // Define derivative gain

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

    // Initialize PWM and servo
    gpioSetFunction(18, GPIO_FUNC_PWM);
    gpioPWMSetMode(0);
    gpioPWMSetRange(PWM_RANGE);
    gpioPWMSetClock(2);
    gpioPWM(18, 0);

    // Initialize PID parameters
    float error = 0.0, prev_error = 0.0, integral = 0.0, derivative = 0.0;
    
    while (1) {
        
        // Read accelerometer data
        float x_acc = 0.0, y_acc = 0.0, z_acc = 0.0;
        result = PicoDrv_ADC_Capture(0, &x_acc, 1);
        if (result != PICO_OK) {
            printf("PicoDrv_ADC_Capture failed with error %d", result);
            return -1;
        }
        result = PicoDrv_ADC_Capture(1, &y_acc, 1);
        if (result != PICO_OK) {
            printf("PicoDrv_ADC_Capture failed with error %d", result);
            return -1;
        }
        result = PicoDrv_ADC_Capture(2, &z_acc, 1);
        if (result != PICO_OK) {
            printf("PicoDrv_ADC_Capture failed with error %d", result);
            return -1;
        }

        // Compute pitch angle from accelerometer data
        float pitch = atan2(x_acc, sqrt(y_acc*y_acc + z_acc*z_acc)) * 180.0/M_PI;
        
        // Compute error and update PID parameters
        error = pitch;
        integral += error;
        derivative = error - prev_error;
        float pwm_value = KP*error + KI*integral + KD*derivative;
        prev_error = error;
        
        // Convert PWM value to servo angle and output to servo
        int servo_angle = (int) round(pwm_value * 90.0/PWM_RANGE);
        int pwm_duty_cycle = (int) round(PWM_RANGE * servo_angle / 180.0);
        gpioPWM(18, pwm_duty_cycle);
        
        // Wait for next loop iteration
        usleep(10000); // Wait for 10 milliseconds
    }

    // Cleanup Pico driver
    PicoDrv_Deinit();
    
    return 0;
}