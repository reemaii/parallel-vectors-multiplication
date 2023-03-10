
   #include <stdio.h>
   #include <stdlib.h>
   #include <mpi.h>
   
   #define max_rows 100000 
   #define send_data_tag 1
   
   int multi(int arr1[],int arr2[],int n){
   int sum=0;
   
   for(int i = 0; i < n; i++) {
   
         sum = sum+arr1[i]*arr2[i];}
         
         return sum;}
   

   int array1[max_rows];
   int buffer1[max_rows];
   int array2[max_rows];
   int buffer2[max_rows];
  int main(int argc, char **argv) 
   {
      int partial_dot,dot;
      int my_id, root_process, i, num_rows, num_procs, avg_rows_per_process;
       double start, end,total ;

      //begining of MPI Code.

      MPI_Init(&argc, &argv);
      
      root_process = 0;
      
      /* find out MY process ID, and how many processes were started. */
      
      MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
      MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
      
      //scatterv arguments 
      int sendcounts[num_procs], displs[num_procs];

      if(my_id == root_process) {
         
         /* I must be the root process, so I will query the user
          * to determine the size of the array */

         printf("please enter the array size: ");
         scanf("%i", &num_rows);
      
         if(num_rows > max_rows) {
            printf("Too many numbers.\n");
            exit(1);
         }

         avg_rows_per_process = num_rows / num_procs;

         /* initialize an array */

         for(i = 0; i < num_rows; i++) {
            array1[i] = rand()%10;
            array2[i]=rand()%10;
         }
         
         //print two vectors
         
          /* printf("\nVector1 = [");
    for (int i = 0; i < num_rows; i++) {
        printf("%d,", array[i]);
    }
    printf("]");
    printf("\nVector2 = [");
    for (int i = 0; i < num_rows; i++) {
        printf("%d,", array3[i]);
    }
    printf("]\n");*/
    
         
         /*create the sendcounts and displs for scatterv */
         
         for(i = 0; i < num_procs; i++) {
         	sendcounts[i]= avg_rows_per_process;}
         
         if(num_rows - (avg_rows_per_process * num_procs)!=0){
         int remaining = num_rows - (avg_rows_per_process * num_procs);
         
         	for(i = 0; remaining > 0 ; i++) {
         		sendcounts[i]+=1;
         		remaining-=1;
         		if(i == num_procs)
         			i=0; 
         	}
         
         }
         
         displs[0]=0;
         for(i = 1; i < num_procs; i++) {
         	displs[i]= displs[i-1]+sendcounts[i-1];
         }
         
       }//end if
       
	 start = MPI_Wtime();
  MPI_Scatterv(&array1, sendcounts, displs, MPI_INT, buffer1, max_rows, MPI_INT,root_process, MPI_COMM_WORLD);
  
   MPI_Scatterv(&array2, sendcounts, displs, MPI_INT, buffer2, max_rows, MPI_INT,root_process, MPI_COMM_WORLD);
   	
          
  partial_dot = multi(buffer1, buffer2, max_rows);
  
  MPI_Reduce(&partial_dot, &dot, 1, MPI_INT,MPI_SUM, 0, MPI_COMM_WORLD);
         
			
	if(my_id == 0) {
		end = MPI_Wtime();
		total = end - start;		
	       printf("\nTotal time : %f", total);
    
    printf("\nThe result of multiplying the two vectors = %d\n", dot);}
			   
	
			
      MPI_Finalize();
      
   }
