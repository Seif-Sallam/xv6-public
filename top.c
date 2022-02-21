#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char const *argv[])
{
    int refreshes = 0;
    int maxRef = 10;
    if (argc > 2)
        maxRef = atoi(argv[1]);
    while (1)
    {
        top();
        sleep(100);
        refreshes++;
        if (refreshes >= maxRef)
            break;
    }
    exit();
}