from collections import deque

""""
    Назначение: Поиск в ширину используется для нахождения кратчайшего пути на невзвешенном 
графе от начальной вершины ко всем остальным вершинам.
    Что делает: Алгоритм исследует все вершины на расстоянии 1 от начальной вершины, 
затем все вершины на расстоянии 2 и так далее, пока не будет найден путь к целевой вершине.
    Как работает: Алгоритм использует очередь для хранения вершин, которые нужно исследовать. 
Он исследует сначала все соседние вершины от начальной, затем их соседей и так далее, 
пока не достигнет целевой вершины.
"""


def breadth_first(start, destination, city_distances):
    queue = deque([(start, [start])])

    while queue:
        current_city, path = queue.popleft()

        if current_city == destination:
            return path

        for neighbor in sorted(city_distances[current_city].keys()):
            if neighbor not in path:
                new_path = list(path)
                new_path.append(neighbor)
                queue.append((neighbor, new_path))

    return None
