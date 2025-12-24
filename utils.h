#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>

#include <assert.h>
#include <readline/readline.h>
#include <commons/string.h>
#include <pthread.h>

#include <commons/temporal.h>

#include <unistd.h>
#include <semaphore.h>





typedef enum
{
    MENSAJE,
	PAQUETE,
    DESCONEXION,
	
}op_code;


typedef struct
{
	int size;
	void* stream;
} t_buffer;



typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;



typedef enum
{   

    COD_1,
    COD_2,
    
}MESSAGE_CODE;


typedef enum
{   

    STORAGE,
    QUERY,
    MASTER,
    WORKER,
    
}MODULE_NAME;


typedef enum
{   
    HANDSHAKE,
    INIT_QUERY,
    RUN_QUERY,
    END_QUERY,
    DATA_READ,
    RTA_STORAGE,
    INTERRUPT,
    INTERRUPT_DISCONNECT_QUERY,
    ERROR_WORKER,
    PAGE_FAULT,
    LENGHT_TABLA,
    
}REQUEST;


typedef enum
{   
    CREATE,
    TRUNCATE,
    WRITE,
    READ,
    TAG,
    COMMIT,
    FLUSH,
    DELETE,
    END,
    
    
}INSTRUCCION;

typedef enum
{   

  OK,
  ERROR,
    
}RESPONSE;

typedef struct 
{
    INSTRUCCION instruccion;
    int direccion;
    int tamanio;
    char* tag;
    char* tagdestino;
    char* contenido;

}comunicacionWorkerStorage;

struct MyStructureMessage {
    
    MESSAGE_CODE message_code;
    MODULE_NAME modulo_name;
    REQUEST request;
    RESPONSE response;
    int query_prioridad;
    int query_id;
    int worker_id;
    int query_pc;
    char * text;
    char * query_name;
    comunicacionWorkerStorage INFOWorkerStorage;
    

};

int iniciar_servidor(char* puerto, t_log* un_log, char* msj_servidor);

void enviar_struct(struct MyStructureMessage* my_struct, int socket_cliente);

struct MyStructureMessage* recibir_struct(int socket_cliente);

void enviar_paquete(t_paquete* paquete, int socket_cliente);

void* serializar_paquete(t_paquete* paquete, int bytes);

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);

void eliminar_paquete(t_paquete* paquete);

t_paquete* crear_paquete(void);

t_list* recibir_paquete(int socket_cliente);

void crear_buffer(t_paquete* paquete);

int crear_conexion(char *ip, char* puerto);


int recibir_operacion(int socket_cliente);

int esperar_cliente(int socket_servidor, t_log* un_log, char* msj) ;

// void inicializar_log();

void* recibir_buffer(int* size, int socket_cliente);

int identificar_modulo(int argc, char *argv[] , char** param_name, int param_id);

void inicializar_log(t_log** log_new , char* log_name , char* name_descriptor);

struct MyStructureMessage* crear_mensaje(); 

void destruir_struct(struct MyStructureMessage* msg); 

#endif