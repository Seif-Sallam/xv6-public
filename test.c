#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char const *argv[])
{
    int value = 3;
start:
    value--;
    int oldPriority = getPriority(getpid());
    printf(1, "oldPriority from getPriority: %d\n", oldPriority);
    int newP = 200 + value * 100;
    int captured = setPriority(getpid(), newP);
    printf(1, "Captured Priority: %d\n", captured);

    int newPriority = getPriority(getpid());
    printf(1, "new Priority: %d\n", newPriority);
    printf(1, "\n\n");
    ps();
    printf(1, "\n\n");
    sleep(300);
    if (value > 0)
        goto start;

    exit();
}