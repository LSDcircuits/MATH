#include <stdio.h>
#include <math.h>

// Function to convert degrees to radians
double toRadians(double degrees) {
    return degrees * (M_PI / 180.0);
}

// Function to calculate quaternion from given angles
void anglesToQuaternion(double roll, double pitch, double yaw, double* qw, double* qx, double* qy, double* qz) {
    double cy = cos(toRadians(yaw) * 0.5);
    double sy = sin(toRadians(yaw) * 0.5);
    double cp = cos(toRadians(pitch) * 0.5);
    double sp = sin(toRadians(pitch) * 0.5);
    double cr = cos(toRadians(roll) * 0.5);
    double sr = sin(toRadians(roll) * 0.5);

    *qw = cr * cp * cy + sr * sp * sy;
    *qx = sr * cp * cy - cr * sp * sy;
    *qy = cr * sp * cy + sr * cp * sy;
    *qz = cr * cp * sy - sr * sp * cy;
}

int main() {
    double roll, pitch, yaw; // Angles in degrees
    double qw, qx, qy, qz; // Quaternion components

    // Input angles in degrees
    printf("Enter roll (x-axis rotation) in degrees: ");
    scanf("%lf", &roll);
    printf("Enter pitch (y-axis rotation) in degrees: ");
    scanf("%lf", &pitch);
    printf("Enter yaw (z-axis rotation) in degrees: ");
    scanf("%lf", &yaw);

    // Convert given angles to quaternion
    anglesToQuaternion(roll, pitch, yaw, &qw, &qx, &qy, &qz);

    // Output the quaternion
    printf("Quaternion Orientation:\n");
    printf("qw: %f\n", qw);
    printf("qx: %f\n", qx);
    printf("qy: %f\n", qy);
    printf("qz: %f\n", qz);

    return 0;
}