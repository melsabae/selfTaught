from functools import partial as pa


def h_uint(h: str, s: slice) -> int:
    return t(bytes.fromhex(h[s]))


def b_uint(b: bytes, s: slice) -> int:
    return t(b[s])


t = pa(int.from_bytes, byteorder='little')
get_h8, get_h16, get_h32, get_h64 = map(lambda _: pa(h_uint, s=_), map(lambda _: slice(2 ** _), range(1, 5)))  # 2,4,8,16
get_b8, get_b16, get_b32, get_b64 = map(lambda _: pa(b_uint, s=_), map(lambda _: slice(2 ** _), range(4)))  # 1,2,4,8
