  #include <iostream>
using namespace std;
string register_user();
bool register_check_user(string usuarios[],int tam,string user);
string register_pass();

bool login_check_user(string usuarios[], int tam, string user);
int position_pass(string usuarios[], int tam, string user);
bool login_check_pass(string pass[], string password, int pos);

int main() {

    const int max_soporte = 250; //cantidad de usuarios que permite el sistema
    string usuarios[max_soporte]; //todos los nombres de usuarios
    string pass[max_soporte]; //todas las contraseñas
    usuarios[0] = "administrador";
    pass[0] = "test_ok";
    int usuarios_enbase = 1; //este contador no se reinicia nunca, ya que determina que posicion de los vectores de usuario y password son escritos. (empieza en 1, porque el 0 esta ocupado por el test de administrador)
    int bucle = 0;
    while(bucle == 0){ //Bucle que se encarga de mantener el programa corriendo para multiples inicios de sesion.
        //Variables que se reinician
    bool log_reg;
    bool valid_user;
    int pos_pass;
    string password = " ";

    //Inicio programa
    cout<<"|1 para registrarse, 0 para iniciar sesion|: ";
    cin>>log_reg;
    string temp_user = " ";

    switch (log_reg){ //determinante de si va a registrar o loggear
        case 1:
        valid_user = false;
        while(valid_user == false){
            temp_user = register_user();
            valid_user = register_check_user(usuarios, max_soporte, temp_user);
        }
            usuarios[usuarios_enbase] = temp_user;
            pass[usuarios_enbase] = register_pass();
            usuarios_enbase++;
        break;

        case 0:
        //Variables que se reinician
        bool logged_in = false;
        bool user_log = false;
        bool pass_log = false;

        cout<<"Ingrese su usuario: ";
        cin>>temp_user;
        user_log = login_check_user(usuarios, max_soporte, temp_user);
        if(user_log == true){
            pos_pass = position_pass(usuarios, max_soporte, temp_user);
            cout<<"Ingrese su password: ";
            cin>>password;
            pass_log = login_check_pass(pass, password, pos_pass);
        }
        else{
            cout<<"Usuario no existente en base de datos, ingrese otro"<<endl;
        }
        if(pass_log == true ){
            cout<<"Sesion Iniciada correctamente"<<endl;
            return 0; //Esto pone fin al programa, borrar si se quiere probar el programa
        }
        else{
            cout<<"Contraseña invalida."<<endl;
        }

        break;
    }
    }
}
///Simplemente pide un dato y lo devuelve (el usuario)
string register_user(){
    string user;
    cout<<"Ingrese el nombre de usuario que desea: ";
    cin>>user;
    return user;
}

///Pide el vector usuarios y su tamaño, para, mediante un ciclo for, verificar que el usuario inputeado no exista en otra posicion del vector, ya que el sistema no admite usuarios iguales.
bool register_check_user(string usuarios[],int tam,string user){
    for(int x = 0; x<tam; x++){
        if(user == usuarios[x]){
            cout<<"Usuario ya ocupado, ingrese otro."<<endl;
            return false;
        }
    }
    return true;
}

///Al igual que register_user, solo que tiene requerimientos de cantidad de digitos a manera de challenge personal.
/*si se quisiera cambiar por ejemplo que tenga almenos una mayuscula, tenemos que tener en cuenta el codigo ASCII (https://elcodigoascii.com.ar), y  teniendo un contador de Mayus, evaluar que el caracter sea mayor o igual que el numero que le corresponde a 'A' (65) y menor o igual que 'Z' (90). en caso positivo, sume al contador de mayus uno mas sobre el mismo, y por ultimo añadir  en el condicional que el contador sea >=1
    Aclaracion: tambien podriamos usar un bool en este hipotetico caso de contador de mayus, que funcionaria igual, pero nos cierra al caso de querer solamente una mayuscula, el hecho de usar un contador, nos da la opcion que si un dia cambiamos de opinion, y queremos que las pass tengan 3 mayus, por ejemplo, un bool no nos serviria
.*/
string register_pass(){
    bool check_pass = false;
    string pass;
    cout<<"Ahora ingrese la password (debe tener minimo 6 digitos y maximo 12): ";
    while(check_pass == false){
        cin>>pass;
        if(pass.size()>=6 && pass.size()<=12){
            return pass;
        }
        cout<<"No cumple los requerimientos pedidos, ingrese una password valida"<<endl;
    }

}


//Pide el vector de usuarios y su tamaño para poder hacer un ciclo for, en el que va a comprar cada elemento de usuarios[] con temp_user, y asi determinar que el usuario esta registrado.
bool login_check_user(string usuarios[], int tam, string user){
    for(int x = 0; x<tam; x++){
        if (usuarios[x] == user){
            return true;
        }
    }
    return false;
}

///Determina la posicion del vector en la que se encuentra registrado el usuario que se inputeo previamente
int position_pass(string usuarios[], int tam, string user){
    for(int x = 0; x<tam; x++){
        if (usuarios[x] == user){
            return x;
        }
    }
    return 1; // este return es imposible que pase, solamente lo pongo para evitar una warning
}

///Pide el vector de password y la posicion de la password para comprar el mismo pass[x] con la contraseña que inputeo el usuario, y si son iguales, es porque el usuario y la contraseña estan bien
bool login_check_pass(string pass[], string password, int pos){
    if(pass[pos] == password){
        return true;
    }
    return false;  // este return es imposible que pase, solamente lo pongo para evitar una warning
}
