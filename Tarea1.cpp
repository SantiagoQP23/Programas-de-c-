#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<locale.h>
#include<string.h>
using namespace std;

/*
Implementar una aplicación que permita registrar las provincias (código, nombre) con sus
respectivos cantones (código, nombre) con sus respectivas parroquias (código, nombres).
1: Registrar
2: Listar
3: buscar un cantón
4: modificar una parroquia

*/

struct Parroquia{
	
	int codigo;
	string nombre;
};

struct Canton{
	
	int codigo;
	string nombre;
	Parroquia parroquias[10];
	int contParroquias;
};

struct Provincia{
	int codigo; 
	string nombre;
	Canton cantones[10];
	int contCantones;
	
};

// Declarar funciones
int mostrarMenu();
void operaciones(int opcion, Provincia provincias[], int &contProvincias);
void registrarProvincia(int &contProvincias, Provincia provincias[]);
void registrarCanton(int &contCantones, Canton cantones[]);
void registrarParroquia(int &contParroquias, Parroquia parroquias[]);
bool mostrarParroquias(Parroquia parroquias[], int contParroquias);
void mostrarParroquia(Parroquia parroquia);
void mostrarCanton(Canton canton);
void mostrarProvincias(Provincia provincias[], int contProvincias);
void mostrarProvincia(Provincia provincias);
void mostrarCantones(Canton cantones[], int contCantones);
bool buscarCanton(int codigoCanton, Canton cantones[], int contCantones);
bool buscarParroquia(int codigoParroquia, Parroquia parroquias[], int contParroquias, int& posParroquia);




int main(){
    setlocale(LC_CTYPE,"Spanish");
    
    Provincia provincias[24];
    int contProvincias = 0;
    
    int opcion;
    do{
    	system("cls");
    	
    	 opcion = mostrarMenu();
    	
    	operaciones(opcion, provincias, contProvincias);
    	

    	cout<<"desea realizar otra operación si(1): ";
    	cin>>opcion;
    	
	}while(opcion==1);

	getch();
	return 0;
}

int mostrarMenu(){
	int respuesta;
	
	do{
		system("cls");
		cout<<"***OPERACIONES***"<<endl;
		cout<<"1. Registrar provincia"<<endl;
		cout<<"2. Listar provincias"<<endl;
		cout<<"3. Buscar cantón"<<endl;
		cout<<"4. Modificar parroquia"<<endl;
		cout<<"Elija una opcion: ";
		cin>>respuesta;	
		
		fflush(stdin);// liberar memoria
	
	}while(respuesta < 0 or respuesta > 4);
	
	return respuesta;
	
}


void operaciones(int opcion, Provincia provincias[], int &contProvincias)
{
		
	switch(opcion){
		
		case 1:
			
			registrarProvincia(contProvincias, provincias);
			break;
			
		case 2: 
		
			mostrarProvincias(provincias, contProvincias);
			break;
		
		case 3: 
			
			int codigoCanton;
			cout<<"**Buscar canton**"<<endl;
			cout<<"Ingrese el codigo del canton: ";
			cin>>codigoCanton;
			
			
			bool cantonExiste;
			cantonExiste = false;
			for(int i = 0; i< contProvincias and !cantonExiste; i++){
				cantonExiste = buscarCanton(codigoCanton, provincias[i].cantones, provincias[i].contCantones);
				
			}
			
			if(!cantonExiste){
				cout<<"El canton no ha sido registrado"<<endl;	
			}
			
			break;
			
		case 4:
			
			
			int codigoParroquia; 
			cout<<"**Modificar parroquia**"<<endl;
			cout<<"Ingrese el codigo de la parroquia: ";
			cin>>codigoParroquia;
				
			bool parroquiaExiste;
			parroquiaExiste = false;
			int posParroquia;
			
			for(int i = 0; i < contProvincias and !parroquiaExiste; i++)// recorre las provincias
			{
				Canton cantones[10] = provincias[i].cantones;
				
				for (int j = 0 ; j < provincias[i].contCantones; j++){//recorre los cantones
					
					parroquiaExiste = buscarParroquia(codigoParroquia, cantones[j].parroquias, cantones[j].contParroquias, posParroquia);
					
					if(parroquiaExiste){//Cambiar valor
						string nombre;
						
						cout<<"Ingrese el nuevo nombre de la parroquia: ";
						cin>>nombre;
						
						provincias[i].cantones[j].parroquias[posParroquia].nombre = nombre;

					}
				}
				
			 } 		
						
			if(!parroquiaExiste){
				cout<<"La parroquia no ha sido registrada"<<endl;
			}
	}
}


void registrarProvincia(int &contProvincias, Provincia provincias[])
{
	
	cout<<"**Registrar provincia**"<<endl;
	cout<<"Ingrese el codigo de la provincia: ";
	cin>>provincias[contProvincias].codigo;
	
	cout<<"Ingrese el nombre de la provincia: ";
	cin>>provincias[contProvincias].nombre;
	
	fflush(stdin);// liberar memoria
	provincias[contProvincias].contCantones = 0;
	
	int resp; 
	cout<<"Desea registar un canton si(1) no (otro numero): ";
    cin>>resp;	
    
    while (resp == 1){
    	
		registrarCanton(provincias[contProvincias].contCantones, provincias[contProvincias].cantones);
    	
    	//alterar la condicion 
    	cout<<"Desea registar otro canton si(1) no (otro numero): ";
    	cin>>resp;
	}
	
	contProvincias++;
	fflush(stdin);// liberar memoria

}


void registrarCanton(int &contCantones, Canton cantones[]){
	
	
	cout<<"**Registrar canton**"<<endl;
	cout<<"Ingrese el codigo del canton: ";
	cin>>cantones[contCantones].codigo;
	
	cout<<"Ingrese el nombre del canton: ";
	cin>>cantones[contCantones].nombre;
	
	fflush(stdin);// liberar memoria
	
	cantones[contCantones].contParroquias = 0;
	
	int resp; 
	cout<<"Desea registar una parroquia si(1) no (otro numero): ";
    cin>>resp;	
    
    while (resp == 1){
    	
    	registrarParroquia(cantones[contCantones].contParroquias, cantones[contCantones].parroquias);
    	
    	//alterar la condicion 
    	cout<<"Desea registar otra parroquia si(1) no (otro numero): ";
    	cin>>resp;
	}
	
	
	contCantones++;
}


void registrarParroquia(int &contParroquias, Parroquia parroquias[]){
	cout<<"**Registrar parroquia**"<<endl;
	
	cout<<"Ingrese el codigo de la parroquia: ";
	cin>>parroquias[contParroquias].codigo;
	
	cout<<"Ingrese el nombre de la parroquia: ";
	cin>>parroquias[contParroquias].nombre;
	
	//fflush(stdin);// liberar memoria
	contParroquias++;
}

bool mostrarParroquias(Parroquia parroquias[],int  contParroquias)
{
	bool resultado;
	resultado = false;
	
	for(int i = 0; i < contParroquias; i++){
		mostrarParroquia(parroquias[i]);
		resultado = true;
		cout<<endl;
	}
	
	return resultado;
}


void mostrarParroquia(Parroquia parroquia)
{
	cout<<"Codigo: "<<parroquia.codigo<<endl;
	cout<<"Nombre: "<<parroquia.nombre<<endl;

	
}

void mostrarCantones(Canton cantones[], int contCantones){
	for (int i = 0; i < contCantones; i++){
				cout<<"\t\t***CANTON***"<<endl;

		mostrarCanton(cantones[i]);
		
		cout<<"\t\t***PARROQUIAS***"<<endl;
		
		if (!mostrarParroquias(cantones[i].parroquias, cantones[i].contParroquias))
		{
			cout<<"No se han registrado parroquias"<<endl;
		}
		
		
		cout<<endl;
		
	}
	
}


void mostrarCanton(Canton canton)
{
	cout<<"Codigo: "<<canton.codigo<<endl;
	cout<<"Nombre: "<<canton.nombre<<endl;

	
}


void mostrarProvincias(Provincia provincias[], int contProvincias)
{
	for (int i = 0; i < contProvincias; i++){
		cout<<"\t\t***PROVINCIA***"<<endl;
		mostrarProvincia(provincias[i]);
		
		
		mostrarCantones(provincias[i].cantones, provincias[i].contCantones);
		
	}
		fflush(stdin);// liberar memoria

}

void mostrarProvincia(Provincia provincia)
{
	cout<<"Codigo: "<<provincia.codigo<<endl;
	cout<<"Nombre: "<<provincia.nombre<<endl;

	
}

bool buscarCanton(int codigoCanton, Canton cantones[], int contCantones)
{
	
	bool resultado = false;
	
	for( int i = 0; i < contCantones; i++){
		
		if (cantones[i].codigo == codigoCanton){
			mostrarCanton(cantones[i]);
			resultado = true;
		}
	}
	return resultado;
	
}

bool buscarParroquia(int codigoParroquia, Parroquia parroquias[], int contParroquias, int &posParroquia)
{
	
	bool resultado = false;
	
	for(int i = 0; i < contParroquias; i++)
	{
		if(parroquias[i].codigo == codigoParroquia){
			
			posParroquia = i;
									
			resultado = true;
		}
		
	}
	
	return resultado;
}





