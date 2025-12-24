
#include "utils.h"


// struct MyStructureMessage* recibir_struct(int socket_cliente) {
    
//     t_list* valores = recibir_paquete(socket_cliente);

//     struct MyStructureMessage* my_struct = malloc(sizeof(struct MyStructureMessage));

   

//     int* message_len = list_remove(valores, 0);
//     my_struct->message_code = *message_len;

//     message_len = list_remove(valores, 0);
//     my_struct->modulo_name = *message_len;

//     message_len = list_remove(valores, 0);
//     my_struct->request = *message_len;

//     message_len = list_remove(valores, 0);
//     my_struct->response = *message_len;

// 	message_len = list_remove(valores, 0);
//     my_struct->query_prioridad = *message_len;

// 	message_len = list_remove(valores, 0);
//     my_struct->query_id = *message_len;
    
//     message_len = list_remove(valores, 0);
//     my_struct->worker_id = *message_len;

//     message_len = list_remove(valores, 0);
//     my_struct->query_pc = *message_len;


    
//     //Extrae `text` de la lista
//     int* text_len = list_remove(valores, 0);
//     my_struct->text = malloc(*text_len);
//     memcpy(my_struct->text, list_remove(valores, 0), *text_len);

// 	//Extrae `query_name` de la lista
//     int* query_name_len = list_remove(valores, 0);
//     my_struct->query_name = malloc(*query_name_len);
//     memcpy(my_struct->query_name, list_remove(valores, 0), *query_name_len);
            
    
//     //AGREGADO EL "comunicacionWorkerStorage"---------------------------------------------------------------------------
       
//         message_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.instruccion = *message_len;

//         message_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.direccion = *message_len;

//         message_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.tamanio = *message_len;

//         //Extrae `tag` de la lista
//         int* tag_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.tag = malloc(*tag_len);
//         memcpy(my_struct->INFOWorkerStorage.tag, list_remove(valores, 0), *tag_len);

//         //Extrae `tagdestino` de la lista
//         int* tagdest_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.tagdestino = malloc(*tagdest_len);
//         memcpy(my_struct->INFOWorkerStorage.tagdestino, list_remove(valores, 0), *tagdest_len);

//         //Extrae `contenido` de la lista
//         int* cont_len = list_remove(valores, 0);
//         my_struct->INFOWorkerStorage.contenido = malloc(*cont_len);
//         memcpy(my_struct->INFOWorkerStorage.contenido, list_remove(valores, 0), *cont_len);

//     //FIN DE "comunicacionWorkerStorage"---------------------------------------------------------------------------------
           
//     // Libera los elementos restantes de la lista
//     list_destroy_and_destroy_elements(valores, free);

//     return my_struct;
// };

struct MyStructureMessage* recibir_struct(int socket_cliente) {

    t_list* valores = recibir_paquete(socket_cliente);
    if (!valores) return NULL;

    struct MyStructureMessage* my_struct = malloc(sizeof(struct MyStructureMessage));

    int* aux_int;
    int* aux_len;
    void* aux_buf;

    /* ---------------- CAMPOS SIMPLES ---------------- */

    aux_int = list_remove(valores, 0);
    my_struct->message_code = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->modulo_name = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->request = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->response = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->query_prioridad = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->query_id = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->worker_id = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->query_pc = *aux_int;
    free(aux_int);

    /* ---------------- TEXT ---------------- */

    aux_len = list_remove(valores, 0);
    aux_buf = list_remove(valores, 0);

    my_struct->text = malloc(*aux_len + 1);
    memcpy(my_struct->text, aux_buf, *aux_len);
    my_struct->text[*aux_len] = '\0';

    free(aux_len);
    free(aux_buf);

    /* ---------------- QUERY_NAME ---------------- */

    aux_len = list_remove(valores, 0);
    aux_buf = list_remove(valores, 0);

    my_struct->query_name = malloc(*aux_len + 1);
    memcpy(my_struct->query_name, aux_buf, *aux_len);
    my_struct->query_name[*aux_len] = '\0';

    free(aux_len);
    free(aux_buf);

    /* ---------------- comunicacionWorkerStorage ---------------- */

    aux_int = list_remove(valores, 0);
    my_struct->INFOWorkerStorage.instruccion = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->INFOWorkerStorage.direccion = *aux_int;
    free(aux_int);

    aux_int = list_remove(valores, 0);
    my_struct->INFOWorkerStorage.tamanio = *aux_int;
    free(aux_int);

    /* tag */

    aux_len = list_remove(valores, 0);
    aux_buf = list_remove(valores, 0);

    my_struct->INFOWorkerStorage.tag = malloc(*aux_len + 1);
    memcpy(my_struct->INFOWorkerStorage.tag, aux_buf, *aux_len);
    my_struct->INFOWorkerStorage.tag[*aux_len] = '\0';

    free(aux_len);
    free(aux_buf);

    /* tagdestino */

    aux_len = list_remove(valores, 0);
    aux_buf = list_remove(valores, 0);

    my_struct->INFOWorkerStorage.tagdestino = malloc(*aux_len + 1);
    memcpy(my_struct->INFOWorkerStorage.tagdestino, aux_buf, *aux_len);
    my_struct->INFOWorkerStorage.tagdestino[*aux_len] = '\0';

    free(aux_len);
    free(aux_buf);

    /* contenido (buffer binario, NO string) */

    aux_len = list_remove(valores, 0);
    aux_buf = list_remove(valores, 0);

    my_struct->INFOWorkerStorage.contenido = malloc(*aux_len);
    memcpy(my_struct->INFOWorkerStorage.contenido, aux_buf, *aux_len);

    free(aux_len);
    free(aux_buf);

    /* ---------------- LIMPIEZA FINAL ---------------- */

    list_destroy(valores);

    return my_struct;
}



void enviar_struct(struct MyStructureMessage* my_struct, int socket_cliente) {
    t_paquete* paquete = crear_paquete();

    

    agregar_a_paquete(paquete, &(my_struct->message_code), sizeof(int));

    agregar_a_paquete(paquete, &(my_struct->modulo_name), sizeof(int));

    agregar_a_paquete(paquete, &(my_struct->request), sizeof(int));

    agregar_a_paquete(paquete, &(my_struct->response), sizeof(int));

	agregar_a_paquete(paquete, &(my_struct->query_prioridad), sizeof(int));

	agregar_a_paquete(paquete, &(my_struct->query_id), sizeof(int));

    agregar_a_paquete(paquete, &(my_struct->worker_id), sizeof(int));

    agregar_a_paquete(paquete, &(my_struct->query_pc), sizeof(int));

	// Agrega `text` al paquete
    int text_len = strlen(my_struct->text) + 1;
    agregar_a_paquete(paquete, &text_len, sizeof(int));         // Enviar longitud de `text`
    agregar_a_paquete(paquete, my_struct->text, text_len);      // Enviar `text`

	// Agrega `query_name` al paquete
    int query_name_len = strlen(my_struct->query_name) + 1;
    agregar_a_paquete(paquete, &query_name_len, sizeof(int));         // Enviar longitud de `query_name`
    agregar_a_paquete(paquete, my_struct->query_name, query_name_len);      // Enviar `query_name`



    //AGREGADO EL "comunicacionWorkerStorage"---------------------------------------------------------------------------

        agregar_a_paquete(paquete, &(my_struct->INFOWorkerStorage.instruccion), sizeof(int));

        agregar_a_paquete(paquete, &(my_struct->INFOWorkerStorage.direccion), sizeof(int));

        agregar_a_paquete(paquete, &(my_struct->INFOWorkerStorage.tamanio), sizeof(int));

        // Agrega 'tag' al paquete
        int tag_len = strlen(my_struct->INFOWorkerStorage.tag) +1;
        agregar_a_paquete(paquete, &tag_len, sizeof(int));         // Enviar longitud de `tag`
        agregar_a_paquete(paquete, my_struct->INFOWorkerStorage.tag, tag_len);      // Enviar `tag`

        // Agrega 'tagdestino' al paquete
        int tagdest_len = strlen(my_struct->INFOWorkerStorage.tagdestino) +1;
        agregar_a_paquete(paquete, &tagdest_len, sizeof(int));         // Enviar longitud de `tagdestino`
        agregar_a_paquete(paquete, my_struct->INFOWorkerStorage.tagdestino, tagdest_len);      // Enviar `tagdestino`

        // Agrega 'contenido' al paquete
        int cont_len = strlen(my_struct->INFOWorkerStorage.contenido) +1;
        agregar_a_paquete(paquete, &cont_len, sizeof(int));         // Enviar longitud de `contenido`
        agregar_a_paquete(paquete, my_struct->INFOWorkerStorage.contenido, cont_len);      // Enviar `contenido`

    //FIN DE "comunicacionWorkerStorage"---------------------------------------------------------------------------------

    // Envía el paquete completo
    enviar_paquete(paquete, socket_cliente);

    // Libera la memoria del paquete
    eliminar_paquete(paquete);
}



void enviar_paquete(t_paquete* paquete, int socket_cliente)
{
	int bytes = paquete->buffer->size + 2*sizeof(int);
	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}


void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

	paquete->buffer->size += tamanio + sizeof(int);
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}


t_paquete* crear_paquete(void)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = PAQUETE;
	crear_buffer(paquete);
	return paquete;
}


void crear_buffer(t_paquete* paquete)
{
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = 0;
	paquete->buffer->stream = NULL;
}


t_list* recibir_paquete(int socket_cliente)
{
		// t_log* recibir_paquete_log = log_create("recibir_paquetes.log", "BUFFER_LOG_PAQUETES", 1, LOG_LEVEL_ERROR);
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list* valores = list_create();
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);

	if (buffer == NULL) {
        // Error en recibir el buffer, retornar una lista vacía o manejar el error
        return valores;
    }


    // Verifica que el tamaño sea mayor que cero
    if (size <= 0) {
        free(buffer);
        return valores; // O maneja el error según corresponda
    }

	  while (desplazamiento < size) {
        // Verifica que podemos leer `tamanio` desde el buffer
        if (desplazamiento + sizeof(int) > size) {
			// log_error(recibir_paquete_log, "Error: tamaño de desplazamiento fuera de límites");
            break;
        }

        memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
        desplazamiento += sizeof(int);

        // Verifica que `tamanio` es válido antes de hacer `malloc`
        if (tamanio <= 0 || desplazamiento + tamanio > size) {
            // log_error(recibir_paquete_log, "Error: tamaño de dato inválido o fuera de límites");
            break;
        }

        char* valor = malloc(tamanio);
        memcpy(valor, buffer + desplazamiento, tamanio);
        desplazamiento += tamanio;

        list_add(valores, valor);
    }
	free(buffer);
	return valores;
}







int esperar_cliente(int socket_servidor, t_log* un_log, char* msj) //Agregar log para pasarlo por parametro 
{
	// Aceptamos un nuevo cliente
	int socket_cliente = accept(socket_servidor, NULL, NULL);
	log_info(un_log, "Se conecto un cliente: %s!", msj);

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) > 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		// return -1;
        return DESCONEXION;
	}
}




int iniciar_servidor(char* puerto, t_log* un_log, char* msj_servidor){

	int socket_servidor;

	struct addrinfo hints, *servinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, puerto, &hints, &servinfo);

	socket_servidor = socket(servinfo->ai_family,
                        servinfo->ai_socktype,
                        servinfo->ai_protocol);

	// Asociamos el socket a un puerto
      bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
	// Escuchamos las conexiones entrantes
      listen(socket_servidor, SOMAXCONN);

	freeaddrinfo(servinfo);
	log_info(un_log, "SERVER: %s", msj_servidor);//pasamos el mensaje por parametro

	return socket_servidor;

}







int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	// Ahora vamos a crear el socket.
	int socket_cliente = socket(server_info->ai_family,
                                server_info->ai_socktype,
                                server_info->ai_protocol);
	// Ahora que tenemos el socket, vamos a conectarlo
	while (true)
	{
		if(connect( socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == 0){

		freeaddrinfo(server_info);

		return socket_cliente;	

		} 
	}
	
	
}





void* recibir_buffer(int* size, int socket_cliente)
{
	void * buffer;
	t_log* buffer_log = log_create("buffer.log", "BUFFER_LOG_CONEXIONES", 1, LOG_LEVEL_ERROR);
	// recv(socket_cliente, size, sizeof(int), MSG_WAITALL);
	// buffer = malloc(*size);
	// recv(socket_cliente, buffer, *size, MSG_WAITALL);

   // Recibe el tamaño primero
    if (recv(socket_cliente, size, sizeof(int), MSG_WAITALL) <= 0) {
        log_error(buffer_log, "Error al recibir tamaño del paquete.");
        log_destroy(buffer_log);
        return NULL; // Error, no se recibió el tamaño
    }

    // Valida el tamaño recibido
    if (*size <= 0) {
        log_error(buffer_log, "Tamaño de paquete inválido.");
        log_destroy(buffer_log);
        return NULL;
    }

    // Asigna memoria para el buffer completo
    buffer = malloc(*size);
    if (recv(socket_cliente, buffer, *size, MSG_WAITALL) <= 0) {
        log_error(buffer_log, "Error al recibir datos del paquete.");
        free(buffer);
        log_destroy(buffer_log);
        return NULL;
    }
    log_destroy(buffer_log);
	return buffer;
}

	// void inicializar_log(){

	// 	modulo_log = log_create( "modulo.log", "LOGGER_TEST_UTILS", 1, LOG_LEVEL_INFO);
	// 	if(modulo_log == NULL){
	// 		perror("Error al cargar el log");
	// 		exit(EXIT_FAILURE);
	// 	}
	// }



int identificar_modulo(int argc, char *argv[] , char** param_name, int param_id) {
    if (argc <= param_id) {
        fprintf(stderr, "Uso: %s [identificador]\n", argv[param_id]);
        return EXIT_FAILURE;
    }

    // Liberar memoria si ya estaba asignado
    if (*param_name != NULL) {
         free(*param_name);
         *param_name = NULL;
    }

    // Asignar nuevo ID (duplicando el string para seguridad)
    *param_name = strdup(argv[param_id]);
    if (*param_name == NULL) {
        perror("Error al asignar memoria para param_name");
        return EXIT_FAILURE;
    }

    printf("Modulo[%s] iniciada correctamente.\n", *param_name);
    return EXIT_SUCCESS;
}



void inicializar_log(t_log** log_new , char* log_name , char* name_descriptor){

	char* logger_descriptor = string_from_format("LOGGER_%s", name_descriptor);
	*log_new = log_create( log_name, logger_descriptor, 1, LOG_LEVEL_INFO);

    free(logger_descriptor);
	if(*log_new == NULL){
		perror("Error al cargar el log");
		exit(EXIT_FAILURE);
	}
}




struct MyStructureMessage* crear_mensaje() {
    struct MyStructureMessage* msg = malloc(sizeof(struct MyStructureMessage));
    if (!msg) return NULL; // defensivo

    msg->message_code = 0;
    msg->modulo_name = 0;
    msg->request = 0;
    msg->response = 0;
    msg->query_prioridad = 0;
    msg->query_id = -1;
    msg->worker_id = -1;
    msg->query_pc = 0;

    msg->text = strdup("");
    msg->query_name = strdup("");

    msg->INFOWorkerStorage.instruccion = 0;
    msg->INFOWorkerStorage.direccion = 0;
    msg->INFOWorkerStorage.tamanio = 0;
    msg->INFOWorkerStorage.tag = strdup("");
    msg->INFOWorkerStorage.tagdestino = strdup("");
    msg->INFOWorkerStorage.contenido = strdup("");
    return msg;
}



void destruir_struct(struct MyStructureMessage* msg) {
    if (!msg) return;

    free(msg->text);
    free(msg->query_name);

    free(msg->INFOWorkerStorage.tag);
    free(msg->INFOWorkerStorage.tagdestino);
    free(msg->INFOWorkerStorage.contenido);

    free(msg);
}
