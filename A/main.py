test_count = int(input())

mod = 35184372089371

for _ in range(test_count):
    k = int(input())

    for i in range(1, 2000):
        if k == 0:
            break
        for j in range(0, i):
            k -= 1
            if k == 0:
                print(((2 ** i) + (2 ** j)) % mod)
                break
