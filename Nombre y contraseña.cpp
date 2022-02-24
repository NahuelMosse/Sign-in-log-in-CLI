#include <iostream>
#include <string.h>
#include <fstream>

struct info_usuario //variables temporales
{
    std::string nombre;
    std::string password;
}usuario;

/******** I N G R E S O ********/
std::string preg_nombre_ingreso(); //pregunta el nombre de usuario
std::string preg_password_ingreso(); //pregunta la contraseña de usuario
int confirmar_ingreso(); //confirma que el nombre y la contraseña esten registrados
int contar_filas_csv(); //cuenta las filas de Nombres y contraseÃ±as.csv
std::string ingreso_info_csv_ingreso(int fila); //saca conjunto nombre;contraseña de Nombres y contraseÃ±as.csv
/******* R E G I S T R O *******/
std::string preg_nombre_registro(); //pregunta el nombre de usuario
std::string preg_password_registro(); //pregunta la contraseña de usuario
void registro_info_csv(); //registra nombre y contraseña en Nombres y contraseÃ±as.csv

/*********** M A I N ***********/

int main()
{
    char preg;
    int v=1;
    while (v)
    {
        std::cout<<"Presione\n[i] para ingresar\n[r] para registrarse\n[s] para salir\n";
        std::cin.get(preg);
        fflush(stdin);
        switch(preg)
        {
            /******** I N G R E S O ********/
            case 'i':
                usuario.nombre=preg_nombre_ingreso(); //pregunta el nombre de usuario
                usuario.password=preg_password_ingreso(); //pregunta la contraseña de usuario
                if (confirmar_ingreso()==0) //confirma que el nombre y la contraseña esten registrados
                {
                    std::cout<<"Se ha ingresado correctamente\n";
                }
                else
                {
                    std::cout<<"Nombre o password incorrectos\n";
                }
            break;
            /******* R E G I S T R O *******/
            case 'r':
                usuario.nombre=preg_nombre_registro(); //pregunta el nombre de usuario
                usuario.password=preg_password_registro(); //pregunta la contraseña de usuario
                registro_info_csv(); //registra nombre y contraseña en Nombres y contraseÃ±as.csv
                std::cout<<"Se ha registrado con exito";
            break;
            /********* S A L I D A *********/
            case 's':
                v=0;
                std::cout<<"Gracias por usar nuestra aplicacion";
            break;
            default:
            std::cout<<"El dato registrado es no valido\n";
            break;
        }
    }
    return 0;
}

/******** I N G R E S O ********/

//pregunta el nombre de usuario
std::string preg_nombre_ingreso()
{
    std::string name;
    std::cout<<"Ingrese Nombre de usuario: ";
    std::cin>>name;
    fflush(stdin);
    return name;
}

//pregunta la contraseña de usuario
std::string preg_password_ingreso()
{
    std::string password;
    std::cout<<"Ingrese password: ";
    std::cin>>password;
    fflush(stdin);
    return password;
}

//confirma que el nombre y la contraseña esten registrados
int confirmar_ingreso()
{
    int len,fila=2;
    std::string nombre_password,nombre_passwordaux;
    nombre_passwordaux=usuario.nombre+";"+usuario.password;
    len=contar_filas_csv(); //cuenta las filas de Nombres y contraseÃ±as.csv
    while (fila<=len)
    {
        nombre_password=ingreso_info_csv_ingreso(fila); //saca una linea de Nombres y contraseÃ±as.csv
        fila++;
        if (nombre_password==nombre_passwordaux)
        {
            return 0;
            break;
        }
    }
    return 1;
}

//cuenta las filas de Nombres y contraseÃ±as.csv
int contar_filas_csv()
{
    int len=0;
    std::ifstream file;
    file.open("Nombres y contraseñas.csv",std::ios::in);
        if(file.fail())
        {
            std::cout<<"error al abrir el archivo\n";
        }
        while (file.good())
        {
            if(file.get()=='\n')
            {
                len++;
            }
        }
    file.close();
    return len;
}

//saca conjunto nombre;contraseña de Nombres y contraseÃ±as.csv
std::string ingreso_info_csv_ingreso(int fila)
{
    int i=0;
    std::string nombre_password;
    std::ifstream file;
    file.open("Nombres y contraseñas.csv",std::ios::in);
        if(file.fail())
        {
        std::cout<<"error al abrir el archivo\n";
        }
        while (i<fila)
        {
            getline(file,nombre_password,'\n');
            i++;
        }
    file.close();
    return nombre_password;
}

/******* R E G I S T R O *******/

//pregunta el nombre de usuario
std::string preg_nombre_registro()
{
    int i=1,j=1;
    char preg;
    std::string name;

    while (i == 1)
    {
        std::cout<<"Ingrese Nombre de usuario: ";
        std::cin>>name;
        fflush(stdin);
        j=1;
        while (j == 1)
        {
            std::cout<<"Su nombre se usuario es "<<name<<"?(s o n) ";
            std::cin.get(preg);
            fflush(stdin);
            switch(preg)
            {
                case 's':
                    i=0;
                    j=0;
                break;
                case 'n':
                    j=0;
                break;
                default:
                    std::cout<<"Esa respuesta es no valida\n";
                break;
            }
        }
    }
    return name;
}

//pregunta la contraseña de usuario
std::string preg_password_registro()
{
    int i=1;
    char password[50],passwordaux[50];
    std::string passwordout;

    while(i == 1)
    {
        std::cout<<"Ingrese password: ";
        std::cin>>password;
        fflush(stdin);
        std::cout<<"Confirmar password: ";
        std::cin>>passwordaux;
        fflush(stdin);
        if (strcmp(password,passwordaux) == 0)
        {
            i=0;
            passwordout=password;
        }
        else
        {
            std::cout<<"Las passwords no son iguales\n";
        }
    }
    return passwordout;
}

//registra nombre y contraseña en Nombres y contraseÃ±as.csv
void registro_info_csv()
{
    std::ofstream file;
    file.open("Nombres y contraseñas.csv",std::ios::app);
        if(file.fail())
        {
        std::cout<<"error al abrir el archivo\n";
        }
        file<<usuario.nombre<<";";
        file<<usuario.password<<"\n";
    file.close();
}
