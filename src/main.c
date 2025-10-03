#include "../incl/taskmaster.h"
#include "../lib/printf/ft_printf.h"

int main(int argc, char **argv, char **envp)
{
    if (argc != 2)
    {
        ft_printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);
    }
    return (0);
}