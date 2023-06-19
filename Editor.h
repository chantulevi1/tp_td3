#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <set>
#include <string>
#include <vector>
#include <map>
/* agregar includes que sean necesarios */

using namespace std;

class Editor {
public:
    // Dimensiones:
    // N: cantidad total de palabras del texto (incluyendo repetidas)
    // M: cantidad de palabras diferentes del texto (conectivas o no)
    // cardinal del conjunto de conectivos -> se puede asumir que es constante K
    // P: cantidad de repeticiones de la palabra más repetida

    // Crea un editor de texto vacío y registra qué conectivos considerará
    Editor(const set<string> & conectivos);                     // O(1)

    // Obtiene el texto completo
    string texto() const;                                       // O(N)

    const set<string>& vocabulario() const;                     // O(1)
    const set<string>& conectivos() const;                      // O(1)

    //  cuántas palabras no conectivas tiene el texto
    int conteo_palabras() const;                                // O(1)
    // cantidad de palabras del texto               
    int longitud() const;                                       // O(1)

    // obtiene posiciones de la palabra en el texto, busqueda binaria?
    const set<int> & buscar_palabra(const string& palabra) const;               // O(log M)

    // agrega una palabra en una posición, desplazando a las restantes
    void insertar_palabras (const string& oracion, int posicion);               // sin requerimiento
    // elimina la palabra de una posición
    void borrar_posicion (int posicion);                                        // sin requerimiento
    // borra todas las apariciones de la palabra del texto y devuelve la cantidad borrada 
    int borrar_palabra (const string& palabra);                                 // sin requerimiento

    // agrega varias palabras al final del texto (separadas por espacios)
    void agregar_atras (const string& oracion);                                 // O(|oracion| * log(M))
    // reemplaza una palabra por otra    
    void reemplazar_palabra(const string& palabra, const string& reemplazo);    // O(log M + P * log(P))

private:
    /* Completar */
    // conjuntos vacíos para devolver por referncia
    set<string> _conectivos;
    int _longitud;
    set<string> _vocabulario;
    vector<string> _texto;
    string palabra;
    int _conteo_palabras;
    std::unordered_map<std::string, std::set<int>> _posiciones;  // Mapa de palabras y sus posiciones
    int _cant_de_palabras;  // Cantidad total de palabras (excluyendo conectivos)

    
    //f auxiliar
    std::vector<std::string> obtenerPalabras(const std::string& texto) const;

};

#endif // __EDITOR_H__
