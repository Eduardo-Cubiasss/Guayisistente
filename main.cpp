#include <iostream>
#include "TEncriptador.h"
#include "TMateriaCRUD.h"

int main()
{
    int opcion_Menu;
    std::cout << "----------------------------------------\n";
    std::cout << "|   /\\                                 |\n";
    std::cout << "|  /  \\    Bienvenido a tu             |\n";
    std::cout << "| /----\\   asistente de tareas         |\n";
    std::cout << "|                                      |\n";
    std::cout << "|--------------------------------------|\n";

    // Solo la G de palitos + texto normal al lado
    std::cout << "   _____   \n";
    std::cout << "  / ____|  \n";
    std::cout << " | |  __   \n";
    std::cout << " | | |_ |  \n";
    std::cout << " | |__| |  \n";
    std::cout << "  \\_____|  \n";
    std::cout << "   _____   uayisistente\n";
    std::cout << "----------------------------------------------------------------\n";
    std::cout << "|  Espero tengas un dia bonito :)                              |\n";
    std::cout << "----------------------------------------------------------------\n";

    std::cout << "Menu de opciones: " << std::endl;
    std::cout << "-> 1. Proximas 5 actividades" << std::endl;
    std::cout << "-> 2. Agregar, actualizar o eliminar tareas" << std::endl;
    std::cout << "-> 3. Ver resumen por materia" << std::endl;
    std::cout << "-> 4. Fechas de parciales y examenes siguientes" << std::endl;
    std::cout << "-> 5. Todas las siguientes actividades" << std::endl;
    std::cout << "-> 6. Gestionar materias" << std::endl;
    std::cout << "Ingresa una opcion: ";
    std::cin >> opcion_Menu;

    TEncriptador encriptador;

    // Verificar si la conexión fue exitosa
    if (encriptador.ConexionExitosa())
    {
        switch (opcion_Menu)
        {
        case 1:
            std::cout << "---Proximas 5 actividades---" << std::endl;
            break;
        case 2:
            std::cout << "---Agregar, actualizar o eliminar tareas---" << std::endl;
            break;
        case 3:
            std::cout << "---Ver resumen por materia---" << std::endl;
            break;
        case 4:
            std::cout << "---Fechas de parciales y examenes siguientes---" << std::endl;
            break;
        case 5:
            std::cout << "---Todas las siguientes actividades---" << std::endl;
            break;
        case 6:
        {
            std::cout << "---Gestionar materias---" << std::endl;
            std::cout << "1. Agregar materia" << std::endl;
            std::cout << "2. Actualizar materia" << std::endl;
            std::cout << "3. Eliminar materia" << std::endl;
            std::cout << "4. Mostrar materias" << std::endl;
            std::cout << "Selecciona una opcion: ";
            int opcionMateria;
            std::cin >> opcionMateria;

            TMateriaCRUD crudMaterias;

            if (crudMaterias.ConexionExitosa())
            {
                switch (opcionMateria)
                {
                case 1:
                {
                    std::cout << "---Agregar materia---" << std::endl;
                    std::cout << "Ingresa el nombre de la materia: ";
                    std::cin.ignore(); // Limpiar buffer
                    std::string nombreMateria;
                    std::getline(std::cin, nombreMateria);
                    crudMaterias.AgregarMateria(nombreMateria);
                    break;
                }
                case 2:
                {
                    std::cout << "---Actualizar materia---" << std::endl;
                    crudMaterias.MostrarMaterias();
                    std::cout << "Ingresa el ID de la materia a actualizar: ";
                    int idActualizar;
                    std::cin >> idActualizar;
                    std::cout << "Ingresa el nuevo nombre de la materia: ";
                    std::cin.ignore();
                    std::string nuevoNombre;
                    std::getline(std::cin, nuevoNombre);
                    crudMaterias.ActualizarMateria(idActualizar, nuevoNombre);
                    break;
                }
                case 3:
                {
                    std::cout << "---Eliminar materia---" << std::endl;
                    crudMaterias.MostrarMaterias();
                    std::cout << "Ingresa el ID de la materia a eliminar: ";
                    int idEliminar;
                    std::cin >> idEliminar;
                    crudMaterias.EliminarMateria(idEliminar);
                    break;
                }
                case 4:
                {
                    std::cout << "---Mostrar materias---" << std::endl;
                    crudMaterias.MostrarMaterias();
                    break;
                }
                default:
                    std::cout << "Opcion no valida, adios chichi" << std::endl;
                    break;
                }
            }
            else
            {
                std::cout << "Error al conectar con el archivo de materias." << std::endl;
            }

            break;
        }

        default:
            std::cout << "Opcion no valida, adios chichi" << std::endl;
            break;
        }
    }
    else
    {
        std::cout << "Error al conectar al archivo .env" << std::endl;
    }

    return 0;
}
