#include <stdio.h>
#define matrix_size 3 //n x n matrix
//     | a11  a12  a13 |               
//     |               |
//     | a21  a22  a23 |
//     |               |
//     | a31  a32  a33 |
// Function to input values into the matrix

void input_matrix(int row_column[matrix_size][matrix_size]){
    for (int i = 0; i < matrix_size; i++){
        for (int j = 0; j < matrix_size; j++){
            printf("Enter an integer for row %d, column %d: ", i+1, j+1);
            scanf("%d", &row_column[i][j]);
        }
    }
}

//     (ajdugate of row_column) -->>
//     | b11  b12  b13 |  1  -1   1 |             
//     |               |            |
//     | b21  b22  b23 | -1   1  -1 |  
//     |               |            |
//     | b31  b32  b33 |  1  -1   1 |

void determinant(float inverse[matrix_size][matrix_size], float *det_A){
    int row_column[matrix_size][matrix_size];
    //initialize input matrix
    input_matrix(row_column);
    int a11 = row_column[0][0];
    int a12 = row_column[0][1];
    int a13 = row_column[0][2];
    int a21 = row_column[1][0];
    int a22 = row_column[1][1];
    int a23 = row_column[1][2];
    int a31 = row_column[2][0];
    int a32 = row_column[2][1];
    int a33 = row_column[2][2];
    // Note the negative sign, as cofactors alternate signs
    float b11 =    (a22 * a33) - (a23 * a32); 
    float b12 = -( (a21 * a33) - (a23 * a31) );
    float b13 =    (a21 * a32) - (a22 * a31);

    float b21 = -( (a12 * a33) - (a13 * a32) ); 
    float b22 =    (a11 * a33) - (a13 * a31);
    float b23 = -( (a11 * a32) - (a12 * a31) );

    float b31 =    (a12 * a23) - (a13 * a22);
    float b32 = -( (a11 * a23) - (a13 * a21) );
    float b33 =    (a11 * a22) - (a12 * a21);
    // get the determinant
    *det_A = (b11 * a11) - (a12 * b12) + (a13 * b13);
    if (det_A != 0){
        //define new matrix 
        inverse[0][0] = b11 / *det_A;
        inverse[0][1] = b12 / *det_A;
        inverse[0][2] = b13 / *det_A;
        inverse[1][0] = b21 / *det_A;
        inverse[1][1] = b22 / *det_A;
        inverse[1][2] = b23 / *det_A;
        inverse[2][0] = b31 / *det_A;
        inverse[2][1] = b32 / *det_A;
        inverse[2][2] = b33 / *det_A;
    }

}
int main() {
    float inverse[matrix_size][matrix_size];
    float detA; // Declare detA here
    determinant(inverse, &detA); // Pass address of detA

    printf("Inverse Matrix:\n");
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf("%f ", inverse[i][j]);
        }
        printf("\n");
    }
    printf("Determinant: %f\n", detA); // Correct format specifier

    return 0;
}