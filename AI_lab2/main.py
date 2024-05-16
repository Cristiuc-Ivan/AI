# main.py
from read_csv import read_csv
from a_star import a_star
from breadth_first import breadth_first
from bidirectional_search import bidirectional_search
from depth_first import depth_first
from greedy_best_first import greedy_best_first
from uniform_cost import uniform_cost

# File path for the CSV file
file_path = 'map.csv'

# Read the CSV file and get city distances
cities, city_distances = read_csv(file_path)

# Define the heuristic for Greedy Best First Search
distance_Bucharest = {
    "Arad": 366, "Bucharest": 0, "Craiova": 160, "Drobita": 242, "Eforie": 161, "Fagaras": 176,
    "Giurgiu": 77, "Hirsova": 151, "Iasi": 226, "Lugoj": 244, "Mehedia": 241, "Neamt": 234,
    "Oradea": 380, "Pitesti": 100, "RM": 193, "Sibiu": 253, "Timisoara": 329, "Urziceni": 80,
    "Vaslui": 199, "Zerind": 374
}


def get_user_input():
    start_city = input("Enter the start city: ")
    destination_city = input("Enter the destination city: ")
    return start_city, destination_city


def print_city():
    print("List of cities:")
    for city in sorted(distance_Bucharest.keys()):
        print(f"{city}")
    print("\n")


def main():
    print_city()
    start_city, destination_city = get_user_input()

    print("\nA* Search:")
    print(a_star(start_city, destination_city, city_distances, distance_Bucharest))
    print()

    print("Breadth First Search:")
    print(breadth_first(start_city, destination_city, city_distances))
    print()

    print("Bidirectional Search:")
    print(bidirectional_search(start_city, destination_city, city_distances))
    print()

    print("Depth First Search:")
    print(depth_first(start_city, destination_city, city_distances))
    print()

    print("Greedy Best First Search:")
    print(greedy_best_first(start_city, destination_city, city_distances, distance_Bucharest))
    print()

    print("Uniform Cost Search:")
    print(uniform_cost(start_city, destination_city, city_distances))
    print()


if __name__ == "__main__":
    main()
