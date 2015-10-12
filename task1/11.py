class mat:

    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def __mul__(self, x):
        aa = self.a * x.a + self.b * x.c
        bb = self.a * x.b + self.b * x.d
        cc = self.c * x.a + self.d * x.c
        dd = self.c * x.c + self.d * x.d
        return mat(aa, bb, cc, dd)

    def __str__(self):
        return str(self.a)


def po(n):
    if n == 1:
        return mat(1, 1, 1, 0)
    else:
        q = po(n // 2)
        z = q * q
        if n % 2 == 1:
            z = z * po(1)
        return z

n = int(input())
print(po(n))
