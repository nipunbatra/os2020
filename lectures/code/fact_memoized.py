store = {}
def fac(n):
    if n==0 or n==1:
        return 1
    else:
        if n in store:
            return store[n]
        else:
            store[n] = n*fac(n-1)
            return store[n]
