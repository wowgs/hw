n=int(input())
if n<2:
    print()
    exit(0)
ar=list(range(2,n+1))
for y in range(2,int(n**0.5)+1):
    ar=[x for x in ar if x==y or x%y!=0]
print(' '.join(map(str,ar)))
