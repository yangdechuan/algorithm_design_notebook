import heapq


def solve(l):
    heapq.heapify(l)
    new_l = []
    while l:
        new_l.append(heapq.heappop(l))
    return new_l


l = [9, 0, 8, 1, 7, 2, 6, 3, 5, 4]
new_l = solve(l)
print(new_l)
