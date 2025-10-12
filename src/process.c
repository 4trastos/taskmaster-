#include "taskmaster.h"
#include "ft_printf.h"

int is_user_input_ready(void)
{
    struct timeval  tv = {0, 0}; //Timeout inmediato 0 segundos y 0 milesimas.
    fd_set          fds;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    // select devuelve el número de file descriptors listos. 
    // Si select devuelve > 0, al menos un FD está listo.
    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0)
        return (FD_ISSET(STDIN_FILENO, &fds));
    return (0);
}

void    init_process_test(t_program_config *config, char **envp)
{
    config->command = "./bin/test_davgalle";
    config->name = "test_davgalle";
    config->env = envp;
    config->exitcodes = 0, 1;
    config->autostart = true;
    config->autorestart = AR_UNEXPECTED;
    config->startretries = 2;
    config->starttime = 1;
    config->stopsignal = "SIGTERM";
    config->stoptime = 3;
    config->stdout_path = "/tmp/test_davgalle.log";
    config->stderr_path = "test_davgalle_err.log";
    config->workingdir = "./";
    config->umask = "022";
    config->next = NULL;
    config->process = NULL;
}