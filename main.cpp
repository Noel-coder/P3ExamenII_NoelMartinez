#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> tokenizer(string linea) {
	vector<string> temp;
	stringstream revisar(linea);
	string intermediate;
	while(getline(revisar, intermediate, ',')) {
		temp.push_back(intermediate);
	}

	return temp;
}

union DatoValor {
	unsigned int ui_dato;
	int i_dato;
	float f_dato;
	char operador;
};

struct Dato {
	char c_tipo;
	DatoValor valor;
};

vector <Dato> convertirTokens(vector<string> tokens) {
	vector<Dato> datos;
	if(tokens.at(0)=="I") {
		for(int i = 1; i < tokens.size(); i++) {
			Dato objeto;
			char tipo='I';
			if(tokens.at(i)=="*" || tokens.at(i)=="/"||tokens.at(i)=="+"||tokens.at(i)=="-") {
				tipo=='O';
				objeto.valor.operador=tokens.at(i)[0];
			}
			if(tokens.at(i)!= "*" && tokens.at(i) != "/"&&tokens.at(i)!= "+"&&tokens.at(i)!="-") {
				objeto.valor.i_dato=stoi(tokens.at(i));
			}
			objeto.c_tipo=tipo;
			datos.push_back(objeto);
		}
	} else if(tokens.at(0)=="F") {
		for(int i = 1; i < tokens.size(); i++) {
			Dato objeto2;
			char tipo='F';
			if(tokens.at(i)=="*"|| tokens.at(i)=="/" || tokens.at(i)=="+" || tokens.at(i)=="-") {
				tipo=='O';
				objeto2.valor.operador=tokens.at(i)[0];
			}
			if(tokens.at(i)!="*" && tokens.at(i)!="/" && tokens.at(i)!="+"&& tokens.at(i)!="-") {
				objeto2.valor.f_dato=atof(tokens.at(i).c_str());
			}
			objeto2.c_tipo=tipo;
			datos.push_back(objeto2);
		}
	} else if(tokens.at(0)=="B") {
		for (int i = 1; i < tokens.size(); i++) {
			Dato objeto3;
			char tipo='B';
			if(tokens.at(i)=="*" || tokens.at(i)=="/" || tokens.at(i)=="+" || tokens.at(i)=="-") {
				tipo=='O';
				objeto3.valor.operador=tokens.at(i)[0];
			}
			if(tokens.at(i)!="*" && tokens.at(i)!="/" && tokens.at(i)!="+" && tokens.at(i)!="-") {
				unsigned long temp= stoul(tokens.at(i),nullptr,10);
				objeto3.valor.ui_dato=temp;
			}
			objeto3.c_tipo=tipo;
			datos.push_back(objeto3);
		}
	}
	return datos;
}

Dato evaluarOperacion(vector<Dato> datos) {
	Dato dato;
	dato=datos.at(0);
	if(dato.c_tipo=='I'){
		stack<int>primerPila;
		for(int i=0; i < datos.size();i++){
			Dato dato2=datos.at(i);
			if(dato2.c_tipo=='*'){
				primerPila.push(dato2.valor.i_dato);
			}
		}
	}
}

vector<string> leerArchivo() {
	ifstream read;
	vector<string> temp;
	read.open("Examen_pila.txt");
	if (read.is_open()) {
		string buffer = "";
		while (getline(read, buffer)) {
			temp.push_back(buffer);
		}
		read.close();
	} else {
		cout << "No se encontro el archivo :( " << endl;
	}
	return temp;
}

int main(int argc, char** argv) {
	int opcion=1;
	stack<Dato> MiStack;
	while(opcion != 2) {
		cout << "Menu" << endl
		     << "1. Ejecutar" << endl
		     << "2. Salir "<<endl;
		cout << "Ingrese una opcion: " << endl;
		cin>>opcion;
		switch(opcion) {
			case 1: {
				//Ejecutar
				vector<string> listarArchivo;
				listarArchivo = leerArchivo();
				string linea="";
				for(int i=0; i < listarArchivo.size();i++){
					vector<string> line;
					line=tokenizer(listarArchivo[i]);
					vector<Dato> datos;
					datos =	convertirTokens(line);
				}
				break;
			}
			case 2: {
				//Salir
				cout<<"Gracias por usar el programa!"<<endl;
				break;
			}

			default: {
				cout <<"La opcion ingresada no es valida!"<<endl;
				break;
			}
		}
	}
	return 0;
}