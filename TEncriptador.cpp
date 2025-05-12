#include "TEncriptador.h"
#include <iostream>
#include <fstream>
#include <limits>  // Necesario para std::numeric_limits

#ifdef _WIN32
#include <windows.h>
#endif

// Constructor vacío
TEncriptador::TEncriptador() {
    aRutaEnv = ".env";
    CargarClave();
    aResultado = "conexion exitosa";
}

// Constructor con mensaje
TEncriptador::TEncriptador(const std::string& mensaje) {
    aRutaEnv = ".env";
    CargarClave();

    if (!mensaje.empty()) {
        aResultado = EncriptarMensaje(mensaje);
    } else {
        aResultado = "conexion exitosa";
    }
}

TEncriptador::~TEncriptador() {
    // No se requiere liberar memoria manualmente
}

void TEncriptador::CargarClave() {
    std::ifstream archivo(aRutaEnv);
    if (!archivo.good()) {
        std::cout << "No se encontro .env. Creando uno nuevo..." << std::endl;
        CrearArchivoEnv();
    }

    aClaveSecreta = LeerClaveDesdeEnv();

    if (aClaveSecreta.empty()) {
        CrearArchivoEnv();
        aClaveSecreta = LeerClaveDesdeEnv();
    }
}

void TEncriptador::CrearArchivoEnv() {
    std::string clave;
    std::cout << "No se encontro .env. Ingrese una clave secreta: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpiar buffer
    std::getline(std::cin, clave);

    std::ofstream archivo(aRutaEnv);
    archivo << "KEY=" << clave << std::endl;
    archivo.close();

#ifdef _WIN32
    SetFileAttributesA(aRutaEnv.c_str(), FILE_ATTRIBUTE_HIDDEN);
#endif
}

std::string TEncriptador::LeerClaveDesdeEnv() {
    std::ifstream archivo(aRutaEnv);
    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos = linea.find("KEY=");
        if (pos != std::string::npos) {
            return linea.substr(pos + 4);
        }
    }
    return "";
}

int TEncriptador::CalcularDesplazamiento() {
    int desplazamiento = 0;
    for (char c : aClaveSecreta) {
        desplazamiento += static_cast<int>(c);
    }
    return desplazamiento % 256;
}

std::string TEncriptador::EncriptarMensaje(const std::string& mensaje) {
    int desplazamiento = CalcularDesplazamiento();
    std::string resultado = mensaje;
    for (char& c : resultado) {
        c = static_cast<char>((static_cast<unsigned char>(c) + desplazamiento) % 256);
    }
    return resultado;
}

std::string TEncriptador::AplicarEncriptacion(const std::string& mensaje) {
    aResultado = EncriptarMensaje(mensaje);
    return aResultado;
}


std::string TEncriptador::ObtenerResultado() const {
    return aResultado;
}

int TEncriptador::ConexionExitosa() {
    return !aClaveSecreta.empty() ? 1 : 0;
}
