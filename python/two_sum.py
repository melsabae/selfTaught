#!/usr/bin/env python3


def two_sum(ns, t):
    m = {}

    for (i, v) in enumerate(ns):
        other_value = t - v

        if other_value in m:
            return [i, m[other_value]]

        m[v] = i


if __name__ == "__main__":
    ns = [4, 5, 1, 3, 8]
    t = 7

    print(two_sum(ns, t))

