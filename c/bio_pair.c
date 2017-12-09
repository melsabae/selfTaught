#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

#define OUTPUT_END (0)
#define INPUT_END (1)

#define DEBUG_PROCESS_VALUE(x, y) \
	(fprintf(stderr, "%s: process_value : %d\n", x, y))

bool signal_caught = false;

void signal_handler(int signal)
{
	signal_caught = true;
}

int main(void)
{
	int exit_code = EXIT_FAILURE;
	int process_value = 0;
	uint8_t read_buffer[UINT16_MAX] = { 0 };
	uint8_t write_buffer[UINT16_MAX] = { 0 };
	size_t write_counter = 0;
	size_t write_bytes = 0;
	BIO* bio1 = NULL;
	BIO* bio2 = NULL;
	//SSL_CTX* ctx = NULL;
	//SSL* ssl = NULL;

	(void) signal(SIGINT, signal_handler);

	(void) BIO_new_bio_pair(&bio1, 0, &bio2, 0);
	if(NULL == bio1
			|| NULL == bio2)
	{ goto function_exit; }

	//ctx = SSL_CTX_new(TLS_method());
	//if(NULL == ctx) { goto function_exit; }
	//ssl = SSL_new(ctx);
	//if(NULL == ssl) { goto function_exit; }

	(void) BIO_reset(bio1);
	(void) BIO_reset(bio2);

	while(false == signal_caught)
	{
		write_bytes = snprintf((char*) write_buffer, UINT16_MAX,
				"%s %zu\n", "ahoy, matey!", ++ write_counter);

		process_value = BIO_write(bio1, write_buffer,
				strnlen((char*) write_buffer, UINT16_MAX));

		process_value = BIO_read(bio2, read_buffer, UINT16_MAX);

		printf("read buffer: %s", read_buffer);
	}

	(void) BIO_reset(bio1);
	(void) BIO_reset(bio2);
	(void) BIO_destroy_bio_pair(bio1);
	(void) BIO_destroy_bio_pair(bio2);
	exit_code = EXIT_SUCCESS;
function_exit:
	if(NULL != bio1) { (void) BIO_free(bio1); }
	if(NULL != bio2) { (void) BIO_free(bio2); }
	exit(exit_code);
}
