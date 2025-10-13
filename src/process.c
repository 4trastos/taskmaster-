#include "taskmaster.h"
#include "ft_printf.h"

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