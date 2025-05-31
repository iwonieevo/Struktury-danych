#include "../headers/AVLTree.h"

AVLTree::AVLTree() {
    root = nullptr;
}

void AVLTree::destroy(AVLNode *node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

AVLTree::~AVLTree() {
    destroy(root);
}

size_t AVLTree::get_height(AVLNode* node) {
    return node ? node->height : 0;
}

AVLNode* AVLTree::rotate_right(AVLNode *node) {
    AVLNode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;
    return temp;
}

AVLNode* AVLTree::rotate_left(AVLNode *node) {
    AVLNode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    temp->height = max(get_height(temp->left), get_height(temp->right)) + 1;
    return temp;
}

int8_t AVLTree::balance_factor(AVLNode* node) {
    return node ? static_cast<int8_t>(get_height(node->left) - get_height(node->right)) : 0;
}

AVLNode* AVLTree::balance_tree(AVLNode *node) {
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
    int8_t balance = balance_factor(node);

    if (balance > 1 && balance_factor(node->left) >= 0) {
        return rotate_right(node);
    }
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    if (balance < -1 && balance_factor(node->right) <= 0) {
        return rotate_left(node);
    }
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

AVLNode* AVLTree::insert_node(AVLNode* node, const std::string& key, int value) {
    if (!node) {
        return new AVLNode(key, value);
    }
    if (key < node->key) {
        node->left = insert_node(node->left, key, value);
    }else if (key > node->key) {
        node->right = insert_node(node->right, key, value);
    }else {
        node->value = value;
    }

    return balance_tree(node);
}

void AVLTree::insert(const std::string& key, int value) {
    root = insert_node(root, key, value);
}

AVLNode* AVLTree::remove_node(AVLNode* node, const std::string& key, int& removed_value) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = remove_node(node->left, key, removed_value);
    } else if (key > node->key) {
        node->right = remove_node(node->right, key, removed_value);
    } else {
        removed_value = node->value;
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        } else {
            AVLNode* temp = node;
            while (temp && temp->left) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove_node(node->right, temp->key, removed_value);
        }
    }

    return balance_tree(node);
}

int AVLTree::remove(const std::string& key) {
    int removed_value = INT_MIN;
    root = remove_node(root, key, removed_value);
    return removed_value;
}

AVLNode* AVLTree::find_node(AVLNode* node, const std::string& key) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        return find_node(node->left, key);
    }else if (key > node->key) {
        return find_node(node->right, key);
    }else {
        return node;
    }
}

Node* AVLTree::find(const std::string& key) {
    return find_node(root, key);
}

void AVLTree::print_in_order(AVLNode* node) {
    if (!node) {
        return;
    }
    print_in_order(node->left);
    std::cout << node->key << ": " << node->value << std::endl;
    print_in_order(node->right);
}

void AVLTree::print(void) {
    print_in_order(root);
}
