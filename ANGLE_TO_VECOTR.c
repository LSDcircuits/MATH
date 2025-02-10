#include <stdio.h>
#include <math.h>

#define M_pi 3.14

double toradians(double degrees) {
    return degrees * (M_pi / 180.0);
}

void angletovector( double roll, double pitch, double yaw,  double* ix, double* iy, double* iz, double* jx, double* jy, double* jz ) {
    *ix = cos(toradians(pitch))*cos(toradians(yaw));
    *iy = sin(toradians(yaw));
    *iz = sin(toradians(pitch));
    *jx = sin(toradians(yaw));
    *jy = cos(toradians(roll)*cos(toradians(yaw)));
    *jz = sin(toradians(roll));
}


int main()
{

    double roll, pitch, yaw; // Angles in degrees
    double ix, iy, iz, jx, jy, jz;
    
    printf("Enter roll (x-axis rotation) in degrees: ");
    scanf("%lf", &roll);
    printf("Enter pitch (y-axis rotation) in degrees: ");
    scanf("%lf", &pitch);
    printf("Enter yaw (z-axis rotation) in degrees: ");
    scanf("%lf", &yaw);
   printf("Hello, World !");
   
   angletovector(roll, pitch, yaw, &ix, &iy, &iz, &jx, &jy, &jz );
   
    printf("angle to vecotr:\n");
    printf("ix: %f\n", ix);
    printf("iy: %f\n", iy);
    printf("iz: %f\n", iz);
   return 0;
}
