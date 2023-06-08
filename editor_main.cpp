#include "Editor.h"
#include <iostream>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
	for (const T& i : s)
		os << i << " ";
	return os;
}

int main() {

    // Main para pruebas. NO ENTREGAR.
    string comando;
    set<string> conectivos;
    cout << "Ingrese lista de conectivos seguidos de '---':" << endl;
    while (cin >> comando, comando != "---") conectivos.insert(comando);
    
    Editor e(conectivos);
    cout << "Ingrese comandos. FIN para terminar. 'ayuda' para ayuda de comandos." << endl;

    cout << "comando: ";
    while (cin >> comando) {
	    if (comando == "FIN") break;
	    if (comando == "ayuda") cout << "Comandos:\nFIN\ntexto\nconteo_palabras\nvocabulario\nconectivos\nlongitud\nbuscar_palabra [palabra]\ninsertar_palabras [posicion] [oracion]\nagregar_atras [oracion]\nborrar_palabra [palabra]\nborrar_posicion [posicion]\nreemplazar_palabra [palabra1] [palabra2]" << endl;
	    if (comando == "texto") cout << e.texto() << endl;
	    else
            if (comando == "conteo_palabras") cout << e.conteo_palabras() << endl;
	    else
	    if (comando == "vocabulario") cout << e.vocabulario() << endl;
	    else
	    if (comando == "conectivos") cout << e.conectivos() << endl;
	    else
	    if (comando == "longitud") cout  << e.longitud() << endl;
	    else 
	    if (comando == "buscar_palabra") { cin >> comando; cout << e.buscar_palabra(comando) << endl; }
            else
            if (comando == "insertar_palabras") { int pos; cin >> pos; cin >> ws; getline(cin, comando); e.insertar_palabras(comando, pos); }
	    else 
	    if (comando == "agregar_atras") { cin >> ws; getline(cin, comando); e.agregar_atras(comando); }
            else
	    if (comando == "borrar_posicion") { int pos; cin >> pos; e.borrar_posicion(pos); }
	    else
	    if (comando == "borrar_palabra") { cin >> comando; cout << e.borrar_palabra(comando) << endl; }
	    else
	    if (comando == "reemplazar_palabra") { cin >> comando; string p2; cin >> p2; e.reemplazar_palabra(comando,p2); }

	cout << "comando: ";	    
    }



	    


    return 0;
}
