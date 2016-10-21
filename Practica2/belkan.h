
#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include "conexion.h"
using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		//
		orientacion_real=3;
		mapa_orientacion=0;
		paso=0;
		tarea=-1;
		tarea_ant=-1;
		destino=-1;
		lado = actTURN_L;
		pk=0;
		pk1_x=0;
		pk1_y=0;
		pk2_y=0;
		pk2_x=0;
		pk1_x_real=0;
		pk1_y_real=0;
		pk2_x_real=0;
		pk2_y_real=0;
		orientado=false;
		segundo_for=false;
		ok=false;
		cosas_mochila=0;
		num_puertas=0;
		llave.x=0;
		llave.y=0;
		coger_llave=false;
		dejar_llave=false;

		for(int i=0;i<3;i++)
			despejado[i]=true;

		for (int i=0;i<7;i++){
				personajes[i].x==-1;
				personajes[i].y==-1;
			}
		///
		size_=200;
		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
					mapa_int[i][j]=-1;
		    }

		for (int i=0;i<100;i++){
		    for(int j=0;j<100;j++){
					if(i<3||i>96||j<3||j>96)
					mapa_solucion_[i][j]='P';
					else
		      mapa_solucion_[i][j]='?';
				}
			}




	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};

	//Ver mochila
	bool tengo(char c);
	//Buscar cosas en la vista
	void buscarObjetos();
	void buscarPK();
	void buscarPersonajes();
	//Comprobar pk1
	void checkPK1();
	//Estamos sobre un objeto
	void sobreObjeto();
	//Pulgarcito
	void pulgarcito(int i);
	//Dar objeto a personaje
	void objetoDePersonaje();
	//Guardar posion de personaje
	void guardarPersonaje(char p,int x,int y);
	//ruta deliberativa
	void rutaDeliberativa(int xd, int yd);

	void guardarPuerta(int x, int y);

	void pasandoPorPuerta();

private:
	//Variables de interaccion con el entorno grafico
	int size_;

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Propios
	struct cuadrado{
		int x;
		int y;
		int padre;
	};
	int paso;
	int destino;
	int tarea,tarea_ant;
	bool orientado;
	Agent::ActionType lado;
	int pk,	pk1_x,pk1_y,pk2_y,pk2_x;
	int pk1_x_real,pk1_y_real,pk2_x_real,pk2_y_real;
	int x_real,y_real,orientacion_real;
	int num_pasos,max_pasos,vueltas;
	cuadrado personajes[7];
	cuadrado puertas[10];
	 int num_puertas;
	cuadrado llave;
	int mapa_int[200][200];
	int mapa_orientacion;
	int casillas[3];
	char letras[3];
	bool despejado[3];
	int bloq_y,bloq_x;
	bool segundo_for;
	bool ok;
	int cosas_mochila;
	int rango;
	bool coger_llave,dejar_llave;

	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;

};

string ActionStr(Agent::ActionType);

#endif
