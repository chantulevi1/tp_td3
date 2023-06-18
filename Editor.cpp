#include "Editor.h"
#include <string>
#include<vector>
#include <sstream>

using namespace std;
using std::string;
using std::istringstream;
using std::string;
using std::set;

Editor::Editor(const set<string> & conectivos) {
    _conteo_palabras = 0;
    this->_texto;
    _longitud = 0;
    conectivos;
    
    // Utilizar la función dividir Texto para obtener el vector de palabras a partir del texto vacío
    std::string textoVacio;
    std::vector<std::string> palabras;

    // Inicializar el vector _texto con las palabras obtenidas
    _texto = palabras;
}

string Editor::texto() const {
    int i=0;
    string texto = "";
    if (this->_texto.size()!= 0) {
        while(i < this->_texto.size()){
            texto = texto + this->_texto[i] + " ";
        }
        if (!texto.empty()) {  //si texto no esta vacio, saca el utlimo espacio
            texto.pop_back();  
        }
        return texto;
    }

    return "";
}

const set<string>& Editor::vocabulario() const {
    return this->_vocabulario;
}

const set<string>& Editor::conectivos() const {
    
    return this->_conectivos;
}

int Editor::conteo_palabras() const { 
    /* Quitar este código y completar */
    return this->_conteo_palabras; 
}

int Editor::longitud() const { 
	return this->_longitud; 
}

vector<string> dividirTexto(const string texto) {
    vector<string> palabras;
    char space = ' ';
    int start = 0;
    int actual = 0;
    string palabraActual = "";
    for (int i = 0; i < texto.length() ; i++) {
        if ((texto[i] == space || i == texto.length() - 1) && i != 0) {
            palabraActual = texto.substr(start, i - 1 - start);
            palabras.push_back(palabraActual);
            start = i + 1;
        }
    }

    return palabras;
    }

void Editor::agregar_atras(const string& oracion) {
   
    vector<string> nuevasPalabras = dividirTexto(oracion);
    for (int i = 0; i< nuevasPalabras.size(); i++) {
        this->_texto.push_back(nuevasPalabras[i]);
    }
    
}
const set<int>& Editor::buscar_palabra(const string& palabra) const {
    set<int> emptySet;
    return emptySet;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    vector<string> nuevasPalabras = dividirTexto(oracion);
    for (int i = 0; i < nuevasPalabras.size(); i++) {
        this->_texto.insert((nuevasPalabras.begin() + pos + i), nuevasPalabras[i]);
    }
}

void Editor::borrar_posicion(int pos) {

    //Pos: 0 =< posicion =< longitud()-1
    //Post: se elimina la palabra ubicada en esa posicion del texto

    // Eliminar la palabra en la posición pos del vocabulario
    this->_vocabulario.erase(this->_texto[pos]);
    // Eliminar la posición pos de la lista de posiciones asociadas a la palabra en la posición pos del texto
    this->_posiciones[this->_texto[pos]].erase(pos);
    // Eliminar la palabra en la posición pos del texto
    this->_texto.erase(this->_texto.begin()+pos);
    // Actualizar la longitud del texto
    this->_longitud --;

    // Verificar si la palabra eliminada está en el conjunto de conectivos y actualizar la cantidad de palabras si es necesario
    if(this->_conectivos.find((this->_texto[pos]))!= this->_conectivos.end()){
        this->_cant_de_palabras --;

     // Actualizar las posiciones de las palabras que están después de la posición eliminada
    for(int i = pos; i<this->_texto.size();i++){
        set <int> posiciones = this->_posiciones[this->_texto[i]];
        for (int posicion : posiciones){
            this->_posiciones[this->_texto[i]].erase(posicion);
            this->_posiciones[this->_texto[i]].insert(posicion - 1);
        }
    }

   
}
}

int Editor::borrar_palabra(const string& palabra) {
    int i=0;
    int count =0;
    while(i<_texto.size()){
        if((_texto[i])==palabra){//operator
           _texto.erase(_texto.begin() + i);
            _conteo_palabras--;
            _longitud--;
            count++;
        }
        i++;
    }
    return count;
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    /* Completar */
}
