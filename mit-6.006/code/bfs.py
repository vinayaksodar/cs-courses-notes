# Assume you are given a adjaceny list

graph = {
    "A": ["B", "C"],
    "B": ["A", "D", "E"],
    "C": ["A", "F"],
    "D": ["B"],
    "E": ["B", "F"],
    "F": ["C", "E"],
}

graph_numeric = {
    0: [1, 2],
    1: [0, 3, 4],
    2: [0, 5],
    3: [1],
    4: [1, 5],
    5: [2, 4],
}


P = {}  # parent List
d = {}
L = {}  # Level Set


# Here we use levelsets to keep track of our progress below you see the same thing but using queue
def bfs(adj, start):
    L["0"] = [start]
    i = 0
    d[(start, start)] = 0
    P[start] = None
    while True:
        temp = []
        for v in L[str(i)]:
            for u in adj[v]:
                if u not in P:
                    P[u] = v
                    d[(start, u)] = d[(start, v)] + 1
                    temp.append(u)
        if temp == []:
            break

        i = i + 1
        L[str(i)] = temp
    print(P, d, L)


bfs(graph, "A")


# Using queue cleaner code

from collections import deque


def bfs(adj, start):
    parent = {start: None}
    distance = {start: 0}

    queue = deque([start])

    while queue:
        current = queue.popleft()
        for neighbor in adj[current]:
            if neighbor not in parent:
                parent[neighbor] = current
                distance[neighbor] = distance[current] + 1
                queue.append(neighbor)
    return parent, distance


print(bfs(graph, "A"))
