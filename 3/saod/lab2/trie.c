#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
    char value;
    struct trie* children;
    struct trie* next;
    int is_end_of_word;
};

struct trie* trie_create() {
    struct trie* node = (struct trie*)malloc(sizeof(struct trie));
    node->value = '\0';
    node->children = NULL;
    node->next = NULL;
    node->is_end_of_word = 0;
    return node;
}

struct trie* trie_insert(struct trie* root, char* key) {
    if (root == NULL) {
        root = trie_create();
    }

    struct trie* current = root;

    while (*key) {
        struct trie* child = current->children;

        while (child && child->value != *key) {
            child = child->next;
        }

        if (!child) {
            struct trie *new_node = trie_create();
            new_node->value = *key;

            new_node->next = current->children;
            current->children = new_node;
            child = new_node;
        }

        current = child;
        key++;
    }

    current->is_end_of_word = 1;
    return root;
}

struct trie* trie_lookup(struct trie* root, char* key) {
    struct trie* current = root;

    while (*key && current) {
        struct trie* child = current->children;

        while (child && child->value != *key) {
            child = child->next;
        }

        if (!child) {
            return NULL;
        }

        current = child;
        key++;
    }

    return (current && current->is_end_of_word) ? current : NULL;
}

struct trie* trie_delete(struct trie* root, char* key) {
    if (!root) return NULL;

    if (*key == '\0') {
        if (root->is_end_of_word) {
            root->is_end_of_word = 0;
        }
        return root;
    }

    struct trie* child = root->children;
    struct trie* prev = NULL;

    while (child && child->value != *key) {
        prev = child;
        child = child->next;
    }

    if (child) {
        trie_delete(child, key + 1);

        if (child->children == NULL && !child->is_end_of_word) {
            if (prev) {
                prev->next = child->next;
            } else {
                root->children = child->next;
            }
            free(child);
        }
    }

    return root;
}

void trie_print_with_branches(struct trie* root, int level, int is_last, int *branch_track) {
    if (!root) return;

    struct trie *child = root->children;
    
    if (level > 0) {
        for (int i = 0; i < level - 1; i++) {
            if (branch_track[i]) {
                printf("│   ");
            } else {
                printf("    ");
            }
        }
        if (is_last) {
            printf("└── ");
        } else {
            printf("├── ");
        }
    }

    if (root->value != '\0') {
        printf("%c", root->value);
        if (root->is_end_of_word) {
            printf(" (leaf)");
        }
        printf("\n");
    }

    int next_level = level + 1;
    while (child) {
        branch_track[level] = (child->next != NULL);  // Определяем, продолжать ли рисовать вертикальные линии на этом уровне
        trie_print_with_branches(child, next_level, child->next == NULL, branch_track);
        child = child->next;
    }
}

void trie_print_to_file_with_branches(struct trie* root, int level, int is_last, int *branch_track, FILE* file) {
    if (!root) return;

    struct trie *child = root->children;

    if (level > 0) {
        for (int i = 0; i < level - 1; i++) {
            if (branch_track[i]) {
                fprintf(file, "│   ");
            } else {
                fprintf(file, "    ");
            }
        }
        if (is_last) {
            fprintf(file, "└── ");
        } else {
            fprintf(file, "├── ");
        }
    }

    if (root->value != '\0') {
        fprintf(file, "%c", root->value);
        if (root->is_end_of_word) {
            fprintf(file, " (leaf)");
        }
        fprintf(file, "\n");
    }

    int next_level = level + 1;
    while (child) {
        branch_track[level] = (child->next != NULL);  // Продолжать ли вертикальные линии
        trie_print_to_file_with_branches(child, next_level, child->next == NULL, branch_track, file);
        child = child->next;
    }
}

int main() {
    struct trie *root = trie_create();

    root = trie_insert(root, "apple");
    root = trie_insert(root, "banana");
    root = trie_insert(root, "grape");
    root = trie_insert(root, "orange");
    root = trie_insert(root, "mango");
    root = trie_insert(root, "melon");
    root = trie_insert(root, "berry");
    root = trie_insert(root, "cherry");
    root = trie_insert(root, "lemon");
    root = trie_insert(root, "lime");

    printf("Содержимое дерева после вставки:\n");
    int branch_track[100] = {0};
    trie_print_with_branches(root, 0, 1, branch_track);

    FILE *file = fopen("trie_structure.txt", "w");
    if (file) {
        fprintf(file, "Содержимое дерева:\n");
        trie_print_to_file_with_branches(root, 0, 1, branch_track, file);
        fclose(file);
        printf("\nСтруктура дерева сохранена в 'trie_structure.txt'.\n");
    } else {
        printf("Не удалось открыть файл для записи.\n");
    }

    return 0;
}
