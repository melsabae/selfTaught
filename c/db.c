#include <stdio.h>
#include <sqlite3.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include <inttypes.h>
#include <stdbool.h>

const char* DB = "/media/sf_vboxshare/test.db";
const char* TABLES[] = {
	"test_table1",
	"test_table2",
};

int main()
{
	sqlite3* db = NULL;
	sqlite3_stmt* stmt = NULL;
	int ret = 0;
	char _stmt[512] = { 0 };
	struct timeval tv;
	uint8_t array[] = {
		0, 1, 2, 3, 4, 5, 6, 7,
		7, 6, 5, 4, 3, 2, 1, 0,
	};

	(void) sqlite3_open_v2(
			DB,
			&db,
			SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE,
			NULL);


	/* test writing data conforming to the schema */
	snprintf(_stmt, 256, "INSERT INTO test_table1(record_ts_unix, integer, \
		text, blob, real) VALUES (?, ?, ?, ?, ?)");

	(void) sqlite3_exec(db, "BEGIN", NULL, NULL, NULL);
	(void) sqlite3_prepare_v2(db, _stmt, -1, &stmt, NULL);
	for(size_t i = 0; i < 1000000; i ++) {
		(void) gettimeofday(&tv, NULL);
		(void) sqlite3_bind_int(stmt, 1, tv.tv_sec);
		(void) sqlite3_bind_int(stmt, 2, i);
		(void) sqlite3_bind_text(stmt, 3, "ahoy, matey!", -1, SQLITE_STATIC);
		(void) sqlite3_bind_blob(stmt, 4, array, 16, SQLITE_STATIC);
		(void) sqlite3_bind_double(stmt, 5, pow(i, 3));
		(void) sqlite3_step(stmt);
		(void) sqlite3_reset(stmt);
	}
	(void) sqlite3_finalize(stmt);
	(void) sqlite3_exec(db, "COMMIT", NULL, NULL, NULL); // assume it all worked

//	/* test reading data from a table*/
//	snprintf(_stmt, 256, "SELECT * FROM test_table1");
//	(void) sqlite3_prepare_v2(db, _stmt, -1, &stmt, NULL);
//
//	while(true) {
//		ret = sqlite3_step(stmt);
//		if(SQLITE_ROW != ret) { break; }
//
//		int pkey = sqlite3_column_int(stmt, 0);
//		const unsigned char* insertion_ts = sqlite3_column_text(stmt, 1);
//		int timestamp = sqlite3_column_int(stmt, 2);
//		int integer = sqlite3_column_int(stmt, 3);
//		const unsigned char* text = sqlite3_column_text(stmt, 4);
//		size_t size = sqlite3_column_bytes(stmt, 5);
//		const uint8_t* blob = sqlite3_column_blob(stmt, 5);
//		double real = sqlite3_column_double(stmt, 6);
//
//		printf ("%d, %s, %d, %d, %s, %lf\n",
//				pkey,
//				insertion_ts,
//				timestamp,
//				integer,
//				text,
//				real);
//
//		for (size_t i = 0; i < size; i ++)
//		{
//			printf ("%.2" PRIX8 " ", blob[i]);
//		}
//		puts("\n");
//	}
//	sqlite3_finalize(stmt);
//

	(void) ret;		// hush the compiler
	goto cleanup; // hush the compiler
cleanup:
	sqlite3_close(db); // v2 is for GC languages
	return 0;
}
