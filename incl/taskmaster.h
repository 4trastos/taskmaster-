#ifndef TASKMASTER_H
# define    TASKMASTER_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <sys/signal.h>
# include <sys/user.h>

typedef enum s_process_state
{
    STOPPED,            // Proceso detenido
    STARTING,           // Iniciando
    RUNNING,            // Ejecutándose correctamente
    BACKOFF,            // Reintentando arranque
    STOPPING,           // En proceso de parada
    EXITED,             // Terminado (esperando decisión)
    FATAL,              // Error fatal (sin más reintentos)
    UNKNOWN
}   t_process_state;

typedef struct s_program_config
{
    char    *name;
    char    *command;
    char    **env;
}   t_program_config;

typedef struct s_process
{
    pid_t           pid;
    int             instance_id;
    t_process_state pstate;
    time_t          start_time;
    int             restart_count;
    int             exit_code;
    int             stdout_fd;
    int             error_fd;
}   t_process;

//*** Binay logic ***/



//*** comunications & signals ***/



//*** auxiliary functions ***/



#endif