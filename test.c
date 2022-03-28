#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char const *argv[])
{
    /*
         Layout of the program:
         - A parent creating a child that calls ps every 100ms.
         - The parent creates a child that creates multiple children that do work endlessly
         - The parent monitors the work for 10000ms (10 seconds)
         - After the time is up, the parent kills the children
         with utter temptation to use exec instead of forking and checking
     */

    // Parnet
    int duration = 10000;
    if (argc < 2)
    {
        printf(1, "Invalid number of arguments\n"
                  "Expected arguments: test <schedular type> [<test duration>] [<Number of Children>]\n"
                  "Scheduler types:\n"
                  "1 -> Priority without decay\n"
                  "2 -> Priority with decay\n"
                  "Any other value -> FCFS\n");
        exit();
    }
    if (argc >= 3)
        duration = atoi(argv[2]);
    int numOfChildren = 7;
    if (argc >= 4)
        numOfChildren = atoi(argv[3]);
    setSchedType(atoi(argv[1]));
    const int prs[] = {1000, 2000, 2500, 3500, 4000, 4500, 5000, 5500, 6000};
    int childrenPIDs[numOfChildren];
    char name[16] = "<Parent>";
    setName(name);
    setPriority(getpid(), 1000);
    childrenPIDs[0] = fork();
    if (childrenPIDs[0] == 0)
    {
        char name[16] = "<top>";
        setName(name);
        setPriority(getpid(), 500);
        while (1)
        {
            top();
        }
    }
    else
    {
        char name[16] = "<Work>";
        int index;
        for (index = 1; index < numOfChildren; index++)
        {
            childrenPIDs[index] = fork();
            if (childrenPIDs[index] == 0)
            {
                setName(name);
                if (index < sizeof(prs) / sizeof(int))
                    setPriority(getpid(), prs[index]);
                else
                    setPriority(getpid(), 5000);
                break;
            }
        }
        if (index != numOfChildren)
        {
            // I am a Work child
            while (1)
            {
                // just do some work
                unsigned long long sum = 0;
                for (int i = 0; i < 10000000; i++)
                {
                    sum += i;
                }
            }
        }
        else // I am the parent
        {
            sleep(duration);
            for (int i = 1; i < numOfChildren; i++)
            {
                printf(1, "killing process %d\n", childrenPIDs[i]);
                kill(childrenPIDs[i]);
            }
            printf(1, "killing top: %d\n", childrenPIDs[0]);
            kill(childrenPIDs[0]);
        }
    }
    exit();
}