#pragma once
#include "Bucket.h"
#include "utility.h"
#include <iostream>

struct AVLNode : public Node {
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    size_t height = 1;

    AVLNode(const std::string& k, int v) : Node(k, v) {}
};

class AVLTree : public Bucket {
private:
    AVLNode* root = nullptr;

    void destroy(AVLNode *node);
    size_t get_height(AVLNode *node);
    AVLNode* rotate_right(AVLNode *node);
    AVLNode* rotate_left(AVLNode *node);
    int8_t balance_factor(AVLNode *node);
    AVLNode* balance_tree(AVLNode *node);
    AVLNode* insert_node(AVLNode* node, const std::string& key, int value);
    AVLNode* remove_node(AVLNode* node, const std::string& key, int& removed_value);
    AVLNode* find_node(AVLNode* node, const std::string& key);
    void print_in_order(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(const std::string& key, int value) override;
    int remove(const std::string& key) override;
    Node* find(const std::string& key) override;
    void print(void) override;
};