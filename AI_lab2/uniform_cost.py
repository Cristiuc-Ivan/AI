from queue import PriorityQueue

""""
    Назначение: Поиск с равномерной стоимостью используется для нахождения кратчайшего пути 
на взвешенном графе, где стоимость каждого ребра может быть разной.
    Что делает: Алгоритм всегда выбирает следующую вершину с наименьшей стоимостью пути 
от начальной вершины.
    Как работает: Алгоритм использует очередь с приоритетом для выбора следующей вершины 
для исследования. Он выбирает вершину с минимальной стоимостью пути от начальной вершины.
"""


def uniform_cost(start, destination, city_distances):
    visited = set()
    priority_queue = PriorityQueue()
    priority_queue.put((0, start, [start]))

    while not priority_queue.empty():
        _, current_city, path = priority_queue.get()

        if current_city == destination:
            return path

        if current_city not in visited:
            visited.add(current_city)

            for neighbor, distance in sorted(city_distances[current_city].items(), key=lambda x: x[1]):
                if neighbor not in visited:
                    new_path = list(path)
                    new_path.append(neighbor)
                    priority_queue.put((distance, neighbor, new_path))

    return None
