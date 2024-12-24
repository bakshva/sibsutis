#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream> // Для работы с файлами

using namespace std;

enum Color
{
    RED,
    BLACK
};

struct rbtree
{
    int key;
    char *value;
    Color color;
    struct rbtree *left;
    struct rbtree *right;
    struct rbtree *parent;
};

// Вспомогательные функции для работы с красно-чёрным деревом

struct rbtree *create_node(int key, char *value, Color color, struct rbtree *parent)
{
    struct rbtree *node = (struct rbtree *)malloc(sizeof(struct rbtree));
    node->key = key;
    node->value = strdup(value);
    node->color = color;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;
    return node;
}

struct rbtree *rotate_left(struct rbtree *root, struct rbtree *x)
{
    struct rbtree *y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

struct rbtree *rotate_right(struct rbtree *root, struct rbtree *y)
{
    struct rbtree *x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;

    return root;
}

struct rbtree *fix_insert(struct rbtree *root, struct rbtree *node)
{
    struct rbtree *parent = nullptr;
    struct rbtree *grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED))
    {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            struct rbtree *uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    root = rotate_left(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                root = rotate_right(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
        else
        {
            struct rbtree *uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    root = rotate_right(root, parent);
                    node = parent;
                    parent = node->parent;
                }

                root = rotate_left(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }

    root->color = BLACK;
    return root;
}

struct rbtree *rbtree_add(struct rbtree *root, int key, char *value)
{
    struct rbtree *node = create_node(key, value, RED, nullptr);
    struct rbtree *parent = nullptr;
    struct rbtree *current = root;

    while (current != nullptr)
    {
        parent = current;
        if (node->key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;

    if (parent == nullptr)
        root = node;
    else if (node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;

    root = fix_insert(root, node);
    return root;
}

struct rbtree *rbtree_lookup(struct rbtree *root, int key)
{
    if (root == nullptr || root->key == key)
    {
        return root;
    }
    if (key < root->key)
    {
        return rbtree_lookup(root->left, key);
    }
    return rbtree_lookup(root->right, key);
}

struct rbtree *rbtree_min(struct rbtree *root)
{
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root;
}

struct rbtree *rbtree_max(struct rbtree *root)
{
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root;
}

struct rbtree *rbtree_delete(struct rbtree *root, int key)
{
    return root;
}

void rbtree_free(struct rbtree *root)
{
    if (root != nullptr)
    {
        rbtree_free(root->left);
        rbtree_free(root->right);
        free(root->value);
        free(root);
    }
}

void rbtree_print_dfs(struct rbtree *root, ofstream &file, int space = 0, int height = 10)
{
    if (root == nullptr)
    {
        return;
    }

    space += height;

    rbtree_print_dfs(root->right, file, space);

    for (int i = height; i < space; i++)
        file << " ";
    file << root->key << (root->color == RED ? "(R)" : "(B)") << endl;

    rbtree_print_dfs(root->left, file, space);
}

// Функция для вычисления высоты дерева
int rbtree_height(struct rbtree *root)
{
    if (root == nullptr)
    {
        return 0;
    }
    int left_height = rbtree_height(root->left);
    int right_height = rbtree_height(root->right);
    return max(left_height, right_height) + 1;
}

int main()
{
    struct rbtree *root = nullptr;

    // Открытие файла для записи высоты дерева
    ofstream height_file("tree_height_data.txt");
    if (!height_file.is_open())
    {
        cout << "Не удалось открыть файл для записи!" << endl;
        return 1;
    }

    // Добавление элементов от 1000 до 50000 с шагом в 1000
    for (int i = 1000; i <= 50000; i += 1000)
    {
        // Вставка элементов
        for (int j = (i - 999); j <= i; ++j)
        {
            char val[10];
            snprintf(val, 10, "val%d", j);
            root = rbtree_add(root, j, val);
        }

        // Вычисление высоты дерева
        int height = rbtree_height(root);

        // Запись количества элементов и высоты дерева в файл
        height_file << i << " " << height << endl;

        // Открытие файла для записи структуры дерева
        string filename = "tree_structure_" + to_string(i) + ".txt";
        ofstream tree_file(filename);
        if (tree_file.is_open())
        {
            tree_file << "Дерево при " << i << " элементах:" << endl;
            rbtree_print_dfs(root, tree_file);
            tree_file.close();
        }
        else
        {
            cout << "Не удалось открыть файл для записи структуры дерева!" << endl;
        }
    }

    // Закрытие файла с данными о высоте
    height_file.close();

    // Освобождение памяти
    rbtree_free(root);

    return 0;
}
