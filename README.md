# Taskmaster 🚀

Un **job-control daemon** similar a supervisord para lanzar, supervisar y mantener procesos según una configuración definida.

## 📋 Tabla de Contenidos
- [Descripción](#-descripción)
- [Características](#-características)
- [Requisitos](#-requisitos)
- [Configuración](#-configuración)
- [Uso](#-uso)
- [Comandos de la Shell](#-comandos-de-la-shell)
- [Estructura Técnica](#-estructura-técnica)
- [Plan de Implementación](#-plan-de-implementación)
- [Defensa y Pruebas](#-defensa-y-pruebas)

## 🎯 Descripción

Taskmaster es un daemon de control de procesos que permite:
- **Supervisar** múltiples programas simultáneamente
- **Reiniciar automáticamente** procesos caídos según políticas configurables
- **Recargar configuración** en caliente sin interrumpir servicios
- **Control interactivo** mediante una shell integrada

## ⭐ Características

### ✅ Funcionalidades Principales
- **Gestión de Procesos**: Lanzar, detener, reiniciar y supervisar procesos
- **Políticas de Reinicio**: `always`, `never`, `unexpected`
- **Shell Interactiva**: Comandos en tiempo real con historial
- **Recarga en Caliente**: Aplicar cambios de configuración sin downtime
- **Sistema de Logs**: Registro detallado de eventos
- **Redirección de E/S**: Gestión de stdout/stderr a archivos

### 🔧 Características Técnicas
- Soporte para múltiples instancias por programa
- Detección precisa del estado de procesos
- Manejo robusto de señales (SIGTERM, SIGKILL, SIGHUP)
- Timeouts configurables para arranque y parada
- Variables de entorno y directorio de trabajo personalizados

## 📋 Requisitos

### Requisitos Obligatorios
- [x] Leer configuración (YAML/JSON)
- [x] Lanzar y mantener procesos vivos
- [x] Detección precisa del estado de procesos
- [x] Recarga con SIGHUP
- [x] Sistema de logs en archivo
- [x] Shell de control interactiva

### Campos de Configuración por Programa
```yaml
cmd: "comando a ejecutar"
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
umask: "022"
```

## ⚙️ Configuración

### Ejemplo de Configuración YAML
```yaml
programs:
  webserver:
    cmd: "python -m http.server 8000"
    numprocs: 2
    autostart: true
    autorestart: "unexpected"
    exitcodes: [0]
    startretries: 3
    starttime: 5
    stopsignal: "SIGTERM"
    stoptime: 10
    stdout: "/var/log/webserver.out"
    stderr: "/var/log/webserver.err"
    workingdir: "/var/www"
    env:
      PORT: "8000"
      HOST: "localhost"

  database:
    cmd: "redis-server"
    numprocs: 1
    autostart: true
    autorestart: "always"
    # ... más configuraciones
```

## 🚀 Uso

### Iniciar Taskmaster
```bash
./taskmaster config.yaml
```

### Comandos Básicos
```bash
# Iniciar un programa
start webserver

# Detener un programa  
stop database

# Ver estado de todos los programas
status

# Reiniciar configuración
reload

# Salir de Taskmaster
quit
```

## ⌨️ Comandos de la Shell

| Comando | Descripción |
|---------|-------------|
| `status` | Estado de todos los programas |
| `status <programa>` | Estado específico de un programa |
| `start <programa>` | Iniciar programa |
| `stop <programa>` | Detener programa |
| `restart <programa>` | Reiniciar programa |
| `reload` | Recargar configuración |
| `quit` | Salir de Taskmaster |

## 🏗️ Estructura Técnica

### Arquitectura del Sistema
```
Taskmaster Core
├── Config Parser (YAML/JSON)
├── Process Manager
├── Signal Handler
├── Event Logger
└── Control Shell
```

### Estados de Proceso
```c
typedef enum {
    STOPPED,      // Proceso detenido
    STARTING,     // Iniciando
    RUNNING,      // Ejecutándose correctamente
    BACKOFF,      // Reintentando arranque
    STOPPING,     // En proceso de parada
    EXITED,       // Terminado (esperando decisión)
    FATAL,        // Error fatal (sin más reintentos)
    UNKNOWN       // Estado desconocido
} process_state_t;
```

### Estructuras de Datos Principales
```c
typedef struct {
    char *name;
    char *cmd;
    int numprocs;
    bool autostart;
    enum {AR_ALWAYS, AR_NEVER, AR_UNEXPECTED} autorestart;
    int *exitcodes;
    int n_exitcodes;
    int startretries;
    int starttime;
    int stoptime;
    int stopsignal;
    char *stdout_path;
    char *stderr_path;
    char **env;
    char *workingdir;
    mode_t umask;
} program_config_t;

typedef struct {
    pid_t pid;
    int instance_id;
    process_state_t state;
    time_t start_time;
    int restart_count;
    int exit_code;
    int stdout_fd;
    int stderr_fd;
} process_instance_t;
```

## 📅 Plan de Implementación

### Fase 1: Núcleo Básico (Semanas 1-2)
- [ ] Parser de configuración YAML
- [ ] Estructuras de datos básicas
- [ ] Lanzamiento simple de procesos
- [ ] Shell interactiva básica

### Fase 2: Supervisión (Semanas 3-4)
- [ ] Manejo de señales (SIGCHLD)
- [ ] Detección de estado de procesos
- [ ] Políticas de reinicio básicas
- [ ] Sistema de logging

### Fase 3: Funcionalidades Avanzadas (Semanas 5-6)
- [ ] Múltiples instancias (numprocs)
- [ ] Recarga con SIGHUP
- [ ] Timeouts y reintentos
- [ ] Redirección de E/S robusta

### Fase 4: Pulido y Pruebas (Semanas 7-8)
- [ ] Manejo de edge cases
- [ ] Pruebas exhaustivas
- [ ] Documentación
- [ ] Preparación para defensa

## 🧪 Defensa y Pruebas

### Casos de Prueba Esenciales
```bash
# 1. Proceso que falla inmediatamente
./test_crash_program

# 2. Proceso que produce mucho output
./test_spam_output

# 3. Proceso que ignora señales
./test_ignore_signals

# 4. Proceso con hijos
./test_with_children
```

### Demostración para la Corrección
1. **Inicio y Status**
   ```bash
   ./taskmaster demo_config.yaml
   status
   ```

2. **Recarga en Caliente**
   ```bash
   # Modificar config.yaml
   kill -HUP <taskmaster_pid>
   status  # Ver cambios aplicados
   ```

3. **Resistencia a Fallos**
   ```bash
   kill -9 <program_pid>
   status  # Ver reinicio automático
   ```

4. **Parada Ordenada**
   ```bash
   stop <program>
   # Verificar que usa stopsignal + stoptime
   ```

## 🎓 Categoría del Proyecto

**Taskmaster pertenece a:**
### 🐧 **Proyectos de Especialización System & Kernel**

**Razones:**
- Manejo avanzado de procesos y señales
- Uso intensivo de system calls
- Gestión de grupos de procesos
- Implementación de un daemon
- Interacción con el kernel via /proc

**Conocimientos clave aplicados:**
- `fork()`, `execve()`, `waitpid()`
- `sigaction()`, `kill()`, `setpgid()`
- Gestión de file descriptors
- Multiplexación I/O con `poll()`/`epoll`
- Procesos y sesiones UNIX

---

## 🚀 Comenzando

```bash
# Clonar y compilar
git clone <repository>
cd taskmaster
make

# Ejecutar con configuración de ejemplo
./taskmaster examples/demo.yaml

# Usar la shell interactiva
taskmaster> status
taskmaster> start webserver
taskmaster> quit
```

**¡Taskmaster está listo para supervisar tus procesos!** 🎉

---

*¿Necesitas ayuda? Revisa la documentación técnica o abre un issue en el repositorio.
