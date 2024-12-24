#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Node {
    int value;
    int level;
    Node* left;
    Node* right;
    
    Node(int v) : value(v), level(1), left(nullptr), right(nullptr) {}
};

Node* root = nullptr;
int addSteps = 0;
int deleteSteps = 0;
int searchSteps = 0;
int skewSteps = 0;
int splitSteps = 0;

Node* skew(Node* node) {
    if (node == nullptr || node->left == nullptr) return node;
    if (node->left->level == node->level) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }
    return node;
}

Node* split(Node* node) {
    if (node == nullptr || node->right == nullptr || node->right->right == nullptr) return node;
    if (node->level == node->right->right->level) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        right->level++;
        return right;
    }
    return node;
}

Node* insert(Node* node, int value) {
    if (node == nullptr) return new Node(value);
    if (value < node->value) {
        node->left = insert(node->left, value);
    } else if (value > node->value) {
        node->right = insert(node->right, value);
    }
    node = skew(node);
    node = split(node);
    return node;
}

Node* remove(Node* node, int value) {
    if (node == nullptr) return nullptr;
    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            node->value = successor->value;
            node->right = remove(node->right, successor->value);
        }
    }
    if (node != nullptr) {
        if (node->left == nullptr || node->right == nullptr) {
            node->level = 1;
        } else {
            node->level = std::min(node->left->level, node->right->level) + 1;
        }
        node = skew(node);
        node = split(node);
    }
    return node;
}

Node* search(Node* node, int value) {
    if (node == nullptr || node->value == value) {
        return node;
    }
    if (value < node->value) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

int calculateTreeHeight(Node* node) {
    if (node == nullptr) return 0;
    return 1 + std::max(calculateTreeHeight(node->left), calculateTreeHeight(node->right));
}

void runExperiment(int maxSize, int stepSize) {
    std::ofstream addFile("add_times.txt");
    std::ofstream removeFile("remove_times.txt");
    std::ofstream searchFile("search_times.txt");
    std::ofstream stepsFile("steps_count.txt");

    if (!addFile.is_open() || !removeFile.is_open() || !searchFile.is_open() || !stepsFile.is_open()) {
        std::cerr << "Error opening output files.\n";
        return;
    }

    std::cout << std::left << std::setw(10) << "Size"
              << std::setw(20) << "Insert Time (ns)"
              << std::setw(20) << "Search Time (ns)"
              << std::setw(20) << "Delete Time (ns)"
              << std::endl;
    std::cout << std::string(95, '-') << std::endl;

    for (int size = 100000; size <= maxSize; size += stepSize) {
        // Perform multiple runs and average results to smooth out irregularities
        int runs = 10;
        double avgInsertTime = 0;
        double avgSearchTime = 0;
        double avgDeleteTime = 0;
        double avgInsertSteps = 0;
        double avgSearchSteps = 0;
        double avgDeleteSteps = 0;
        int treeHeight = 0;

        for (int run = 0; run < runs; ++run) {
            // Initialize tree with `size` elements using random values
            root = nullptr;
            addSteps = deleteSteps = searchSteps = 0;

            for (int i = 0; i < size; ++i) {
                int value = rand() % (size * 10);
                root = insert(root, value);
            }

            // Measure add time
            double totalAddSteps = 0;
            auto startAdd = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; ++i) {
                int valueToAdd = rand() % (size * 10);
                addSteps = 0; // Reset add steps for each individual insertion
                root = insert(root, valueToAdd);
                totalAddSteps += addSteps;
            }
            auto endAdd = std::chrono::high_resolution_clock::now();
            auto elapsedAdd = std::chrono::duration_cast<std::chrono::nanoseconds>(endAdd - startAdd);
            avgInsertTime += elapsedAdd.count() / 10000.0;
            avgInsertSteps += totalAddSteps / 10000.0;

            // Measure search time
            double totalSearchSteps = 0;
            auto startSearch = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; ++i) {
                int valueToSearch = rand() % size;
                searchSteps = 0; // Reset search steps for each individual search
                search(root, valueToSearch);
                totalSearchSteps += searchSteps;
            }
            auto endSearch = std::chrono::high_resolution_clock::now();
            auto elapsedSearch = std::chrono::duration_cast<std::chrono::nanoseconds>(endSearch - startSearch);
            avgSearchTime += elapsedSearch.count() / 10000.0;
            avgSearchSteps += totalSearchSteps / 10000.0;

            // Measure remove time
            double totalDeleteSteps = 0;
            auto startRemove = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; ++i) {
                int valueToRemove = rand() % size;
                deleteSteps = 0; // Reset delete steps for each individual removal
                root = remove(root, valueToRemove);
                totalDeleteSteps += deleteSteps;
            }
            auto endRemove = std::chrono::high_resolution_clock::now();
            auto elapsedRemove = std::chrono::duration_cast<std::chrono::nanoseconds>(endRemove - startRemove);
            avgDeleteTime += elapsedRemove.count() / 10000.0;
            avgDeleteSteps += totalDeleteSteps / 10000.0;

            // Calculate tree height for the last run
            if (run == runs - 1) {
                treeHeight = calculateTreeHeight(root);
            }
        }

        // Average the results over all runs
        avgInsertTime /= runs;
        avgSearchTime /= runs;
        avgDeleteTime /= runs;
        avgInsertSteps /= runs;
        avgSearchSteps /= runs;
        avgDeleteSteps /= runs;

        // Write results to files
        addFile << size << " " << std::fixed << avgInsertTime << "\n";
        searchFile << size << " " << std::fixed << avgSearchTime << "\n";
        removeFile << size << " " << std::fixed << avgDeleteTime << "\n";

        // Display data for current size
        std::cout << std::setw(10) << size
                  << std::setw(20) << avgInsertTime
                  << std::setw(20) << avgSearchTime
                  << std::setw(20) << avgDeleteTime
                  << std::endl;
    }

    addFile.close();
    removeFile.close();
    searchFile.close();
    stepsFile.close();
}

int main() {
    runExperiment(1000000, 50000);
    return 0;
}
