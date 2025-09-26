# taskmaster-

1) Lo esencial
	•	Objetivo: implementar un job-control daemon (algo similar a supervisord) que arranque, supervise y mantenga procesos/programas conforme a una configuración. Debe correr en una VM y no necesita ejecutarse como root; no tiene por qué convertirse en demonio: puede quedarse en primer plano y ofrecer una shell de control al usuario.  ￼
	•	Requisitos obligatorios:
	•	Leer una configuración (formato libre — YAML, JSON, etc. — puedes usar una librería externa sólo para parseo).
	•	Lanzar procesos hijos y mantenerlos vivos según la política (reiniciar cuando toque).
	•	Saber en todo momento si cada proceso está vivo (detección accurate).
	•	Recargar la configuración al recibir SIGHUP y aplicar cambios sin matar procesos que no han cambiado.
	•	Sistema de logs en fichero para eventos (start/stop/restart/muerte de procesos, reload, etc.).
	•	Proveer una shell de control (mínimo: edición de línea, historial — puedes usar readline) con comandos: status, start, stop, restart, reload, quit/stop main program.
	•	Por cada programa en la config debes soportar (lista de campos que debe aceptar la config — traducido/resumido):
	•	cmd: comando para lanzar.
	•	numprocs: cuántas instancias.
	•	autostart: arrancar al lanzar el taskmaster.
	•	autorestart: always, never, unexpected.
	•	exitcodes: lista de códigos considerados “esperados”.
	•	startretries: reintentos antes de fallar.
	•	starttime: segundos que debe sobrevivir para considerarse “arrancado OK”.
	•	stopsignal y stoptime: señal para parar y tiempo de espera antes de SIGKILL.
	•	stdout/stderr: rutas a archivos o descartar.
	•	env, workingdir, umask. (Ejemplo en el apéndice).  ￼
	•	Bonus sugeridos: privilege drop (si arrancas como root), arquitectura cliente/daemon (UNIX sockets o TCP), attach/detach con pty (tipo screen/tmux), notificaciones, etc.  ￼

⸻

2) ¿Qué tienes que hacer — desglose paso a paso (high level)
	1.	Elegir formato y parser de config (ej. YAML) — puedes usar una librería externa sólo para esto.
	2.	Diseñar estructuras en memoria:
	•	ProgramConfig (campos de la config).
	•	ProcessInstance (pid, estado, start_time, restart_count, stdout/stderr fd, instance id).
	3.	Init: leer config, crear estructuras, lanzar procesos con autostart=true.
	4.	Lanzar procesos: fork + exec (o posix_spawn), antes de exec:
	•	setear umask, chdir, env, redirecciones stdout/stderr (dup2), crear process group si hace falta.
	5.	Supervisión: monitorizar hijos:
	•	manejar SIGCHLD y usar waitpid(..., WNOHANG) para reap.
	•	mantener estado STARTING, RUNNING, STOPPED, FATAL, etc.
	•	aplicar política autorestart y startretries / starttime.
	6.	Control shell: loop de lectura (readline permitido) con comandos status, start <prog>, stop <prog>, restart <prog>, reload, quit. Actualiza estado en memoria y actúa.
	7.	Recarga SIGHUP: parsear nuevo config y:
	•	añadir programas nuevos (y arrancarlos si autostart),
	•	eliminar programas que ya no están (pararlos),
	•	cambiar numprocs (añadir/terminar instancias necesarias),
	•	no matar instancias no- cambiadas.
	•	para cambios en cmd/env/etc. reiniciar las instancias afectadas.
	8.	Logging: fichero con timestamps para eventos clave.
	9.	Apagado: cuando el usuario pide quit/stop main o recibe SIGINT/SIGTERM: para todos los programas según stopsignal->esperar->kill si necesario; salir.
	10.	Pruebas: crear programas de prueba que simulen distintos comportamientos (sale con código, crashea, produce mucho output, nunca arranca, etc.).

⸻

3) Detalles técnicos importantes (algoritmos y comportamiento esperado)

A) Lanzar procesos y preparar su entorno
	•	Para cada instancia:
	•	pipe o open a archivo destino para stdout/stderr; dup2 para redirigir antes de exec.
	•	Aplicar umask(umask), chdir(workingdir), setear env (modificar environ o pasar execve).
	•	Ejecutar el comando (recomiendo usar execvp si parseas cmd en argv, o execl("/bin/sh", "sh", "-c", cmd, NULL) si quieres permitir la línea como shell).

B) Detección de “vivo” y reap de hijos
	•	Instalar sigaction para SIGCHLD, con SA_RESTART y/o usar signalfd/epoll en Linux avanzado.
	•	En handler o en bucle principal: llamar waitpid(-1, &status, WNOHANG) en bucle para reapear todos los hijos que han cambiado. Para cada reap:
	•	registrar pid, exit_code, sig y hora.
	•	decidir si reiniciar según autorestart y exitcodes.

C) Política de reinicio (pseudocódigo)
	•	Si proceso murió antes de starttime tras iniciar:
	•	contar como fallo de arranque; intentar reiniciar hasta startretries. Si se pasa, marcar FATAL (no más reintentos) y loggear.
	•	Si proceso murió después de starttime:
	•	autorestart == always → reiniciar.
	•	autorestart == unexpected → reiniciar solo si exit_code no está en exitcodes.
	•	autorestart == never → no reiniciar.

D) SIGHUP / recarga de config
	•	Al recibir SIGHUP:
	•	parsea nuevo archivo a estructuras NewConfig.
	•	Para cada programa en NewConfig:
	•	Si no existía → crear y arrancar si autostart.
	•	Si existía → comparar campo por campo:
	•	Si nada ha cambiado → no tocar sus instancias.
	•	Si numprocs cambió → arrancar o parar instancias adicionales (detener las que sobren).
	•	Si cmd/env/workingdir/umask cambió → reiniciar sus instancias (solo las afectadas).
	•	Para programas que estaban y ya no están en NewConfig → parar sus instancias.
	•	Regla clave del enunciado: no de-spawn procesos que no hayan cambiado. Implementa comparación (hash) de ProgramConfig para decidir.

E) Parada ordenada
	•	Para stop/shutdown:
	•	enviar stopsignal (ej. SIGTERM por defecto) a cada instancia (mejor enviar a process group si los hijos generan procesos hijos).
	•	esperar hasta stoptime segundos; si siguen vivos → SIGKILL.
	•	limpiar metadata.

F) Redirección de stdout/stderr y problemas de bloqueo
	•	Si rediriges a archivo: abrir con O_APPEND/O_CREAT.
	•	Si descartas: redirigir a /dev/null.
	•	Atención: si no lees tuberías y el buffer se llena el proceso puede bloquearse; lee o redirige correctamente (usa ficheros o threads/poll para consumir output).

G) Concurrencia y consistencia
	•	Estructuras compartidas accesibles desde: signal handler, threads de IO, thread del shell y loop principal. Evita operaciones no reentrantes en handlers. Mejor: en handler de SIGCHLD simplemente escribir a un pipe de eventos o establecer una flag y hacer el trabajo de waitpid en el loop principal (safe).
	•	Usa mutexes al modificar mapas/listas de procesos desde distintos hilos.

⸻

4) Casos de prueba concretos que el grador hará — prepárate

El enunciado avisa que el corrector hará pruebas reales: matar procesos, lanzar procesos que no arrancan, generar mucho stdout, etc. Prepara estos tests:
	•	Programa que sale inmediatamente con código 1 (para probar starttime y startretries).
	•	Programa que se queda corriendo (sleep loop) — para status y reinicio.
	•	Programa que imprime muchísimo (loop printf) — comprobar redirección y no bloqueo.
	•	Programa que atrapa señales (instala handler para SIGTERM/SIGUSR1) — comprobar stopsignal y stoptime.
	•	Proceso que crea hijos — comprobar que matar al grupo mata todo, usar setpgid.

Pide en la demo: muestra status, mata con kill -9 <pid>, haz SIGHUP para recargar, modifica numprocs y muestra que no matas procesos no cambiados.

⸻

5) Conocimientos técnicos concretos que debes estudiar (lista práctica)

Prioridad alta (imprescindible):
	•	Modelos de procesos Unix: fork(2), execve(2), waitpid(2), kill(2).
	•	Señales y sigaction(2), bloqueo de señales (sigprocmask), comportamiento de SIGCHLD.
	•	Process groups / sessions: setpgid(2), setsid(2) — útil para enviar señales a todo el árbol.
	•	Redirección de fds en C: pipe(2), dup2(2), open(2).
	•	File I/O en C y flags (O_APPEND, permisos).
	•	umask(2), chdir(2), manejo de environ y execve.
	•	select(2) / poll(2) / epoll para multiplexar fds (lectura no bloqueante de stdout/stderr).
	•	readline (si quieres shell con edición/historia).
	•	Manejo de timeouts y temporización (calcular starttime, stoptime).
	•	Sintaxis de señales por nombre (mapear TERM, KILL, USR1 a números).

Útiles / recomendados:
	•	posix_spawn (alternativa a fork+exec).
	•	PTYs (forkpty, openpty) si planeas implementar attach/detach.
	•	Sockets Unix/D-Bus si vas a hacer cliente/daemon (bonus).
	•	Concurrencia: pthread o modelos concurrentes del lenguaje elegido.
	•	YAML/JSON parsing library (permitido sólo para parsing).
	•	Logging y rotación (simplemente escribe en fichero; rotación no es obligatoria).

Lecturas/manpages y libros:
	•	man fork, man execve, man waitpid, man sigaction, man setpgid, man dup2, man poll.
	•	The Linux Programming Interface — Michael Kerrisk (altamente recomendable).
	•	Advanced Programming in the UNIX Environment — W. R. Stevens.

⸻

6) Errores y trampas comunes (qué evitar)
	•	Hacer trabajo pesado dentro del handler de señales (no es seguro). Mejor comunicar evento a loop principal.
	•	No reapear todos los hijos — deja zombies.
	•	Filtrar mal el comportamiento en autorestart unexpected — ten cuidado con la lista exitcodes.
	•	Dormir en handlers o bloquear la shell mientras esperas waitpid.
	•	Dejar fds abiertos que apunten a archivos temporales/TTYs.
	•	Matar indiscriminadamente PIDs sin comprobar a qué programa pertenecen (race conditions).

⸻

7) Estructura de datos sugerida (ejemplo conceptual en C)

typedef enum { STOPPED, STARTING, RUNNING, EXITED, FATAL } state_t;

typedef struct {
    char *name;
    char *cmd;
    int numprocs;
    bool autostart;
    enum {AR_ALWAYS, AR_NEVER, AR_UNEXPECTED} autorestart;
    int *exitcodes; int n_exitcodes;
    int startretries;
    int starttime; // seconds
    int stoptime;
    int stopsignal; // SIGTERM etc.
    char *stdout_path;
    char *stderr_path;
    char **env;
    char *workingdir;
    mode_t umask;
} ProgramConfig;

typedef struct {
    pid_t pid;
    int instance_id; // 0..numprocs-1
    state_t state;
    time_t start_ts;
    int restarts;
    int last_exitcode;
    int stdout_fd, stderr_fd;
} ProcessInstance;

typedef struct {
    ProgramConfig cfg;
    ProcessInstance *instances; // array length = cfg.numprocs
    pthread_mutex_t lock;
} Program;


⸻

8) Plan de implementación sugerido (milestones)
	1.	MVP mínimo: parsear config, lanzar 1 proceso con redirección, registrar en log, proveer status.
	2.	Supervisión básica: SIGCHLD, reap y reinicio básico (sin starttime/startretries).
	3.	Implementar starttime/startretries y autorestart.
	4.	Soporte para numprocs (múltiples instancias).
	5.	Control shell con start/stop/restart/reload/quit.
	6.	SIGHUP reload: smart diffs entre configs, no matar procesos no cambiados.
	7.	Edge cases: manejo de salida masiva, procesos que crean hijos (PGID), timeouts en stop.
	8.	Hardening y tests automáticos para todos los casos que el corrector pueda probar.
	9.	Bonuses si te sobra tiempo: client/server y attach/detach por pty; privilege drop.

⸻

9) Cómo preparar la demo / defensa
	•	Ten un config de ejemplo (uno parecido al del apéndice) listo.
	•	Ten scripts de prueba (ej.: bad_start.sh que sale rápido; crash.c que segfault; spam_output.sh).
	•	Demuestra:
	•	Lanzamiento y status.
	•	Muerte de procesos (kill) y que Taskmaster los reinicia según política.
	•	SIGHUP con un cambio que añade/quita programas y que no mata procesos no cambiados.
	•	startretries/starttime en acción.
	•	stop <prog> y que respeta stopsignal+stoptime.
	•	Logs generados.
	•	Explica decisiones de diseño (cómo evitaste race conditions y dónde usaste locking vs. event loop).

⸻

10) ¿Quieres que te implemente un esqueleto?

Puedo ahora mismo generarte (en este chat) un esqueleto funcional en C (con la arquitectura básica: lectura de config YAML, estructuras, loop principal, fork+exec, SIGCHLD safe handling y shell mínima usando readline), o bien en Python para prototipado rápido.
Dime si prefieres C (más acorde al entorno 42) o Python para un prototipo rápido y te lo escribo ya (sin esperar).

Opcionee:
	•	(A) Esqueleto en C: estructuras, main + signal handling + ejemplo de start_program() y reap_children(); o
	•	(B) Prototipo en Python: más corto, parseo YAML rápido y demo de comportamiento (útil para validar lógica antes de reescribir en C).
