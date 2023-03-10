#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
void multi(int arr1[], int arr2[], int n) {
    double start,end;
    double total;
    int result = 0;
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:result) num_threads(4)
    for (int i = 0; i < n; i++) {
	result = result + (arr1[i] * arr2[i]);}
		 end = omp_get_wtime();
		
    total = (end - start) ;
    printf("\nTotal time : %f", total);
    printf("\nThe result of multiplying the two vectors = %d\n", result);
}

int main(){
  int n;
  printf("Enter the size of array: ");
    scanf("%d", &n);
    int array1[n];
    int array2[n];
    for (int i = 0; i < n; i++) {
        array1[i] = rand()%10;
        array2[i] = rand()%10;}
        
     printf("\nVector1 = [");
    for (int i = 0; i < n; i++) {
        printf("%d,", array1[i]);
    }
    printf("]\n");
    printf("\nVector2 = [");
    for (int i = 0; i < n; i++) {
        printf("%d,", array2[i]);
    }
    printf("]\n");  
    multi(array1, array2, n);  
        
   return 0;
}


