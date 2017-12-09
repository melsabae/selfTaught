#include <stdio.h>
#include <sqlite3.h>
#include <assert.h>

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

	ret = sqlite3_open_v2(
			DB,
			&db,
			SQLITE_OPEN_FULLMUTEX | SQLITE_OPEN_READWRITE,
			NULL
			);
	//printf("open: %d\n", ret);

	sqlite3_exec(db, "BEGIN", NULL, NULL, NULL);
	for(size_t j = 0; j < 2; j ++) {

		char _stmt[128] = { 0 };
		(void) snprintf(_stmt, 128, "INSERT INTO %s(value) VALUES (?)", TABLES[j]);

		for(size_t i = 0; i < 100; i ++) {
			ret = sqlite3_prepare_v2(db, _stmt, -1, &stmt, NULL);
			if(SQLITE_OK != ret) {
				printf("prepare: %d\n", ret);
				break;
			}

			ret = sqlite3_bind_int(stmt, 1, i);
			if(SQLITE_OK != ret) {
				printf("prepare: %d\n", ret);
				break;
			}

			ret = sqlite3_step(stmt);
			if(SQLITE_DONE != ret) {
				printf("prepare: %d\n", ret);
				break;
			}

			ret = sqlite3_finalize(stmt);
			if(SQLITE_OK != ret) {
				printf("prepare: %d\n", ret);
				break;
			}
		}
	}

	if(0 == ret) {
		sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
	}

	(void) ret;		// hush the compiler
	goto cleanup; // hush the compiler
cleanup:
	sqlite3_close(db); // v2 is for GC languages
	return 0;
}
