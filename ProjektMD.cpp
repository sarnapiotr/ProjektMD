#include <iostream>
#include <vector>
#include <stack>

void chooseGraphMatrix(int**& graphMatrix, int& vertexCount) {
    std::cout << "Wybierz graf do pokolorowania: \n";
    std::cout << "1. Graf 3-wierzcholkowy\n";
    std::cout << "2. Graf 5-wierzcholkowy\n";
    std::cout << "3. Graf 10-wierzcholkowy\n";

    int choice{ 0 };
    std::cin >> choice;

    switch (choice) {
    case 1:
        vertexCount = 3;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1},
                new int[vertexCount] {1, 0, 1},
                new int[vertexCount] {1, 1, 0}};
        break;
    case 2:
        vertexCount = 5;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1, 1, 1},
                new int[vertexCount] {1, 0, 1, 1, 1},
                new int[vertexCount] {1, 1, 0, 1, 0},
                new int[vertexCount] {1, 1, 1, 0, 1},
                new int[vertexCount] {1, 1, 0, 1, 0}};
        break;
    case 3:
        vertexCount = 10;
        graphMatrix = new int* [vertexCount] {
            new int[vertexCount] {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
                new int[vertexCount] {1, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                new int[vertexCount] {1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                new int[vertexCount] {1, 1, 1, 0, 1, 1, 0, 0, 0, 0},
                new int[vertexCount] {1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
                new int[vertexCount] {0, 0, 0, 1, 0, 0, 1, 1, 0, 0},
                new int[vertexCount] {0, 0, 0, 0, 1, 1, 0, 1, 1, 0},
                new int[vertexCount] {0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
                new int[vertexCount] {0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
                new int[vertexCount] {0, 0, 0, 0, 0, 0, 0, 1, 1, 0}};
        break;
    default:
        std::cout << "Niepoprawny wybor\n";
        return;
    }
}

void printGraph(int**& graphMatrix, const int& vertexCount) {
    for (int i = 0; i < vertexCount; i++) {
        for (int j = 0; j < vertexCount; j++) {
            std::cout << graphMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void printBacktrackColoring(const std::vector<int>& colors) {
    for (int i = 0; i < colors.size(); i++) {
        std::cout << "Wierzcholek " << i << " Kolor " << colors[i] << std::endl;
    }
}

bool isSafe(int**& graphMatrix, const int& vertexCount, const std::vector<int>& colors, const int& vertex, const int& color) {
    for (int i = 0; i < vertexCount; i++) {
        if (graphMatrix[vertex][i] == 1 && colors[i] == color) {
            return false;
        }
    }
    return true;
}

bool allColored(std::vector<int>& colors, std::stack<int>& vertexStack) {
    for (int i = 0; i < colors.size(); i++) {
        if (colors[i] == 0) {
            vertexStack.push(i);
            colors[i] = 1;
            return false;
        }
    }
    return true;
}

bool boolBacktrackGraphColoring(int**& graphMatrix, const int& vertexCount, const int& maxColors, std::vector<int>& colors) {
    std::stack<int> vertexStack;
    int currentVertex{ 0 };
    colors[currentVertex] = 1;
    vertexStack.push(currentVertex);

    while (!vertexStack.empty()) {
        currentVertex = vertexStack.top();
        bool colored = false;

        for (int newColor = colors[currentVertex]; newColor <= maxColors; newColor++) {
            if (isSafe(graphMatrix, vertexCount, colors, currentVertex, newColor)) {
                colors[currentVertex] = newColor;
                colored = true;
                break;
            }
        }

        if (colored) {
            if (allColored(colors, vertexStack)) {
                return true;
            }
        }
        else {
            colors[currentVertex] = 0;
            vertexStack.pop();
        }
    }

    return false;
}

void backtrackGraphColoring(int**& graphMatrix, const int& vertexCount, const int& maxColors) {
    std::vector<int> colors(vertexCount, 0);

    if (boolBacktrackGraphColoring(graphMatrix, vertexCount, maxColors, colors)) {
        printBacktrackColoring(colors);
    }
    else {
        std::cout << "Nie mozna pokolorowac grafu przy uzyciu " << maxColors << " kolorow\n";
    }
}

int main()
{
    std::cout << "Projekt MD Piotr Sarna - Kolorowanie grafow\n";

    int** graphMatrix{ nullptr };
    int vertexCount{ 0 };

    chooseGraphMatrix(graphMatrix, vertexCount);
    printGraph(graphMatrix, vertexCount);

    std::cout << "1. Algorytm z nawrotami\n";
    std::cout << "2. Algorytm DSATUR\n";
    std::cout << "3. Algorytm T-DSATUR\n";
    std::cout << "Wybierz algorytm: \n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        int maxColors{ 0 };

        std::cout << "Podaj maksymalna liczbe kolorow: \n";
        std::cin >> maxColors;

        backtrackGraphColoring(graphMatrix, vertexCount, maxColors);
    }
    else if (choice == 2) {
        
    }
    else if (choice == 3) {

    }
    else {
        std::cout << "Niepoprawny wybor\n";
        for (int i = 0; i < vertexCount; i++) {
            delete[] graphMatrix[i];
        }
        delete[] graphMatrix;
        return -1;
    }

    for (int i = 0; i < vertexCount; i++) {
        delete[] graphMatrix[i];
    }
    delete[] graphMatrix;

    return 0;
}
