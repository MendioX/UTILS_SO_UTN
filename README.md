# UTILS SO UTN - Las utils de la muerte.

El codigo que pueden ver en este repo esta destinado a facilitar la implementacion de cliente/servidor para la materia de Sistemas Operativos de UTN. La idea es que puedan hacerce un copy paste de esto y llevarlo a la implementacion de sus TP con las modificaciones que qieran.

Librería en C para **comunicación cliente-servidor mediante sockets**, desarrollada para proyectos de Sistemas Operativos (UTN).

Permite enviar y recibir **estructuras complejas** de forma serializada, incluyendo:
- tipos simples
- strings dinámicos
- buffers binarios
- estructuras anidadas

La librería abstrae el manejo de paquetes, serialización y deserialización, manteniendo un protocolo claro y determinístico.

---

## 📦 Estructuras de datos

### Estructura de comunicación anidada

```c
typedef struct {
    INSTRUCCION instruccion;
    int direccion;
    int tamanio;
    char* tag;
    char* tagdestino;
    char* contenido;   // buffer binario (no necesariamente string)
} comunicacionWorkerStorage;


typedef struct {
    MESSAGE_CODE message_code;
    MODULE_NAME modulo_name;
    REQUEST request;
    RESPONSE response;

    int query_prioridad;
    int query_id;
    int worker_id;
    int query_pc;

    char* text;
    char* query_name;

    comunicacionWorkerStorage INFOWorkerStorage;
} MyStructureMessage;



```


### 🔁 Flujo de comunicación

El servidor inicia y queda a la espera de conexiones.

El cliente establece conexión con el servidor.

El cliente crea un MyStructureMessage.

El cliente envía el mensaje con enviar_struct.

El servidor recibe el mensaje con recibir_struct.

Ambos liberan correctamente la memoria utilizada.




### 🖥️ Ejemplo de servidor
```c
#include "utils.h"

int main() {
    t_log* log;
    inicializar_log(&log, "server.log", "SERVER");

    int socket_servidor = iniciar_servidor("8080", log, "Servidor iniciado");
    int socket_cliente = esperar_cliente(socket_servidor, log, "Cliente conectado");
    
    int cod_op = recibir_operacion(socket_cliente); // si no haces esto no deserealizas el inicio del paquete

     if(cod_op == DESCONEXION ){
        return NULL;
     }
    MyStructureMessage* msg = recibir_struct(socket_cliente);// ahora si lees el contenido del paquete.
   
    if (cod_op == PAQUETE && msg) {
        log_info(log, "Mensaje recibido");
        log_info(log, "Text: %s", msg->text);
        log_info(log, "Query name: %s", msg->query_name);
        log_info(log, "Tag origen: %s", msg->INFOWorkerStorage.tag);

        destruir_struct(msg);// libera recursos como un campeon y te olvidas de los leaks.
    }

    close(socket_cliente);
    close(socket_servidor);
    log_destroy(log);
    return 0;
}

```


### 💻 Ejemplo de cliente

```c
#include "utils.h"

int main() {
    int socket = crear_conexion("127.0.0.1", "8080");

    MyStructureMessage* msg = crear_mensaje(); // inicializa todos los campos del paquete, esto porque si no usas alguno no te comas un segfault de la gran flauta y solo usas lo que necesitas.

    msg->message_code = 1; // RECOMENDABLE USAR UN ENUM ASI ES MAS LEGIBLE
    msg->request = 2; // RECOMENDABLE USAR UN ENUM ASI ES MAS LEGIBLE

    free(msg->text);
    msg->text = strdup("Hola desde el cliente");

    free(msg->query_name);
    msg->query_name = strdup("QUERY_TEST");

    msg->INFOWorkerStorage.instruccion = 10;
    msg->INFOWorkerStorage.direccion = 256;
    msg->INFOWorkerStorage.tamanio = 64;

    free(msg->INFOWorkerStorage.tag);// siempre que sea char* libero el contenido que tenia antes (por los leaks)
    msg->INFOWorkerStorage.tag = strdup("CLIENTE");

    free(msg->INFOWorkerStorage.tagdestino);
    msg->INFOWorkerStorage.tagdestino = strdup("SERVIDOR");

    free(msg->INFOWorkerStorage.contenido);
    msg->INFOWorkerStorage.contenido = strdup("BUFFER_DE_DATOS");

    enviar_struct(msg, socket);
    destruir_struct(msg); // esto hace todos los free

    close(socket);
    return 0;
}

```

### 📤 Envío y recepción de mensajes

```c

// ENVIO

void enviar_struct(MyStructureMessage* msg, int socket_cliente);

// Serializa todos los campos del mensaje

// Envía tamaños + buffers

// Mantiene orden estricto del protocolo
```

```c
// RECEPCION

int cod_op = recibir_operacion(socket_cliente);
MyStructureMessage* recibir_struct(int socket_cliente);


// Esa dupla de funciones va siempre y es ese orden.

// Reconstruye el mensaje respetando el orden de envío

// Reserva memoria dinámica para strings y buffers

// Retorna NULL si falla la recepción

```

### 🧹 Manejo de memoria

REGLA: Si creo el mensaje, destruyo el mensaje.

```c
MyStructureMessage* crear_mensaje(); // inicializo el paquete para usarlo
void destruir_struct(MyStructureMessage* msg); // libero todos sus recursos luego de usarlo.
```

## 👤 Autor

Desarrollado por **Nahuel Nehuen Mendiolar Colombo**  
Proyecto creado en el contexto de trabajos prácticos de  
**Sistemas Operativos – UTN**

Repositorio mantenido para reutilización en futuros proyectos
académicos y personales.