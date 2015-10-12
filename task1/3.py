def power(a, n):
    if a == 0 and n == 0:
        print('Ошибке!!111 ОШИИИИБКЕ!!11')
        exit(0)
    elif n == 0:
        return 1
    elif n == 1:
        return a
    else:
        z = power(a, n // 2)
        z = z * z
        if n % 2:
            z = z * a
        return z

num, po = map(int, input().split())
mod = power(num, abs(po))
if po < 0:
    print('%.20f' % (1 / mod))
else:
    print(mod)
