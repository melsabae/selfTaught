#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef int32_t err_code;
typedef err_code (*p_init_func)(void);
typedef err_code (*p_deinit_func)(void);

#define EXPAND_ENUMERATION(a, b, c)	a,
#define EXPAND_PROTOTYPE(a,b,c)			err_code b (void);
#define EXPAND_STRING(a,b,c)				#b,
#define EXPAND_FUNCTION(a,b,c)			b,
#define EXPAND_ERROR_CODE(a,b,c)		c,

#define INIT_TABLE(ENTRY)												\
	ENTRY(INIT_CONFIG,	init_config,		EXIT_SUCCESS)				\
ENTRY(INIT_THREADS,		init_threads,		EXIT_SUCCESS)				\
ENTRY(INIT_RESOURCES,	init_resources, EXIT_SUCCESS)				\
ENTRY(INIT_DB,				init_db,				EXIT_SUCCESS)				\
ENTRY(INIT_IPC,				init_ipc,				EXIT_SUCCESS)				\
ENTRY(INIT_NET,				init_net,				EXIT_SUCCESS)

#define DEINIT_TABLE(ENTRY)												\
	ENTRY(DEINIT_CONFIG,	deinit_config,		EXIT_SUCCESS)				\
ENTRY(DEINIT_THREADS,		deinit_threads,		EXIT_SUCCESS)				\
ENTRY(DEINIT_RESOURCES,	deinit_resources, EXIT_SUCCESS)				\
ENTRY(DEINIT_DB,				deinit_db,				EXIT_SUCCESS)				\
ENTRY(DEINIT_IPC,				deinit_ipc,				EXIT_SUCCESS)				\
ENTRY(DEINIT_NET,				deinit_net,				EXIT_SUCCESS)

typedef enum {
	INIT_TABLE(EXPAND_ENUMERATION)
		INIT_COUNT,
} INIT_FUNCTIONS;

typedef enum {
	DEINIT_TABLE(EXPAND_ENUMERATION)
		DEINIT_COUNT,
} DEINIT_FUNCTIONS;

const char* init_func_strings[INIT_COUNT] = {
	INIT_TABLE(EXPAND_STRING)
};

const err_code init_success_codes[INIT_COUNT] = {
	INIT_TABLE(EXPAND_ERROR_CODE)
};

INIT_TABLE(EXPAND_PROTOTYPE);

const p_init_func init_functions[INIT_COUNT] = {
	INIT_TABLE(EXPAND_FUNCTION)
};

const char* deinit_func_strings[INIT_COUNT] = {
	DEINIT_TABLE(EXPAND_STRING)
};

const err_code deinit_success_codes[INIT_COUNT] = {
	DEINIT_TABLE(EXPAND_ERROR_CODE)
};

DEINIT_TABLE(EXPAND_PROTOTYPE);

const p_deinit_func deinit_functions[INIT_COUNT] = {
	DEINIT_TABLE(EXPAND_FUNCTION)
};

err_code init_config (void) {
	return EXIT_SUCCESS;
}

err_code init_threads(void) {
	return EXIT_SUCCESS;
}

err_code init_resources(void) {
	return EXIT_SUCCESS;
}

err_code init_db (void) {
	return EXIT_SUCCESS;
}

err_code init_net (void) {
	return EXIT_SUCCESS;
}

err_code init_ipc(void) {
	return EXIT_SUCCESS;
}

err_code deinit_config (void) {
	return EXIT_SUCCESS;
}

err_code deinit_threads(void) {
	return EXIT_SUCCESS;
}

err_code deinit_resources(void) {
	return EXIT_SUCCESS;
}

err_code deinit_db(void) {
	return EXIT_SUCCESS;
}

err_code deinit_ipc (void) {
	return EXIT_SUCCESS;
}

err_code deinit_net(void) {
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	(void) argc;
	(void) argv;

	err_code error = 0;

	for(size_t i = 0; i < INIT_COUNT; i ++ ) {
		if (INIT_DB == i) {
			puts("doing the database shuffle");
		}

		printf("starting %s\n", init_func_strings[i]);
		error = init_functions[i]();
		if(init_success_codes[i] != error) {
			printf("failed to initialize %s, return code %" PRId32 "\n",
					init_func_strings[i], error);
			exit(EXIT_FAILURE);
		}
	}

	for(size_t i = 0; i < INIT_COUNT; i ++ ) {
		printf("starting %s\n", deinit_func_strings[i]);
		error = deinit_functions[i]();
		if(deinit_success_codes[i] != error) {
			printf("failed to initialize %s, return code %" PRId32 "\n",
					deinit_func_strings[i], error);
			exit(EXIT_FAILURE);
		}
	}

	return EXIT_SUCCESS;
}
