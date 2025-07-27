#include <iostream>
#include <random>
#include <chrono>
#include "AVLTree.cpp"
#include <ctime>

using namespace std;

int main() {
    AVLTree tree;

    // Inicializa randomizador para IDs
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1000, 999999);

    // Inserção das 5000 transações
    for (int time = 0; time < 5000; ++time) {
        int id = distrib(gen);
        tree.root = tree.insert(tree.root, time, id);
    }

    // Após todas as inserções, imprime a altura (altura da raiz)
    cout << "Altura da arvore AVL após 5000 insercoes: " << tree.height(tree.root) << endl;

    // Busca das chaves especificadas e medição do tempo
    int queries[] = {100, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 4999};
    const int n_queries = sizeof(queries) / sizeof(queries[0]);

    auto inicioBusca = chrono::high_resolution_clock::now();

    for (int i = 0; i < n_queries; ++i) {
       AVLTree::Node* res = tree.search(tree.root, queries[i]); // Supondo método search(Node*, int)
        if (res)
            cout << "Chave " << queries[i] << " encontrada. id = " << res->id << endl;
        else
            cout << "Chave " << queries[i] << " NAO encontrada!" << endl;
    }

    auto fimBusca = chrono::high_resolution_clock::now();
    auto duracaoBusca = chrono::duration_cast<chrono::microseconds>(fimBusca - inicioBusca);

    cout << "Tempo total gasto para buscar todas as chaves: "
         << duracaoBusca.count() << " microssegundos" << endl;

    // Remoção das transações com tempo de 0 a 500
    auto inicioRemocao = chrono::high_resolution_clock::now();

    for (int t = 0; t <= 500; ++t) {
        tree.root = tree.remove(tree.root, t); // Supondo método remove(Node*, int)
    }

    auto fimRemocao = chrono::high_resolution_clock::now();
    auto duracaoRemocao = chrono::duration_cast<chrono::microseconds>(fimRemocao - inicioRemocao);

    cout << "Tempo total gasto para remover as chaves de 0 a 500: "
         << duracaoRemocao.count() << " microssegundos" << endl;

    // Após as remoções, imprime a altura da nova árvore
    cout << "Altura da arvore AVL apos remocao das transacoes antigas: "
         << tree.height(tree.root) << endl;

    // Exibição ordenada das transações restantes (ordem cronológica)
    cout << "Transacoes remanescentes em ordem cronologica:" << endl;
    cout << "Descomentar a linha ***** para ver o percurso in-order ";
  //  tree.printInOrder(tree.root);


    return 0;
}
