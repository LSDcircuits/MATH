#include <stdio.h>
#include <math.h>

#define M_pi 3.14

double toradians(double degrees) {
    return degrees * (M_pi / 180.0);
}
// pitch is yangle7y
// roll is xangle
// yaw is z angle 
void angletovector(double roll, double pitch, double yaw,  double* id, double* jr, double* ip){
    *id = atan((sin(toradians(yaw)))/(cos(toradians(pitch))*cos(toradians(yaw))));
    *ip = atan(sin(toradians(pitch))/(cos(toradians(pitch))*cos(toradians(yaw))));
    *jr = atan(sin(toradians(roll))/(cos(toradians(roll))*cos(toradians(yaw))));
}

int main()
{

    double roll, pitch, yaw; // Angles in degrees
    double id, ip, jr;
    
    printf("Enter roll (x-axis rotation) in degrees: ");
    scanf("%lf", &roll);
    printf("Enter pitch (y-axis rotation) in degrees: ");
    scanf("%lf", &pitch);
    printf("Enter yaw (z-axis rotation) in degrees: ");
    scanf("%lf", &yaw);
    printf("Hello, World !");
   
    angletovector(roll, pitch, yaw, &id, &ip, &jr);
   
    printf("angle to vecotr:\n");
    printf("roll angle: %f\n", jr);
    printf("pitch angle: %f\n", ip);
    printf("yaw angle: %f\n", id);
    return 0;
}
