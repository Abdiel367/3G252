#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/color.hpp>
using namespace ftxui;


string gato1 =
    "                    _ |\\_ \n"
    "                   \\` ..\\ \n"
    "              __,.-\" =__Y= \n"
    "            .\"        ) \n"
    "      _    /   ,    \\/\\_ \n"
    "     ((____|    )_-\\ \\_-` \n"
    "     `-----'`-----` `--`  \n"
    "    _ _ _ _ _ _ _ _ _ _";

  
string pajaro1 =
    "          __            \n"
    "        _/ '>           \n"
    "  _ _.-'(   )'-._ _     \n"
    " '=._.=-(   )-=._.='    \n"
    "        |/\\-\\|           \n"
    "        Y   Y           ";


string gato2 =
    "  _._     _,-'\"\"`-._ \n"
    " (,-.`._,'(       |\\`-/| \n"
    "     `-.-' \\ )-`( , o o) \n"
    "           `-    \\`_`\"'- \n"
    "    _ _ _ _ _ _ _ _ _ _";


string pajaro2 =
    "            __          \n"
    "    <___  ___( o)>      \n"
    "            \\ <_. )     \n"
    "           `---'        ";


string gato3 =
    "       ,_     _,       \n"
    "      |\\\\___//|       \n"
    "      |=6   6=|       \n"
    "      \\=._Y_.=/        \n"
    "       )  `  (    ,    \n"
    "      /       \\  ((    \n"
    "       | |   | |\\\\_// \n"
    "     \\| |._.| |/-`     \n"
    "      '\"'   '\"'       \n"
    "    _ _ _ _ _ _ _ _ _ _";

int main(int argc, char const *argv[])
{
    auto pantalla = Screen::Create(
        Dimension::Full(),
        Dimension::Fixed(20));

    int gatoX = 10;
    int pajaroX = 50;
    int contador = 0;
    int contadorVictoria = 0;  
    bool enMovimiento = false;
    bool pajaroAtrapado = false;

    while (true)
    {
        pantalla.Clear();

        
        if (contador < 15 && !pajaroAtrapado) {
            // Dibujar gato frame 1 (ESPERA)
            stringstream ssGato(gato1);
            string linea;
            int noLinea = 0;
            while (getline(ssGato, linea)) {
                int columna = 0;
                for(auto &&letra : linea) {
                    auto &pixel = pantalla.PixelAt(gatoX + columna, 12 + noLinea);
                    pixel.character = letra;
                    columna++;
                }
                noLinea++;
            }

            
            stringstream ssPajaro(pajaro1);
            noLinea = 0;
            while (getline(ssPajaro, linea)) {
                int columna = 0;
                for(auto &&letra : linea) {
                    auto &pixel = pantalla.PixelAt(pajaroX + columna, 5 + noLinea);
                    pixel.character = letra;
                    columna++;
                }
                noLinea++;
            }
            contador++;
        } 
        
        else if (!pajaroAtrapado) {
            enMovimiento = true;
            
            // GATO MÁS RÁPIDO QUE EL PÁJARO
            gatoX += 2;      // Gato rápido
            pajaroX += 1;    // Pájaro lento

            // VERIFICAR SI EL GATO ALCANZA AL PÁJARO
            if (gatoX >= pajaroX - 15) { // Si el gato está cerca del pájaro
                pajaroAtrapado = true;
                gatoX = pajaroX - 5; // Posicionar el gato donde estaba el pájaro
                contadorVictoria = 0; // Reiniciar contador de victoria
            }

            // Dibujar gato frame 2 (CORRIENDO)
            stringstream ssGato(gato2);
            string linea;
            int noLinea = 0;
            while (getline(ssGato, linea)) {
                int columna = 0;
                for(auto &&letra : linea) {
                    auto &pixel = pantalla.PixelAt(gatoX + columna, 12 + noLinea);
                    pixel.character = letra;
                    columna++;
                }
                noLinea++;
            }

            // Dibujar pájaro frame 2 (solo si no fue atrapado)
            if (!pajaroAtrapado) {
                stringstream ssPajaro(pajaro2);
                noLinea = 0;
                while (getline(ssPajaro, linea)) {
                    int columna = 0;
                    for(auto &&letra : linea) {
                        auto &pixel = pantalla.PixelAt(pajaroX + columna, 5 + noLinea);
                        pixel.character = letra;
                        columna++;
                    }
                    noLinea++;
                }
            }
            contador++;
        }
        // Fase final: GATO EN VICTORIA (DURACIÓN MÁS LARGA)
        else {
            // Dibujar gato frame 3 (VICTORIA)
            stringstream ssGato(gato3);
            string linea;
            int noLinea = 0;
            while (getline(ssGato, linea)) {
                int columna = 0;
                for(auto &&letra : linea) {
                    auto &pixel = pantalla.PixelAt(gatoX + columna, 12 + noLinea);
                    pixel.character = letra;
                    columna++;
                }
                noLinea++;
            }

            // CONTADOR SEPARADO PARA VICTORIA - 5 SEGUNDOS
            contadorVictoria++;
            if (contadorVictoria > 25) { // 25 frames * 200ms = 5 segundos
                gatoX = 10;
                pajaroX = 50;
                contador = 0;
                contadorVictoria = 0;
                pajaroAtrapado = false;
                enMovimiento = false;
            }
        }

        // Reiniciar si salen de pantalla (solo si no hay atrapada)
        if (gatoX > pantalla.dimx() && !pajaroAtrapado) {
            gatoX = 10;
            pajaroX = 50;
            contador = 0;
            enMovimiento = false;
        }

        pantalla.Print();
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << pantalla.ResetPosition();
    }
    return 0;
}