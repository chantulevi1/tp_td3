#include <gtest/gtest.h>

#include "Editor.h"

using namespace std;
typedef set<string> strset;
typedef set<int> intset;

TEST(editor_tests, test_vacio) {
    Editor e({"hola"});
    ASSERT_EQ(e.vocabulario(), strset({}));
    ASSERT_EQ(e.conectivos(), strset({"hola"}));
    ASSERT_EQ(e.conteo_palabras(), 0);
    ASSERT_EQ(e.longitud(), 0);
}

TEST(editor_tests, test_texto) {
    Editor e({});
    e.agregar_atras("el vecino es mi amigo");

    ASSERT_EQ(e.texto(), "el vecino es mi amigo");
}

TEST(editor_tests, test_conteo_palabras_longitud) {
    Editor e({});
    e.agregar_atras("el vecino es mi amigo");
    ASSERT_EQ(e.conteo_palabras(), 5);
    ASSERT_EQ(e.longitud(), 5);

   Editor e2({"el", "es", "mi"});
    e2.agregar_atras("el vecino es mi amigo");
    ASSERT_EQ(e2.conteo_palabras(), 2);
    ASSERT_EQ(e.longitud(), 5);
}

TEST(editor_tests, test_buscar) {
    Editor e({"el", "es", "mi"});
    e.agregar_atras("el vecino es mi amigo");

    ASSERT_EQ(e.buscar_palabra("amigo"), intset({4}));
}

TEST(editor_tests, test_vocabulario) {
    Editor e({"el", "es", "mi"});
    e.agregar_atras("el vecino es mi amigo");

    ASSERT_EQ(e.vocabulario(), strset({"vecino","amigo"}));
}

TEST(editor_tests, test_insertar) {
    Editor e({"el", "es", "mi"});
    e.agregar_atras("el vecino es mi amigo");
    e.insertar_palabras("mejor", 4);

    ASSERT_EQ(e.texto(), "el vecino es mi mejor amigo");
}

TEST(editor_tests, test_insertar_y_luego_buscar) {
    Editor e({"el", "es", "mi"});
    e.agregar_atras("el vecino es mi amigo");
    e.insertar_palabras("amigo",2);

    ASSERT_EQ(e.buscar_palabra("amigo"), intset({2,5}));
}

TEST(editor_tests, test_borrar_posicion) {
    Editor e({});

    e.agregar_atras("el vecino es mi amigo");
    e.borrar_posicion(2);

    ASSERT_EQ(e.texto(), "el vecino mi amigo");

}

TEST(editor_tests, test_borrar_posicion_y_buscar) {
    Editor e({});

    e.agregar_atras("el vecino es mi amigo");

    ASSERT_EQ(e.buscar_palabra("amigo"), intset({4}));

    e.borrar_posicion(2);

    ASSERT_EQ(e.buscar_palabra("amigo"), intset({3}));
}

TEST(editor_tests, borrar_palabra) {
    Editor e({});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");

    e.borrar_palabra("pin");
    ASSERT_EQ(e.texto(), "uno dos tres cuatro cinco seis siete pinocho");
}

TEST(editor_tests, borrar_palabra_y_buscar) {
    Editor e({});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");

    ASSERT_EQ(e.buscar_palabra("pin"), intset({0,2,4,6,8,10,12}));
    e.borrar_palabra("pin");
    ASSERT_EQ(e.buscar_palabra("pin"), intset({}));
}

TEST(editor_tests, borrar_conectivo) {
    // "pin" es conectivo
    Editor e({"pin"});

    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");

    ASSERT_EQ(e.vocabulario(), strset({"uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "pinocho"}));
    ASSERT_EQ(e.conteo_palabras(), 8);

    e.borrar_palabra("pin");

    ASSERT_EQ(e.vocabulario(), strset({"uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "pinocho"}));
    ASSERT_EQ(e.conteo_palabras(), 8);
}

TEST(editor_tests, reemplazar_palabra) {
    Editor e({});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");
    ASSERT_EQ(e.conteo_palabras(), 15);

    e.reemplazar_palabra("pin", "pon");
    ASSERT_EQ(e.texto(), "pon uno pon dos pon tres pon cuatro pon cinco pon seis pon siete pinocho");
    ASSERT_EQ(e.conteo_palabras(), 15);
}

TEST(editor_tests, reemplazar_conectivo_por_conectivo) {
    Editor e({"pin", "pon"});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");
    ASSERT_EQ(e.conteo_palabras(), 8);

    e.reemplazar_palabra("pin", "pon");
    ASSERT_EQ(e.conteo_palabras(), 8);
}

TEST(editor_tests, reemplazar_conectivo_por_no_conectivo) {
    Editor e({"pin"});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");
    ASSERT_EQ(e.conteo_palabras(), 8);

    e.reemplazar_palabra("pin", "pon");
    ASSERT_EQ(e.conteo_palabras(), 15);
}

TEST(editor_tests, reemplazar_no_conectivo_por_conectivo) {
    Editor e({"pon"});
    e.agregar_atras("pin uno pin dos pin tres pin cuatro pin cinco pin seis pin siete pinocho");
    ASSERT_EQ(e.conteo_palabras(), 15);

    e.reemplazar_palabra("pin", "pon");
    ASSERT_EQ(e.conteo_palabras(), 8);
}

// TEST(editor_tests, nombre_test) {
// }

// TEST(editor_tests, nombre_test) {
// }

