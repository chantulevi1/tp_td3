#include <iostream>

using namespace std;

// Nodo de un arbol binario
struct nodo {
   int elem;
   nodo *izq, *der;
};

bool es_primo(int N) {
  int i=0;
  while(i<N){
    if((i%N)==0){
      return false;
    }
    return true;
  }
}

int minimo_divisor(int N) {
    while(int i=0 && (i<N)) {
        if (i%N){
        return i;
    }
}
}


// Descompone N en un arbol de divisores
nodo* descomponer(int N) {
  // Pre: N>1
  struct nodo {
int elem;
nodo* izquierdo = nullptr;
nodo* derecho = nullptr;
nodo* raiz = ({N,nullptr,nullptr}) ;
}

  if (es_primo(N)==true){
   return raiz;
  }
  else
  raiz->izq= new nodo(minimo_divisor(N), nullptr, nullptr);
  raiz->der= new nodo(minimo_divisor(N/minimo_divisor(N)), nullptr, nullptr);
  
}

void print_inorder(nodo* n) {
    if (n == nullptr) return;

    print_inorder(n->izq);
    std::cout << n->elem << " ";
    print_inorder(n->der);
}

void destruir(nodo* n) {
    if (n == nullptr) return;
    destruir(n->izq);
    destruir(n->der);
    delete n;
}

  int main() {
      nodo* raiz = descomponer(2310);
      cout << "inorder: ";
      print_inorder(raiz);
      destruir(raiz);
  }