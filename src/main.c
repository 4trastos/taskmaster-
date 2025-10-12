#include "taskmaster.h"
#include "ft_printf.h"

int main(int argc, char **argv, char **envp)
{
    int                 numb_prog;
    t_program_config    *config;

    if (argc != 2)
    {
        ft_printf("❌ Use: %s must have PROG [ARGS] ❌\n", argv[0]);
        return (1);

    }
    
    numb_prog = get_number_of_program(argv[1]);
    config = malloc(sizeof(t_program_config));
    if (!config)
        return (1);

    // 3. INICIALIZACIÓN DE SEÑALES (SIGINT, SIGQUIT, SIGCHLD)
    init_signal();
    
    // 4. PREPARACIÓN DE PROCESOS
    init_process_test(&config, envp);

    // 5. AUTOSTART DE PROCESOS (Lanzamiento inicial de los que lo requieran)
    start_autostart_programs(config);

    // 6. BUCLÉ MAESTRO (MONITOREO NO BLOQUEANTE Y CLI INTERACTIVA)
    taskmaster_main_loop(config);

    // 7. LIMPIEZA Y SALIDA
    ft_printf("Taskmaster se ha cerrado limpiamente.\n");

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

    free (config);
    return (0);
}