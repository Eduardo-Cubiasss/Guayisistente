#ifndef TENCRIPTADOR_H
#define TENCRIPTADOR_H

#include <string>

class TEncriptador
{
private:
    std::string aClaveSecreta;
    std::string aRutaEnv;
    std::string aResultado;

    void CargarClave();
    void CrearArchivoEnv();
    std::string LeerClaveDesdeEnv();
    int CalcularDesplazamiento();
    std::string EncriptarMensaje(const std::string &mensaje);

public:
    TEncriptador();
    TEncriptador(const std::string &mensaje);
    ~TEncriptador();

    std::string ObtenerResultado() const;
    int ConexionExitosa();
    std::string AplicarEncriptacion(const std::string &mensaje);
};

#endif
