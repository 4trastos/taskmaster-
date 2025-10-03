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

typedef enum 
{
    STOPPED,            // Proceso detenido
    STARTING,           // Iniciando
    RUNNING,            // Ejecutándose correctamente
    BACKOFF,            // Reintentando arranque
    STOPPING,           // En proceso de parada
    EXITED,             // Terminado (esperando decisión)
    FATAL,              // Error fatal (sin más reintentos)
    UNKNOWN
}   process_state_t;

//*** Binay logic ***/



//*** comunications & signals ***/



//*** auxiliary functions ***/



#endif