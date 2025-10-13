#include "taskmaster.h"
#include "ft_printf.h"

void    child_status_change(t_program_config *config)
{
    pid_t   pid;
    int     status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        if (config->process && config->process->pid == pid)
        {
            ft_printf("\n⚠️ Proceso '%s' (PID %d) ha terminado.\n", config->name, config->process->pid);
            config->process->pstate = STOPPED;
            if (config->autostart == true && (config->exitcodes[0] == 0 || config->exitcodes[1] == 1))
            {
                config->process->pstate = STARTING;
                config->process->restart_count++;
                break;
            }
        }
        if (WIFEXITED(status))
            ft_printf("   Estado de salida normal: %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            ft_printf("   Terminado por señal: %d\n", WTERMSIG(status));
        free(config->process);
        config->process = NULL;
    }

    g_child_status_changed = 0;

    // Necesario para re-imprimir el prompt si estábamos esperando input
    rl_on_new_line();
    rl_redisplay();  
}

void    sigchld_handler(int signum)
{
    (void)signum;
    g_child_status_changed = 1;
}

void    sigint_handler(int signum)
{
    (void)signum;
    if (g_signal == 100)
    {
        g_signal = 1;
        rl_redisplay();
        ioctl(0, TIOCSTI, "\n");
		return ;
    }

	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    init_signal(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGCHLD, sigchld_handler);
}