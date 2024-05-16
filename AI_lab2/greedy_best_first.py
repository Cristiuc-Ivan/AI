from queue import PriorityQueue

""""
    Назначение: Жадный поиск с приоритетом используется для нахождения пути к цели, 
ориентируясь на эвристическую оценку расстояния до цели.
    Что делает: Алгоритм всегда выбирает следующую вершину, которая, по его мнению, наиболее 
близка к цели, независимо от того, как далеко он уже находится от начальной вершины.
    Как работает: Алгоритм использует очередь с приоритетом для выбора следующей вершины 
для исследования. Он выбирает вершину, которая имеет наименьшее значение эвристической функции.
"""


def greedy_best_first(start, destination, city_distances, heuristic):
    visited = set()
    priority_queue = PriorityQueue()
    priority_queue.put((heuristic[start], start, [start]))

    while not priority_queue.empty():
        _, current_city, path = priority_queue.get()

        if current_city == destination:
            return path

        if current_city not in visited:
            visited.add(current_city)

            for neighbor in sorted(city_distances[current_city].keys(), key=lambda x: heuristic[x]):
                if neighbor not in visited:
                    new_path = list(path)
                    new_path.append(neighbor)
                    priority_queue.put((heuristic[neighbor], neighbor, new_path))

    return None
