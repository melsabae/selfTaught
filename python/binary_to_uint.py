from functools import partial as p
from struct import unpack as u


def h_uint(h: str, s: slice) -> int:
    return t(bytes.fromhex(h[s]))


def b_uint(b: bytes, s: slice) -> int:
    return t(b[s])


def h_float(h: str) -> float:
    return u("<f", bytes.fromhex(h))[0]


def b_float(h: bytes) -> float:
    return u("<f", h)[0]


t = p(int.from_bytes, byteorder='little')
get_h8, get_h16, get_h32, get_h64 = map(lambda _: p(h_uint, s=_), map(lambda _: slice(2 ** _), range(1, 5)))  # 2,4,8,16
get_b8, get_b16, get_b32, get_b64 = map(lambda _: p(b_uint, s=_), map(lambda _: slice(2 ** _), range(4)))  # 1,2,4,8
