#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char const *argv[])
{
    //     int value = 3;
    // start:
    //     value--;
    //     int oldPriority = getPriority(getpid());
    //     printf(1, "oldPriority from getPriority: %d\n", oldPriority);
    //     int newP = 200 + value * 100;
    //     int captured = setPriority(getpid(), newP);
    //     printf(1, "Captured Priority: %d\n", captured);

    //     int newPriority = getPriority(getpid());
    //     printf(1, "new Priority: %d\n", newPriority);
    //     printf(1, "\n\n");
    //     ps();
    //     printf(1, "\n\n");
    //     sleep(300);
    //     if (value > 0)
    //         goto start;

    /*
        Layout of the program:
        - A parent creating a child that calls ps every 100ms.
        - The parent creates a child that creates multiple children that do work endlessly
        - The parent monitors the work for 10000ms (10 seconds)
        - After the time is up, the parent kills the children
        with utter temptation to use exec instead of forking and checking
    */

    // Parnet
    // int parentPID = getpid();
    int duration = 10000;
    if (argc < 2)
    {
        printf(1, "Invalid number of arguments\nExpected arguments: test <schedular type> [<test duration>] [<Number of Children>]\nScheduler types:\n1 -> Priority without decay\n2 -> Priority with decay\nAny other value -> FCFS\n");
        exit();
    }
    if (argc >= 3)
        duration = atoi(argv[2]);
    int numOfChildren = 7;
    if (argc >= 4)
        numOfChildren = atoi(argv[3]);
    setSchedType(atoi(argv[1]));
    const int prs[7] = {1000, 2000, 2500, 3500, 4000, 4500, 5000};
    int childrenPIDs[numOfChildren];
    char name[16] = "parent";
    setName(name);
    setPriority(getpid(), 1000);
    childrenPIDs[0] = fork();
    if (childrenPIDs[0] == 0)
    {
        char name[16] = "ps Child";
        setName(name);
        setPriority(getpid(), 500);
        // I am the first child that calls ps everey 100 ms
        while (1)
        {
            ps();
            sleep(100);
        }
    }
    else
    {
        char name[16] = "work Child";

        for (int i = 1; i < numOfChildren; i++)
        {
            childrenPIDs[i] = fork();
            if (childrenPIDs[i] == 0)
            {
                if (i < 7)
                {
                    setPriority(getpid(), prs[i]);
                }
                else
                {
                    setPriority(getpid(), 5500);
                }
                setName(name);
                goto child;
            }
        }
        goto parent;
    child:
        while (1)
        {
            // just do some work
            unsigned long long sum = 0;
            for (int i = 0; i < 10000000; i++)
            {
                sum += i;
            }
        }
    parent:
        sleep(duration);
        for (int i = 1; i < numOfChildren; i++)
        {
            printf(1, "killing process %d\n", childrenPIDs[i]);
            kill(childrenPIDs[i]);
        }
        kill(childrenPIDs[0]);
    }
    exit();
}