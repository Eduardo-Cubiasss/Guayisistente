#ifndef TMATERIACRUD_H
#define TMATERIACRUD_H

#include <string>
#include <vector>

class TMateriaCRUD
{
private:
    struct Materia
    {
        int idMateria;
        std::string nombreMateria;
    };

    std::string aRutaJson;
    std::vector<Materia> aMaterias;

    void CargarMateriasDesdeArchivo();
    void GuardarMateriasEnArchivo();
    void CrearArchivoJsonSiNoExiste();
    void OcultarArchivo(const std::string &ruta);

public:
    TMateriaCRUD();
    ~TMateriaCRUD();

    int ConexionExitosa();
    void AgregarMateria(const std::string &nombreMateria);
    void ActualizarMateria(int idMateria, const std::string &nuevoNombre);
    void EliminarMateria(int idMateria);
    void MostrarMaterias();
};

#endif
