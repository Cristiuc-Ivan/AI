import csv


def read_csv(file_path):
    city_distances = {}
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        cities = next(reader)  # Assuming the first row contains city names
        for city in cities:
            city_distances[city] = {}
        for row, city in zip(reader, cities):
            for destination, distance in zip(cities, row):
                city_distances[city][destination] = int(distance)
    return cities, city_distances
