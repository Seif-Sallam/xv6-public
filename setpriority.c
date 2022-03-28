#include "types.h"
#include "user.h"
#include "stat.h"

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf(1, "The number of arguments is not correct\nexpected arguments: ./setpriority <pid> <priority>\n");
        exit();
    }
    setPriority(atoi(argv[1]), atoi(argv[2]));

    exit();
}