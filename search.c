#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(1, "The number of arguments is not sufficient enough\n"
                  "The format shoule be like this: search <search item> <list of items searching for seperated by spaces>\n");
        exit();
    }

    const char *searchableItem = argv[1];
    for (int i = 2; i < argc; i++)
    {
        if (strcmp(searchableItem, argv[i]) == 0)
        {
            printf(1, "Found! at index %d\n", i - 2);
            exit();
        }
    }
    printf(1, "Not Found!\n");
    exit();
}