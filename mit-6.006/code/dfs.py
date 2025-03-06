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


# Using recursion
def dfs(adj, start, parent=None, distance=None):
    if parent == None:
        parent = {start: None}
        distance = {start: 0}
    for v in adj[start]:
        if v not in parent:
            parent[v] = start
            distance[v] = distance[start] + 1
            dfs(adj, v, parent, distance)

    return parent, distance


print(dfs(graph, "A"))


# Using stack
def dfs(adj, start):
    stack = []
    stack.append(start)
    distance = {start: 0}
    parent = {start: None}
    while stack:
        current = stack.pop()
        for v in adj[current]:
            if v not in parent:
                parent[v] = current
                distance[v] = distance[current] + 1
                stack.append(v)
                # Visits last node in the adjacency list first, use reversed adjacency list if you don't want this
    return parent, distance


print(dfs(graph, "A"))
