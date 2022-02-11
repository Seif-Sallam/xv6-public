#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
//#include <string.h>

int main(int argc, char * argv[]) {
    
    int elements[argc], temp;
    //char *arr[]= {"3", "6", "8", "2", "4"};
    for (int i = 1; i < argc; ++i)
    {
        //int t;
        //sscanf(argv[i], "%d", &elements[i]);
        elements[i]=atoi(argv[i]);
    }
    
    for(int i=2; i<argc; i++)
    {
        temp= elements[i];
        int j= i-1;
        
        while(j>=0 && elements[j]>temp)
        {
            elements[j+1]= elements[j];
            j= j-1;
        }
        
        elements[j+1]= temp;
    }
    
    for(int i=1; i<argc; i++)
    {
        printf(1, "%d ", elements[i]);
    }
    printf(1, "\n");
    
    exit();
}


