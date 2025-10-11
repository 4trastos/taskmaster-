#include "taskmaster.h"
#include "ft_printf.h"

int main(int argc, char **argv, char **envp)
{
    if (argc != 2)
    {
        ft_printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);

    }

    // 1. Parser de configuración YAML
    // 2. Estructuras de datos básicas
    // 3. Lanzamiento simple de procesos
    // 4. Shell interactiva básica

    // 5. Manejo de señales (SIGCHLD)
    // 6. Detección de estado de procesos
    // 7. Políticas de reinicio básicas
    // 8. Sistema de logging    (es la memoria del daemon)

    // 9. Múltiples instancias (numprocs)
    // 10. Recarga con SIGHUP
    // 11. Timeouts y reintentos
    // 12. Redirección de E/S robusta

    // 13. Manejo de edge cases
    // 14. Pruebas exhaustivas

    return (0);
}