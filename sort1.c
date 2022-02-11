#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
  
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
  
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf(1,"%d ", arr[i]);
    printf(1,"\n");
}
  
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "The number of arguments is not sufficient enough\n"
                  "The format shoule be like this: sort1 <list of items you want to bubble sort>\n");
        exit();
    }
    int array[argc];
    for(int i=1; i<argc; i++)
    {
        array[i-1]=atoi(argv[i]);
    }
    bubbleSort(array, argc-1);
    printf(1,"Sorted array: \n");
    printArray(array, argc-1);
    exit();
}
