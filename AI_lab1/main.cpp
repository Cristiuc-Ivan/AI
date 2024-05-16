#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>

// Open a file for output
std::ofstream outputFile("output.txt");

void cmdHandler(const std::string& cmd, int target, int columnNumber) {
    std::ifstream inputFile("output.txt");
    if (cmd.find("How did you") == 0) {
        std::istringstream iss(cmd);
        std::string word;
        for (int i = 0; i < 4; i++) {
            iss >> word; // Получаем следующее слово после "How did you"
        }

        // Обработка различных подкоманд для "How did you"
        if (word == "cleared") {
            iss >> word; // Получаем слово "the"
            iss >> word; // Получаем слово "top"
            if (word == "top") {
                // Обработка команды "How did you clear the top of X"
                iss >> word; // Получаем слово "of"
                iss >> word; // Получаем X

                // Открываем файл для чтения
                if (inputFile.is_open()) {
                    std::string line;

                    // Выводим все строки из файла
                    while (std::getline(inputFile, line)) {
                        std::cout << line << std::endl;
                    }

                    // Закрываем файл
                    inputFile.close();
                } else {
                    std::cerr << "Unable to open output.txt" << std::endl;
                }
            }
        }
        else if (word == "get") {
            iss >> word; // Получаем следующее слово после "get"
            if (word == "rid") {
                // Обработка команды "How did you get rid of X"
                iss >> word; // Получаем слово "of"
                iss >> word; // Получаем X

                // Открываем файл для чтения
                if (inputFile.is_open()) {
                    std::string line;

                    // Выводим все строки из файла, которые начинаются с "# Clearing" или "# Grasping" и содержат X
                    while (std::getline(inputFile, line)) {
                        if ((line.find("# Putting") != std::string::npos || line.find("# Grasping") != std::string::npos) &&
                            line.find(word) != std::string::npos) {
                            std::cout << line << std::endl;
                        }
                    }

                    // Закрываем файл
                    inputFile.close();
                } else {
                    std::cerr << "Unable to open output.txt" << std::endl;
                }
            }
        } else {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }
    else if (cmd.find("Why did you") == 0) {
        std::istringstream iss(cmd);
        std::string word;
        for (int i = 0; i < 4; i++) {
            iss >> word; // Получаем следующее слово после "Why did you"
        }

        // Обработка различных подкоманд для "Why did you"
        if (word == "clear") {
            iss >> word; // Получаем слово "the"
            iss >> word; // Получаем слово "top"
            if (word == "top") {
                // Обработка команды "How did you clear the top of X"
                iss >> word; // Получаем слово "of"
                iss >> word; // Получаем X

                // Открываем файл для чтения
                std::ifstream inputFile("output.txt");
                if (inputFile.is_open()) {
                    std::cout << "Because I found this elements above: ";
                    std::string line;

                    // Выводим содержимое файла
                    while (std::getline(inputFile, line)) {
                        std::istringstream issf(line);
                        std::string firstWord;
                        issf >> firstWord;

                        // Проверяем первое слово в строке
                        if (firstWord == "#") {
                            std::string command;
                            issf >> command;
                            if (command == "Element" && issf >> command && command == "above:") {
                                std::string output;
                                while (issf >> output) {
                                    std::cout << output;
                                }
                                std::cout << " ";
                            }
                        }
                    }

                    std::cout << std::endl;
                    // Закрываем файл
                    inputFile.close();
                } else {
                    std::cerr << "Unable to open output.txt" << std::endl;
                }

            }
        }
        else if (word == "get") {
            iss >> word; // Получаем следующее слово после "get"
            if (word == "rid") {
                // Обработка команды "Why did you get rid of X"
                iss >> word; // Получаем слово "of"
                iss >> word; // Получаем X

                std::cout << "Because " << word << " is above " << target << std::endl;
                } else {
                    std::cerr << "Unable to open output.txt" << std::endl;
                }
        }
        else if (word == "put") {
            std::basic_string<char> upCube;
            std::basic_string<char> downCube;
            iss >> word; // Получаем target element
            upCube = word;
            iss >> word; // Получаем "on"
            iss >> word; // Получаем top element
            downCube = word;

            std::cout << "Because user said to move " << target << " to the top of "
                      << columnNumber << " column" << std::endl;
        }
        else if (word == "grasp") {
            iss >> word; // Получаем target element

            if (std::stoi(word) == target)
                std::cout << "Because user said to move " << target << std::endl;
            else
                std::cout << "Because element " << word << " was above " << target << std::endl;
        }
        else {
            std::cout << "Unknown command: " << cmd << std::endl;
        }
    }
    else {
        std::cout << "No such command!" << std::endl;
    }
}

// Заполнение матрицы пользователем с клавиатуры
void fillingMatrix (int r, int c, std::vector<std::vector<int>> &arr) {
    std::set<int> uniqueElements;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            int element;
            do {
                std::cout << "Enter unique value for [" << i + 1 << "][" << j + 1 << "]:";
                std::cin >> element;

                if (element != 0 && uniqueElements.count(element) != 0) {
                    std::cout << "This number already has been entered. Please enter another one."
                              << std::endl;
                } else {
                    uniqueElements.insert(element);
                    arr[i][j] = element;
                    break;  // Добавлен break, чтобы выйти из цикла после успешного ввода
                }
            } while (element != 0);
        }
    }

}

// Добавляет нулевые строки и столбцы
void addingZeroes (int c, std::vector<std::vector<int>> &arr) {
    // Добавление 2 нулевых строк сверху
    arr.insert(arr.begin(), std::vector<int>(c, 0));
    arr.insert(arr.begin(), std::vector<int>(c, 0));

    // Добавление 2 нулевых столбцов слева
    for (auto & i : arr) {
        i.insert(i.begin(), 0);
        i.insert(i.begin(), 0);
    }

    // Добавление 2 нулевых столбцов справа
    for (auto & i : arr) {
        i.push_back(0);
        i.push_back(0);
    }
}

// Приводит матрицу к такому виду, чтобы кубики не находелись в воздухе (над нулями)
void beautifulMatrix(int r, int c, std::vector<std::vector<int>>& arr) {
    // Удаляем нули из матрицы и смещаем оставшиеся элементы вниз
    for (int j = 1; j <= c + 1; j++) {
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

// Ищет элемент в матрице и очищает его верхушку, если это требуется
bool searchAndClearTop(int r, int c, std::vector<std::vector<int>>& arr, int target) {
    // Redirecting std::cout to the file
    std::streambuf *coutbuf = std::cout.rdbuf(); // Save old buf
    std::cout.rdbuf(outputFile.rdbuf()); // Redirect std::cout to outFile

    // Ищем элемент в матрице
    bool found = false;
    for (int i = 0; i < r + 2; i++) {
        for (int j = 0; j < c + 2; j++) {
            if (arr[i][j] == target) {
                outputFile << "# Element " << target << " found at position [" << i << "][" << j << "]." << std::endl;

                // Выводим и обнуляем все ненулевые элементы над найденным элементом
                for (int k = 0; k < i; k++) {
                    if (arr[k][j] != 0) {
                        outputFile << "# Element above: " << arr[k][j] << std::endl;
                        outputFile << "# Clearing the top of " << target << std::endl;
                        outputFile << "# Grasping " << arr[k][j] << std::endl;
                        outputFile << "# Getting rid of " << arr[k][j] << std::endl;
                        outputFile << "# Putting on table cube " << arr[k][j] << std::endl;
                        arr[k][j] = 0; // Превращаем в ноль
                        found = true;
                    }
                }

                // Если не было ненулевых элементов над найденным элементом
                if (!found) {
                    outputFile << "# There are no non-zero elements above it." << std::endl;
                }

                // Закрываем файл
                std::cout.rdbuf(coutbuf);
                outputFile.close();
                return true;
            }
        }
    }

    outputFile << "# Element " << target << " not found in the matrix." << std::endl;

    std::cout.rdbuf(coutbuf);
    // Закрываем файл
    outputFile.close();
    return false;
}

void moveElementToTop(int r, int c, std::vector<std::vector<int>>& arr, int target, int columnNumber) {
    // Ищем элемент target
    outputFile.open("output.txt", std::ios::app);
    int initialRow, initialColumn, n = 1;

    for (int i = 0; i < r + 2; i++) {
        for (int j = 0; j < c + 2; j++) {
            if (arr[i][j] == target) {
                initialRow = i;
                initialColumn = j;
                break;
            }
        }
    }

    // Проверка на то, не пытается ли пользователь переместить элемент туда же
    if (initialColumn == columnNumber) {
        std::cout << std::endl << "# Element " << target << " is already at the top of column "
                  << columnNumber << "." << std::endl;
        return;
    }
    // Перенос, когда ниже есть нули
    else if (arr[2][columnNumber] == 0) {
        // Помещаю элемент на верхкушку нужного столбца
        std::swap(arr[initialRow][initialColumn], arr[1][columnNumber]);
        // Двигаю его вниз по столбцу пока не наткнусь на любое ненулевое число
        while (n != r + 1){
            if (arr[n + 1][columnNumber] == 0) {
                std::swap(arr[n][columnNumber], arr[n + 1][columnNumber]);
            } else {
                // Используйте outputFile с флагом std::ios::app для записи в конец файла
                outputFile.open("output.txt", std::ios::app);
                if (outputFile.is_open()) {
                    outputFile << "# Grasping " << target << std::endl;
                    outputFile << "# Putting at the top of " << columnNumber << " column cube " << target << std::endl;
                    break;
                }
                else {
                    std::cerr << "Unable to open output.txt" << std::endl;
                }
            }
            n++;
        }
    }
    // Самый просто способ перемещения, без нюансов
    else {
        std::swap(arr[initialRow][initialColumn], arr[1][columnNumber]);
        // Используйте outputFile с флагом std::ios::app для записи в конец файла
        outputFile.open("output.txt", std::ios::app);
        if (outputFile.is_open()) {
            outputFile << "# Grasping " << target << std::endl;
            outputFile << "# Putting at the top of " << columnNumber << " column cube " << target << std::endl;
            outputFile.close();
        }
        else {
            std::cerr << "Unable to open output.txt" << std::endl;
        }
    }

    std::cout << std::endl << "# Element " << target << " moved to the top of column "
                << columnNumber << "." << std::endl;
}

// Вывод данных матрицы
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << std::endl << "Final matrix:" << std::endl;
    for (const auto& row : matrix) {
        for (int elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    // Задаем размеры двумерного массива
    int rows, columns, cubeNumber, columnNumber;

    std::cout << "Please enter matrix dimensions" << std::endl;
    std::cout << "Number of rows:";
    std::cin >> rows;
    std::cout << "Number of columns:";
    std::cin >> columns;
    std::cout << std::endl;

    // Checking if the files are successfully opened
    if (!outputFile.is_open()) {
        std::cerr << "Error opening input or output file." << std::endl;
        return 0;
    }

    // Создание и ввод элементов матрицы с проверкой уникальности
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns));

    // Заполнение матрицы элементами с клавиатуры
    fillingMatrix(rows, columns, matrix);

    // Добавляет нулевые строки и столбцы
    addingZeroes(columns, matrix);

    beautifulMatrix(rows, columns, matrix);

    // Вывод итоговой матрицы
    printMatrix(matrix);

    std::cout << std::endl << "Write number of cube you want to take:";
    std::cin >> cubeNumber;
    std::cout << std::endl << "Write row number where to place cube " << cubeNumber << ":";
    std::cin >> columnNumber;
    std::cout << std::endl;

    if (columnNumber > rows + 2) {
        std::cerr << std::endl << "Error! You entered wrong number of rows!" << std::endl;
        return 0;
    }

    searchAndClearTop(rows, columns, matrix, cubeNumber);

    printMatrix(matrix);

    moveElementToTop(rows, columns, matrix, cubeNumber, columnNumber);

    printMatrix(matrix);

    while (true) {
        std::string cmd;
        std::cout << "> ";
        std::getline(std::cin, cmd);

        if (cmd == "quit") {
            break;
        }
        else {
            // Передаем введенную команду в ваш обработчик командной строки
            cmdHandler(cmd, cubeNumber, columnNumber);
        }
    }

    // Для очистки памяти вектор достаточно просто вызвать его деструктор
    matrix.clear();

    return 0;
}
