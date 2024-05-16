""""
    Назначение: Поиск в глубину используется для поиска пути в глубину графа.
    Что делает: Алгоритм исследует все возможные пути от начальной вершины до конца,
передвигаясь вглубь графа, пока не найдет целевую вершину или не достигнет конца пути.
    Как работает: Алгоритм использует стек для отслеживания вершин, которые нужно исследовать.
Он продвигается глубже в граф, пока не достигнет конечной вершины или не найдет путь к цели.
"""


def depth_first(start, destination, city_distances):
    stack = [(start, [start])]

    while stack:
        current_city, path = stack.pop()

        if current_city == destination:
            return path

        for neighbor in sorted(city_distances[current_city].keys(), reverse=True):
            if neighbor not in path:
                new_path = list(path)
                new_path.append(neighbor)
                stack.append((neighbor, new_path))

    return None
