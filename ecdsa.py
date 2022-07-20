from hashlib import sha256
import sm2.py

def hash_message(message):

    message_hash = hashlib.sha512(message).digest()
    e = int.from_bytes(message_hash, 'big')
    z = e >> (e.bit_length() - curve.n.bit_length())
    assert z.bit_length() <= curve.n.bit_length()
    return z


def sign_message(private_key, message):

    z = hash_message(message)
    r = 0
    s = 0
    t = tuple()
    while not r or not s:
        k = random.randrange(1, curve.n)
        x, y = scalar_mult(k, curve.g)
        r = x % curve.n
        s = ((z + r * private_key) * inverse_mod(k, curve.n)) % curve.n

        t = (r, s)
    return t


def verify_signature(public_key, message, signature):
    z = hash_message(message)

    r, s = signature

    w = inverse_mod(int(str(s), 16), curve.n)
    u1 = (z * w) % curve.n
    u2 = (int(str(r), 16) * w) % curve.n
    x, y = point_add(scalar_mult(u1, curve.g),
                     scalar_mult(u2, public_key))
    if (int(str(r), 16) % curve.n) == (x % curve.n):
        return 'success'
    else:
        return 'failure'