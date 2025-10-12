#include "taskmaster.h"
#include "ft_printf.h"

void    start_autostart_programs(t_program_config *config)
{
    t_process   *process;
    char        *argv_exec[2];
    char        **envp_exec;
    int         status;

    process = malloc(sizeof(t_process));
    if (!process)
        return;

    argv_exec[0] = config->command;
    argv_exec[1] = NULL;
    envp_exec = (config->env) ? config->env : environ;

    process->pid = fork();
    if (process->pid == -1)
    {
        ft_printf("Error: Failed fork ( %s )\n", strerror(errno));
        free (process);
        return;
    }
    if (process->pid == 0)
    {
        if (execve(config->command, argv_exec, envp_exec) == -1)
        {
            ft_printf("Error: execve para %s ( %s )\n", config->name, strerror(errno));
            free(process);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        config->process = process;
        config->process->start_time = time(NULL);
        config->process->pstate = STARTING;
        config->process->restart_count = 0;
        ft_printf("✅ Proceso '%s' iniciado con PID: %d\n", config->name, config->process->pid);
    }
}


void    taskmaster_main_loop(t_program_config *config)
{
    while (1)
    {
        if (g_child_status_changed)
        {
            handle_child_status_change(config);
            g_child_status_changed = 0;
        }
        if (is_user_input_ready())
        {
            if (!prompt_loop(config))
            break;
        }
        check_all_program_timeouts(config);
        usleep(10000);
        // 1. Comprobar g_child_status_changed (y hacer waitpid si es 1).
        // 2. Comprobar timeouts de procesos (STARTING, STOPPING, etc.).
        // 3. Usar select() para esperar INPUT del usuario (no bloqueante, o con timeout corto).
        // 4. Si select() devuelve INPUT, llamar a readline()/prompt_loop.
        // 5. Si select() hace timeout, repetir (esto permite el monitoreo).
    }
    return;
}