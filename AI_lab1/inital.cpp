#include <iostream>
#include <set>

void addingUpZeros(int r, int c, int **arr) {
    // Заполняем первый и последний столбцы, а также первую строку нулями
    for (int i = 0; i < r; i++) {
        arr[i][0] = 0;                // первый столбец
        for (int j = 1; j <= c; j++) {
            arr[i][j] = 0;            // основная часть матрицы
        }
        arr[i][c + 1] = 0;             // последний столбец
    }
}

void fillingMatrix(int r, int c, int **arr) {
    // Множество для отслеживания уже введенных чисел
    std::set<int> uniqueNumbers;

    // Вводим значения с консоли и записываем их по указанным координатам
    for (int i = 2; i < r + 2; i++) {
        for (int j = 2; j < c - 2; j++) {
            int inputValue;

            // Повторяем ввод, пока не получим уникальное число
            while (true) {
                std::cout << "Enter unique value for [" << i - 2 << "][" << j - 2 << "]:";
                std::cin >> inputValue;

                // Проверяем, было ли число уже введено (исключая повторение нуля)
                if ((inputValue == 0) || (uniqueNumbers.count(inputValue) == 0)) {
                    // Записываем значение в массив и добавляем его в множество уникальных чисел
                    arr[i][j] = inputValue;
                    uniqueNumbers.insert(inputValue);
                    break;  // Выход из цикла, так как введено уникальное число
                } else {
                    std::cout << "This number already has been entered. Please enter another one."
                              << std::endl;
                }
            }
        }
    }
}

void beautifulMatrix(int r, int c, int **arr) {
    // Удаляем нули из матрицы и смещаем оставшиеся элементы вниз
    for (int j = 1; j <= c; j++) {
        int destinationRow = r + 1;
        for (int i = r + 1; i >= 2; i--) {
            if (arr[i][j] != 0) {
                arr[destinationRow][j] = arr[i][j];
                destinationRow--;
            }
        }
        // Заполняем оставшиеся строки нулями
        for (; destinationRow >= 0; destinationRow--) {
            arr[destinationRow][j] = 0;
        }
    }
}

void printMatrix(int r, int c, int **arr) {
    // Выводим содержимое массива
    for (int i = 0; i < r + 2; i++) {
        std::cout << "\t\t";
        for (int j = 0; j < c + 2; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool searchElement(int r, int c, int **arr, int target) {
    // Ищем элемент в матрице
    bool found = false;
    for (int i = 0; i < r + 2; i++) {
        for (int j = 0; j < c + 2; j++) {
            if (arr[i][j] == target) {
                std::cout << "Element " << target << " found at position [" << i << "][" << j << "]."
                          << std::endl;

                // Выводим и обнуляем все ненулевые элементы над найденным элементом
                for (int k = 0; k < i; k++) {
                    if (arr[k][j] != 0) {
                        std::cout << "Element above: " << arr[k][j] << std::endl;
                        std::cout << "Clearing the top of " << target << std::endl;
                        std::cout << "Putting " << arr[k][j] << " on table" << std::endl;
                        arr[k][j] = 0; // Превращаем в ноль
                        found = true;
                    }
                }

                // Если не было ненулевых элементов над найденным элементом
                if (!found) {
                    std::cout << "There are no non-zero elements above it." << std::endl;
                }

                return true;
            }
        }
    }

    std::cout << "Element " << target << " not found in the matrix." << std::endl;
    return false;
}

void clearMatrix(int r, int **arr) {
    // Освобождаем выделенную память
    for (int i = 0; i < r + 2; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

void moveCube() {

}

//int main() {
//    // Задаем размеры двумерного массива
//    int rows, columns, cubeNumber, rowNumber;
//
//    std::cout << "Please enter matrix dimensions" << std::endl;
//    std::cout << "Number of rows:";
//    std::cin >> rows;
//    std::cout << "Number of columns:";
//    std::cin >> columns;
//    std::cout << std::endl;
//
//    rows += 2;
//    columns += 4;
//    // Динамически выделяем память для двумерного массива
//    int **matrix = new int *[rows];
//    for (int i = 0; i < rows; i++) {
//        matrix[i] = new int[columns];
//    }
//
//    addingUpZeros(rows, columns, matrix);
//
//    fillingMatrix(rows, columns, matrix);
//
//    beautifulMatrix(rows, columns, matrix);
//
//    std::cout << std::endl << "Final matrix:" << std::endl;
//    printMatrix(rows, columns, matrix);
//
//    std::cout << std::endl << "Write number of cube you want to take:";
//    std::cin >> cubeNumber;
//    std::cout << std::endl << "Write row number where to place cube " << cubeNumber << ":";
//    std::cin >> rowNumber;
//    std::cout << std::endl;
//
//    if (rowNumber > rows)
//        std::cerr << std::endl << "Error! You entered wrong number of rows!";
//
//    searchElement(rows, columns, matrix, cubeNumber);
//
//    std::cout << std::endl;
//    printMatrix(rows, columns, matrix);
//
//    clearMatrix(rows, matrix);
//
//    return 0;
//}
