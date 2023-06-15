#include "Editor.h"
#include <string>
#include<vector>
#include <sstream>

using namespace std;
using std::string;
using std::istringstream;
using std::string;


Editor::Editor(const set<string> & conectivos) {
}

string Editor::texto() const {
   vector<std::string> _texto;
    std::istringstream iss(texto);
    while (iss >> (std::string palabra)) {
            _texto.push_back(palabra);
    }
    
    this->palabras = _texto;
    return this->texto;
}

const set<string>& Editor::vocabulario() const {
    return vocabulario;
}

const set<string>& Editor::conectivos() const {
    
    return conectivos;
}

int Editor::conteo_palabras() const { 
    /* Quitar este código y completar */
    return  (longitud - conectivos.size()); 
}

int Editor::longitud() const { 
	return longitud ; 
}

void Editor::agregar_atras(const string& oracion) {
    if(texto.end()){
        texto.push_back(oracion)
    }
}
const set<int> & Editor::buscar_palabra(const string& palabra) const {
    //busqueda_binaria???
    return set_int_vacio;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    texto[pos].push_back(oracion);
}

void Editor::borrar_posicion(int pos) {
        _texto.erase(_texto.begin() + pos);
   
}


int Editor::borrar_palabra(const string& palabra) {
    
    int borrar_palabra(const std::string& palabra) {
        int count = 0;
        auto it = _texto.begin();
        while (it != _texto.end()) {
            if (*it == palabra) {
                it = _texto.erase(it);
                ++count;
            } else {
                ++it;
            }
        }
        return count;
    }
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    /* Completar */
}
