#include "taskmaster.h"
#include "ft_printf.h"

// 5. test_davgalle.c (Termina normalmente)

int main(void)
{
    ft_printf("✅ PROGRAMA NORMAL - Iniciando...\n");
    fflush(stdout);
    sleep(1);
    ft_printf("✅ PROGRAMA NORMAL - Terminando con código 0\n");

    return (0);     // Terminación normal
}