#include "Editor.h"
#include <string>
#include<vector>
#include <sstream>

using namespace std;
using std::string;
using std::istringstream;
using std::string;
using std::set;



Editor::Editor(const set<string> & conectivos) { //O(|conectivos|)
    //Constructor de la clase Editor

    //Pre: los strings de conectivos son palabras sin espacios ni signos de puntuacion
    //Post: construye un Editor vacio con un conjunto de conectivos dados

    // Utilizar la función obtenerPalabras para obtener el vector de palabras a partir del texto vacío
    std::string textoVacio;
    std::vector<std::string> palabras = obtenerPalabras(textoVacio);

    // Inicializar el vector _texto con las palabras obtenidas
    _texto = palabras;
    _conectivos = conectivos;
    _conteo_palabras = 0;
    _longitud = 0;

//La complejidad algorítmica es O(1) porque el tamaño del texto vacío es constante y la inicialización de los miembros de datos es una operación de tiempo constante.

}

string Editor::texto() const { //O(N) N = cant de palabras totales (inclyendo repetidas) del texto
    //Devuelve el texto completo
    string textoCompleto;
    for (const string& palabra : _texto) {
        textoCompleto += palabra + " ";
    }
    // Eliminar el último espacio en blanco agregado
    if (!textoCompleto.empty()) {
        textoCompleto.pop_back();
    }
    return textoCompleto;

}

const set<string>& Editor::vocabulario() const { //O(1)
    // Devuelve el conjunto de palabras no conectivas presentes en el texto

    //Pre: V
    //Post: devuelve por ref el cjto de todas las palabras que aparecen alguna vez en el texto y que no estan en conectivos()

    static set<string> palabrasNoConectivas;

    palabrasNoConectivas.clear();
    for (const string& palabra : _vocabulario) {
        if (_conectivos.find(palabra) == _conectivos.end()) {
            palabrasNoConectivas.insert(palabra);
        }
    }
    return palabrasNoConectivas;

// La complejidad algorítmica es O(|cantidad de palabras diferentes en el vocabulario|)
}

const set<string>& Editor::conectivos() const { //O(1)
    // Devuelve el conjunto de palabras registradas como conectivos

    //Pre: V
    //Post: devuelve por ref el cjto de palabras registradas como conectivos
    
    return this->_conectivos;

// La complejidad algorítmica es O(1) porque devuelve una referencia al conjunto _conectivos.
}

int Editor::conteo_palabras() const { //O(1)
    // Devuelve la cantidad total de palabras que aparecen en el texto (contando repeticiones), excluyendo las que están en conectivos

    //Pre: V
    //Post: devuelve cant total de palabras que aparecen en el texto (contando repeticiones), excluyendo las que esten en conectivos()

    return this->_conteo_palabras; 

 //La complejidad algorítmica es O(1) porque devuelve el valor almacenado en _conteo_palabras.
}

int Editor::longitud() const { //O(1)
    // Devuelve la cantidad total de palabras del texto (contando repeticiones)

    //Pre: V
    //Post: devuelve cant total de palabras del texto (contando repes)

	return this->_longitud; 
//La complejidad algorítmica es O(1) porque devuelve el valor almacenado en _longitud.
}


void Editor::agregar_atras(const string& oracion) { //O(|oracion| ∗ log M) M = cantidad de palabras diferentes escritas en el texto
    // Agrega todas las palabras al final del texto

    //Pre: string oracion es una secuencia de palabras separadas por un espacio, sin signos de puntuacion y sin espacios al ppio/final
    //Post: se agregan todas las palabras al final del texto

    vector<string> palabras = obtenerPalabras(oracion);
    size_t posicionInicial = _texto.size();
    //Agregar palabras al final del texto
    _texto.insert(_texto.end(), palabras.begin(), palabras.end());

    // Actualizar el vocabulario y la longitud del texto para que el conjunto refleje solo las palabras presentes en el texto actualizado
    _vocabulario.clear();
    for (const std::string& palabra : _texto) {
        _vocabulario.insert(palabra);
    }
    _longitud = _texto.size();

    // Actualizar el conteo de palabras no conectivas
    int palabrasNoConectivas = 0;
    for (const string& palabra : _texto) {
        if (_conectivos.find(palabra) == _conectivos.end()) {
            palabrasNoConectivas++;
        }
    }
    _conteo_palabras = palabrasNoConectivas;

    // Actualizar las posiciones de las nuevas palabras agregadas
    for (size_t i = posicionInicial; i < _texto.size(); i++) {
        const string& palabra = _texto[i];
        _posiciones[palabra].insert(i);
    }
}

const set<int>& Editor::buscar_palabra(const string& palabra) const { //O(log M) M = cantidad de palabras diferentes escritas en el texto
    // Devuelve el conjunto de posiciones del texto donde aparece la palabra buscada

    //Pre: string palabra no tiene espacios ni signos de puntuacion
    //Post: devuelve el cjto de posiciones del texto donde aparece la palabra buscada
   
    static set<int> emptySet;  // Conjunto vacío a devolver en caso de que la palabra no se encuentre

    // Verificar si la palabra está presente en el vocabulario
    if (_vocabulario.count(palabra) == 0) {
        return emptySet;  // La palabra no está en el texto, se devuelve el conjunto vacío
    }

    // Obtener el conjunto de posiciones asociado a la palabra buscada
    const set<int>& posiciones = _posiciones.at(palabra);

    return posiciones;

    //Complejidad O(log M) se cumple porque tanto la verificación de pertenencia en el vocabulario como el acceso al conjunto de posiciones se realizan en tiempo logarítmico en función del tamaño del vocabulario
}

void Editor::insertar_palabras(const string& oracion, int pos) { //sin requerimiento
    // Inserta en orden cada una de las palabras de la oración a partir de la posición indicada

    //Pre: 0 =< posicion =< longitud() y oracion es una secuencia de palabras separadas por un espacio, sin signos de puntuacion y sin espacios al ppio/final
    //Post: se inserta en orden cada una de las palabras de la oracion, a partir de la pos indicada

    // Obtener las palabras individuales de la oración
    vector<string> palabras = obtenerPalabras(oracion);
    size_t posicionInicial = _texto.size();

    // Actualizar el vocabulario y la longitud del texto para que el conjunto refleje solo las palabras presentes en el texto actualizado
    _vocabulario.clear();
    for (const std::string& palabra : _texto) {
        _vocabulario.insert(palabra);
    }

    // Actualizar el conteo de palabras no conectivas
    int palabrasNoConectivas = 0;
    for (const string& palabra : _texto) {
        if (_conectivos.find(palabra) == _conectivos.end()) {
            palabrasNoConectivas++;
        }
    }
    _conteo_palabras = palabrasNoConectivas;

    // Actualizar las posiciones de las nuevas palabras agregadas
    for (auto& entry : _posiciones) {
        std::set<int>& posiciones = entry.second;
        std::set<int> PosicionesUpdateadas;

        for (const int posicion : posiciones) {
            if (posicion >= pos) {
                PosicionesUpdateadas.insert(posicion + palabras.size());
            } else {
                PosicionesUpdateadas.insert(posicion);
            }
        }

        posiciones = std::move(PosicionesUpdateadas);
    }

    for (size_t i = 0; i < palabras.size(); ++i) {
        _texto.insert(_texto.begin() + pos + i, palabras[i]);

        // Updatea mapa _posiciones para palabra insertada
        _posiciones[palabras[i]].insert(pos + i);
    }

    // Actualizar el vocabulario y la longitud del texto para que el conjunto refleje solo las palabras presentes en el texto actualizado
    _vocabulario.clear();
    for (const std::string& palabra : _texto) {
        _vocabulario.insert(palabra);
    }
    _longitud = _texto.size();

    // Actualizar el conteo de palabras no conectivas
    palabrasNoConectivas = 0;
    for (const string& palabra : _texto) {
        if (_conectivos.find(palabra) == _conectivos.end()) {
            palabrasNoConectivas++;
        }
    }
    _conteo_palabras = palabrasNoConectivas;

    //Complejidad -> O(long texto + cant elementos a insertar)
    //ObtenerPalabras -> O(longitud texto)
    //Insertar palabra -> O(cant de elementos a insertar)
    //Actualizar vocab y long -> O(longitud texto)
    //Actualizar conteo -> O(longitud texto)

}

void Editor::borrar_posicion(int pos) { //sin requerimiento
    // Elimina la palabra ubicada en esa posición del texto

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
    }

    // Actualizar las posiciones de las palabras que están después de la posición eliminada
    for(int i = pos; i<this->_texto.size();i++){
        set <int> posiciones = this->_posiciones[this->_texto[i]];
        for (int posicion : posiciones){
            this->_posiciones[this->_texto[i]].erase(posicion);
            this->_posiciones[this->_texto[i]].insert(posicion - 1);
        }
    }

//  La complejidad algorítmica es O(long texto) porque recorre las palabras después de la posición eliminada y actualiza las posiciones en el mapa _posiciones.

   
}

int Editor::borrar_palabra(const string& palabra) { //sin requerimiento
    // Elimina la palabra indicada de todo el texto y devuelve la cantidad de palabras eliminadas

    //Pre: string palabra no tiene espacios ni signos de puntuacion
    //Post: se elimina la palabra indicada de todo el texto, y se devuelve la cant de palabras eliminadas
       
    int cantidadEliminada = 0;  // Variable para almacenar la cantidad de palabras eliminadas

    // Buscar la palabra en el texto
    for (int i = 0; i < _texto.size(); i++) {
        if (_texto[i] == palabra) {
            // La palabra se encuentra en la posición i del texto

            // Eliminar la palabra en la posición i del vocabulario
            _vocabulario.erase(_texto[i]);

            // Eliminar la posición i de la lista de posiciones asociadas a la palabra en el texto
            _posiciones[_texto[i]].erase(i);

            // Eliminar la palabra en la posición i del texto
            _texto.erase(_texto.begin() + i);

            // Actualizar la longitud del texto
            _longitud--;

            // Verificar si la palabra eliminada está en el conjunto de conectivos y actualizar la cantidad de palabras si es necesario
            if (_conectivos.find(palabra) != _conectivos.end()) {
                _cant_de_palabras--;
            }

            // Actualizar las posiciones de las palabras que están antes de la posición eliminada
            for (int j = 0; j < i; j++) {
                set<int>& posiciones = _posiciones[_texto[j]];
                for (int posicion : posiciones) {
                    if (posicion > i) {
                        posicion--;
                    }
                }
            }

            // Actualizar las posiciones de las palabras que están después de la posición eliminada
            for (int j = i; j < _texto.size(); j++) {
                set<int> posiciones = _posiciones[_texto[j]];
                for (int posicion : posiciones) {
                    if (posicion > i) {
                        posicion--;
                    }
                }
            }

            cantidadEliminada++;  // Incrementar la cantidad de palabras eliminadas

            // Como se eliminó una palabra, se debe retroceder el índice para seguir verificando las palabras restantes
            i--;
        }
    }

    return cantidadEliminada;

    //Complejidad -> O(long texto * num de palabras a eliminar)
    //Bucle for -> O(long texto)
    //Comparacion actual con palabra a borrar -> O(1)
    //Eliminacion y actualizacion -> O(numero de palabras a eliminar)

}


void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) { //O(log M + P log P) M = cantidad de palabras diferentes escritas en el texto. P =  cantidad máxima de repeticiones de una palabra en el texto
    // Reemplaza todas las ocurrencias en el texto de palabra1 por palabra2

    //Pre: strings palabra1 y palabra2 no tiene espacios ni signos de puntuacion
    //Post: se reemplazan todas las ocurrencias en el texto de palabra1 por palabra2

    // Verificar si palabra1 está en el vocabulario
    if (_vocabulario.count(palabra1) == 0) {
        // La palabra no está en el texto, no se realiza ningún reemplazo
        return;
    }

    // Obtener las posiciones de palabra1 en el texto
    const set<int>& posiciones = _posiciones.at(palabra1);

    // Reemplazar todas las ocurrencias de palabra1 por palabra2
    for (int posicion : posiciones) {
        _texto[posicion] = palabra2;
    }

    // Actualizar el vocabulario con la nueva palabra
    _vocabulario.erase(palabra1);
    _vocabulario.insert(palabra2);

    // Actualizar el conteo de palabras no conectivas
    int palabrasNoConectivas = 0;
    for (const string& palabra : _texto) {
        if (_conectivos.find(palabra) == _conectivos.end()) {
            palabrasNoConectivas++;
        }
    }
    _conteo_palabras = palabrasNoConectivas;

    //Complejidad -> O(log M + P log P)
    //Busqueda en _vocab -> (O(log M))
    //recorrido de posiciones de p1 -> (O(P))
    //reemplazo de c ocurrencia -> O(1)

}

std::vector<std::string> Editor::obtenerPalabras(const std::string& texto) const {
    // Función auxiliar para obtener las palabras individuales de un texto

    std::istringstream iss(texto);  // Crear un flujo de entrada desde el texto
    std::vector<std::string> _texto;

    std::string palabra;
    while (iss >> palabra) {
        _texto.push_back(palabra);  // Agregar cada palabra al vector
    }

    return _texto;


// La complejidad algorítmica es O(long texto) porque recorre el texto y agrega cada palabra al vector.
}

