#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	

	valor = config_get_string_value(config, "CLAVE");
	puerto =  config_get_string_value(config , "PUERTO");
	ip = config_get_string_value(config , "IP");


	// Loggeamos el valor de config

	log_info(logger, valor);
	log_info(logger, puerto);
	log_info(logger, ip);



	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	if ((nuevo_logger= log_create("tp0.log","tp0",1,LOG_LEVEL_INFO)) == NULL){
		printf("No pude crear el logger\n");
		exit(1);
	
	}
	nuevo_logger = log_create("tp0.log","tp0",1,LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if ((nuevo_config = config_create("cliente.config")) == NULL){
		printf("No se a podido leer un archivo de configuracion\n");
		exit(2);
	}
	nuevo_config = config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	// La primera te la dejo de yapa
	while(1){

		leido = readline(" >");
		if(!strncmp(leido, "\0", 1)){
			printf("Se salio del ciclo\n");
			free(leido);
			break;
		}

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		log_info(logger, leido);
		printf("Se ha leido: %s\n", leido);

	// ¡No te olvides de liberar las lineas antes de regresar!
		free(leido);
	}


}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	while(1){
		leido = readline(" >");
		if(!strncmp(leido, "\0", 1)){
			printf("Se salio del ciclo\n");
			free(leido);
			break;
		}

		agregar_a_paquete(paquete,leido,strlen(leido) + 1);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		printf("Se ha leido: %s\n", leido);

	// ¡No te olvides de liberar las lineas antes de regresar!
		free(leido);
	}

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	if(logger != 0){
		log_destroy(logger);
	}
	if(config != 0){
		config_destroy(config);
	}

	if(conexion != 0){
		liberar_conexion(conexion);
	}

}
