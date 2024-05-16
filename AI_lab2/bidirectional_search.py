""""
    Назначение: Двунаправленный поиск используется для нахождения кратчайшего пути между
двумя вершинами на графе.
    Что делает: Алгоритм одновременно ищет путь от начальной вершины к целевой и от целевой
к начальной, сокращая время поиска.
    Как работает: Алгоритм запускает два поиска: один от начальной вершины и один от целевой.
Он продвигается от обеих сторон к центру графа до тех пор, пока пути не пересекутся.
"""


def bidirectional_search(start, destination, city_distances):
    forward_visited = set()
    backward_visited = set()
    forward_queue = [(start, [start])]
    backward_queue = [(destination, [destination])]

    while forward_queue and backward_queue:
        forward_city, forward_path = forward_queue.pop(0)
        backward_city, backward_path = backward_queue.pop(0)

        if forward_city in backward_visited:
            return forward_path + backward_path[::-1]

        if backward_city in forward_visited:
            return forward_path[::-1] + backward_path

        forward_visited.add(forward_city)
        backward_visited.add(backward_city)

        for neighbor in sorted(city_distances[forward_city].keys()):
            if neighbor not in forward_path:
                forward_queue.append((neighbor, forward_path + [neighbor]))

        for neighbor in sorted(city_distances[backward_city].keys()):
            if neighbor not in backward_path:
                backward_queue.append((neighbor, backward_path + [neighbor]))

    return None
