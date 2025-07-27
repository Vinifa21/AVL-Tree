

class AVLTree {
public:
    struct Node {
        int time;    // chave primária: incremental, determina ordem
        int id;      // identificador da transação
        Node* left;
        Node* right;
        int height;

        Node(int t, int i) : time(t), id(i), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    AVLTree() : root(nullptr) {}

    int height(Node* n) {
        return n ? n->height : 0;
    }

    void updateHeight(Node* n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }

    int balanceFactor(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* insert(Node* node, int time, int id) {
        if (!node) return new Node(time, id);
        if (time < node->time)
            node->left = insert(node->left, time, id);
        else if (time > node->time)
            node->right = insert(node->right, time, id);
        else
            return node; // Não insere duplicatas de time

        updateHeight(node);

        int balance = balanceFactor(node);

        // Rotação simples à esquerda
        if (balance < -1 && time > node->right->time)
            return leftRotate(node);

        // Rotação simples à direita
        if (balance > 1 && time < node->left->time)
            return rightRotate(node);

        // Direita-Esquerda
        if (balance < -1 && time < node->right->time) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Esquerda-Direita
        if (balance > 1 && time > node->left->time) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        return node;
    }
    // Inserção facilitada (gera id aleatório automaticamente)
    void insertAuto(int time) {
        int id = getRandomID();
        root = insert(root, time, id);
    }

    Node* search(Node* node, int time) {
        if (!node) return nullptr;
        if (time < node->time) return search(node->left, time);
        else if (time > node->time) return search(node->right, time);
        else return node;
    }
    Node* search(int time) {
        return search(root, time);
    }

    // Menor valor (usado na remoção)
    Node* minValueNode(Node* node) {
        Node* cur = node;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    Node* remove(Node* node, int time) {
        if (!node) return node;

        if (time < node->time)
            node->left = remove(node->left, time);
        else if (time > node->time)
            node->right = remove(node->right, time);
        else {
            if (!node->left || !node->right) {
                Node* tmp = node->left ? node->left : node->right;
                delete node;
                return tmp;
            } else {
                Node* tmp = minValueNode(node->right);
                node->time = tmp->time;
                node->id = tmp->id;
                node->right = remove(node->right, tmp->time);
            }
        }
        updateHeight(node);
        int balance = balanceFactor(node);

        // Rotação simples à esquerda
        if (balance < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);

        // Direita-Esquerda
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Rotação simples à direita
        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);

        // Esquerda-Direita
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        return node;
    }

    void removeRange(int t0, int t1) {
        for (int i = t0; i <= t1; ++i) {
            root = remove(root, i);
        }
    }

    void printInOrder(Node* node) {
        if (node) {
            printInOrder(node->left);
            std::cout << "[time: " << node->time << " | id: " << node->id << "] ";
            printInOrder(node->right);
        }
    }
    void printAll() {
        printInOrder(root);
        std::cout << std::endl;
    }

    // Função para medir altura da árvore
    int rootHeight() {
        return height(root);
    }

    // Utilitário para gerar id aleatório
    int getRandomID() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1000, 999999);
        return dis(gen);
    }
};
