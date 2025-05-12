#include "TMateriaCRUD.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <windows.h> // Para ocultar el archivo
#include "nlohmann/json.hpp"  // <-- Asegúrate de tener esto

using json = nlohmann::json;  // <-- Esto te faltaba

TMateriaCRUD::TMateriaCRUD()
{
    aRutaJson = ".materias.json";
    CrearArchivoJsonSiNoExiste();
    CargarMateriasDesdeArchivo();
}

TMateriaCRUD::~TMateriaCRUD()
{
}

int TMateriaCRUD::ConexionExitosa()
{
    std::ifstream archivo(aRutaJson);
    return archivo.good() ? 1 : 0;
}

void TMateriaCRUD::CrearArchivoJsonSiNoExiste()
{
    std::ifstream archivo(aRutaJson);
    if (!archivo.good())
    {
        std::ofstream nuevoArchivo(aRutaJson);
        nuevoArchivo << "[]";
        nuevoArchivo.close();
        OcultarArchivo(aRutaJson);
        std::cout << "Archivo .materias.json creado y ocultado." << std::endl;
    }
}

void TMateriaCRUD::OcultarArchivo(const std::string &ruta)
{
    SetFileAttributesA(ruta.c_str(), FILE_ATTRIBUTE_HIDDEN);
}

void TMateriaCRUD::CargarMateriasDesdeArchivo() {
    std::ifstream archivo(aRutaJson);
    if (!archivo.is_open()) {
        return;
    }

    json jMaterias;
    archivo >> jMaterias;  // <-- Simplemente parsea el JSON completo
    archivo.close();

    aMaterias.clear();
    for (const auto& j : jMaterias) {
        Materia materia;
        materia.idMateria = j["idMateria"];
        materia.nombreMateria = j["nombreMateria"];
        aMaterias.push_back(materia);
    }
}

void TMateriaCRUD::GuardarMateriasEnArchivo() {
    json jMaterias = json::array();

    for (const auto& materia : aMaterias) {
        json j;
        j["idMateria"] = materia.idMateria;
        j["nombreMateria"] = materia.nombreMateria;
        jMaterias.push_back(j);
    }

    std::ofstream archivo(aRutaJson);
    if (archivo.is_open()) {
        archivo << jMaterias.dump(4);  // dump(4) = bonito (4 espacios sangría)
        archivo.close();
    }
}


void TMateriaCRUD::AgregarMateria(const std::string &nombreMateria)
{
    int nuevoId = 1;
    if (!aMaterias.empty())
    {
        nuevoId = aMaterias.back().idMateria + 1;
    }

    Materia nuevaMateria;
    nuevaMateria.idMateria = nuevoId;
    nuevaMateria.nombreMateria = nombreMateria;
    aMaterias.push_back(nuevaMateria);

    GuardarMateriasEnArchivo();
    std::cout << "Materia agregada correctamente." << std::endl;
}

void TMateriaCRUD::MostrarMaterias()
{
    std::cout << "--- Materias Registradas ---" << std::endl;
    for (const auto &materia : aMaterias)
    {
        std::cout << "ID: " << materia.idMateria << " | Nombre: " << materia.nombreMateria << std::endl;
    }
}

void TMateriaCRUD::ActualizarMateria(int idMateria, const std::string &nuevoNombre)
{
    bool encontrado = false;
    for (auto &materia : aMaterias)
    {
        if (materia.idMateria == idMateria)
        {
            materia.nombreMateria = nuevoNombre;
            encontrado = true;
            break;
        }
    }
    if (encontrado)
    {
        GuardarMateriasEnArchivo();
        std::cout << "Materia actualizada correctamente." << std::endl;
    }
    else
    {
        std::cout << "ID no encontrado." << std::endl;
    }
}

void TMateriaCRUD::EliminarMateria(int idMateria)
{
    bool eliminado = false;
    for (auto it = aMaterias.begin(); it != aMaterias.end(); ++it)
    {
        if (it->idMateria == idMateria)
        {
            aMaterias.erase(it);
            eliminado = true;
            break;
        }
    }
    if (eliminado)
    {
        GuardarMateriasEnArchivo();
        std::cout << "Materia eliminada correctamente." << std::endl;
    }
    else
    {
        std::cout << "ID no encontrado." << std::endl;
    }
}
