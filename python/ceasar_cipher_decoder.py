#!/usr/bin/env python3


import argparse
import string


def decode(ciphertext, shift):
    # This does not do underflow or overflow correction

    def __char__(c):
        if c not in string.ascii_letters:
            return c

        return chr(ord(c) + shift)


    return "".join(map(__char__, ciphertext))


def main(args):
    if args["shift"] < 0:
        shift_str = "<<({})".format(args["shift"])
    elif args["shift"] == 0:
        shift_str = "==".format(args["shift"])
    else:
        shift_str = ">>({})".format(args["shift"])

    while True:
        try:
            i = input()
        except:
            break

        print("{} {} {}".format(i, shift_str, decode(i, args["shift"])))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("shift", type=int, help="The key shift for a Ceasar cipher")
    args = parser.parse_args().__dict__
    main(args)

