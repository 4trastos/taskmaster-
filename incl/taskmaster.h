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

/* cmd: "comando a ejecutar"
numprocs: 1
autostart: true
autorestart: "unexpected"  # always, never, unexpected
exitcodes: [0, 1]
startretries: 3
starttime: 5
stopsignal: "SIGTERM"
stoptime: 10
stdout: "/path/to/stdout.log"
stderr: "/path/to/stderr.log"
env:
  VAR1: "valor1"
  VAR2: "valor2"
workingdir: "/path/to/workdir"
umask: "022" */

typedef enum s_autorestart
{
    AR_ALWAYS,
    AR_NEVER,
    AR_UNEXPECTED
}   t_autorestart;

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
    char            *name;
    char            *command;
    char            **env;
    char            *workingdir;
    char            *stdout_path;
    char            *stderr_path;
    int             *exitcodes;
    int             numbexicod;
    int             numprocs;
    int             starttime;
    int             stoptime;
    int             stopsignal;
    int             startretries;
    bool            autostart;
    mode_t          umask;
    t_autorestart   autorestart;
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