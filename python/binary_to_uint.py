from functools import partial as p
from struct import unpack as _u


def _h_uint(h: str, s: slice) -> int:
    return _t(bytes.fromhex(h[s]))


def _b_uint(b: bytes, s: slice) -> int:
    return _t(b[s])


def _h_float(h: str) -> float:
    return _u("<f", bytes.fromhex(h))[0]


def _b_float(h: bytes) -> float:
    return _u("<f", h)[0]


def get_uint(h, s):
    return _am[(type(h), s)](h) if (type(h), s) in _am else None


_t = p(int.from_bytes, byteorder='little')
_h8, _h16, _h32, _h64 = map(lambda _: p(_h_uint, s=_), map(lambda _: slice(2 ** _), range(1, 5)))  # 2, 4, 8, 16
_b8, _b16, _b32, _b64 = map(lambda _: p(_b_uint, s=_), map(lambda _: slice(2 ** _), range(4)))  # 1, 2, 4, 8

"""
bytes => bits
"""
_am = {
    (type(""),          1): _h8,
    (type(""),          2): _h16,
    (type(""),          4): _h32,
    (type(""),          8): _h64,
    (type(bytes([])),   1): _b8,
    (type(bytes([])),   2): _b16,
    (type(bytes([])),   4): _b32,
    (type(bytes([])),   8): _b64,
}
