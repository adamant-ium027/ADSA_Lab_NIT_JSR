// Create a two dimensional array with all elements 0. Take the user input roll_no., col_no., and the value and print the array.

#include <stdio.h>

#define COL 3

int main(void){
    
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    printf("\n\n");

    int arr[n][COL];

    for(int i=0; i<n; i++){
        for(int j=0; j<COL; j++) arr[i][j] = 0;
    }

    for(int i=0; i<n; i++){
        printf("Enter details of student %d: ", i+1);
        scanf("%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
    }

    printf("\nUser details are:\n");

    printf("ROLL_NO.   COL_NO.    VALUE\n");
    for(int i=0; i<n; i++){
        printf("%-10d %-10d %-10d", arr[i][0], arr[i][1], arr[i][2]);
        printf("\n");
    }

    return 0;
}