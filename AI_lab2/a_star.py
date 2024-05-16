from queue import PriorityQueue

""""
    Назначение: A* является информированным алгоритмом поиска, используемым для нахождения 
кратчайшего пути от начальной вершины к целевой вершине на графе с весами на ребрах.
    Что делает: A* учитывает как стоимость пути от начальной вершины, так и оценку 
стоимости пути от текущей вершины до цели. Он пытается выбрать следующую вершину, 
которая минимизирует суммарную оценку.
    Как работает: Алгоритм использует очередь с приоритетом для выбора следующей вершины 
для исследования. Он продвигается от начальной вершины к целевой, выбирая на каждом шаге 
вершину с наименьшей оценкой.
"""


def a_star(start, destination, city_distances, heuristic):
    visited = set()
    priority_queue = PriorityQueue()
    priority_queue.put((heuristic[start], start, [start]))

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
                    priority_queue.put((heuristic[neighbor] + distance, neighbor, new_path))

    return None
