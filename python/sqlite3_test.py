#!/usr/bin/env python3


import sqlite3
import random
import string


def generate_thing(*args):
    return { "name": ''.join(random.choices(string.ascii_lowercase, k=7)), "value": random.random() }


if __name__ == "__main__":
    con = sqlite3.connect("test.db")
    cur = con.cursor()

    cur.execute("CREATE TABLE IF NOT EXISTS datas(name, value)")

    datas = list(map(generate_thing, range(10)))
    sql_datas = list(map(lambda json: repr((json["name"], json["value"])), datas))
    sql_datas2 = list(map(lambda json: (json["name"], json["value"]), datas))

    cur.execute("INSERT INTO datas VALUES {}".format(",".join(sql_datas)))
    cur.executemany("INSERT INTO datas VALUES (?, ?)", sql_datas2)
    con.commit()

    print(len(sql_datas),len( sql_datas2))

    exit(0)

