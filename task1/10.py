def kmp(s, t):
    def prefix(s):
        v = [0] * len(s)
        for i in range(1, len(s)):
            k = v[i - 1]
            while k > 0 and s[k] != s[i]:
                k = v[k - 1]
            if s[k] == s[i]:
                k += 1
            v[i] = k
        return v
    res = 0
    f = prefix(s)
    k = 0
    m = len(s)
    for i in range(len(t)):
        while k > 0 and s[k] != t[i]:
            k = f[k - 1]
        if s[k] == t[i]:
            k += 1
        if k == m:
            res += 1
            k = 0
    return res


print(kmp(*input().split()))  # string and text
