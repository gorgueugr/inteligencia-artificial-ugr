#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>

using namespace std;

bool  Agent::tengo(char c){
  bool teng = false;
  for(int i=0;i<5;i++)
    if(MOCHILLA_[i]==c)
      teng = true;

  return teng;
}

void PasarVectoraMapaCaracteresInt(int fila, int columna, int m[200][200], char *v, int brujula){
  //Sustituir valores de cada casilla por int
  int vint[10];
    for(int i=0;i<10;i++){
      //if(v[i]=='A')
        //vint[i]=20000;
      //else if(v[i]=='B')
      //  vint[i]=30000;
      //else
      if(v[i]=='P')
        vint[i]=50000;
      //else if(v[i]=='D')
      //  vint[i]=10000;
      else if(v[i]=='M')
          vint[i]=7000;
      else
        vint[i]=0;
        //cout<<"letra: " << v[i] << "valor: " << vint[i] << endl;
    }

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=m[fila-1][columna]>vint[1] || m[fila-1][columna]==-2 ? m[fila-1][columna] : vint[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]= m[fila-2][columna+i-1]>vint[2+i] ||  m[fila-2][columna+i-1]==-2 ? m[fila-2][columna+i-1] : vint[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]= m[fila-3][columna+j-2]>vint[5+j] || m[fila-3][columna+j-2]==-2 ? m[fila-3][columna+j-2] :vint[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]= m[fila][columna+1]>vint[1] || m[fila][columna+1]==-2 ? m[fila][columna+1] : vint[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]= m[fila+i-1][columna+2]>vint[2+i] ||  m[fila+i-1][columna+2]==-2 ? m[fila+i-1][columna+2] : vint[2+i] ;
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]= m[fila+j-2][columna+3]>vint[5+j] || m[fila+j-2][columna+3]==-2 ? m[fila+j-2][columna+3] : vint[5+j] ;
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]= m[fila+1][columna]>vint[1] || m[fila+1][columna]==-2 ? m[fila+1][columna] : vint[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]= m[fila+2][columna+1-i]>vint[2+i] || m[fila+2][columna+1-i]==-2 ? m[fila+2][columna+1-i] : vint[2+i] ;
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=m[fila+3][columna+2-j]>vint[5+j] || m[fila+3][columna+2-j]==-2 ? m[fila+3][columna+2-j] : vint[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]= m[fila][columna-1]>vint[1] || m[fila][columna-1]==-2 ? m[fila][columna-1] : vint[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=m[fila+1-i][columna-2]>vint[2+i] || m[fila+1-i][columna-2]==-2 ? m[fila+1-i][columna-2] : vint[2+i] ;
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]= m[fila+2-j][columna-3]>vint[5+j] || m[fila+2-j][columna-3]==-2 ? m[fila+2-j][columna-3] :  vint[5+j];
		}

                break;
    }

}
void PasarVectoraMapaCaracteresSolucion(int fila, int columna, char m[100][100], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}

// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}



// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}


void Agent::buscarObjetos(){
  //destino=-1;
  for(int i=1;i<10;i++){
    if(SURFACE_[i]>='0' && SURFACE_[i]<='9'){
      destino=i;
      tarea=1; //ir a destino
      paso=0;
    }
  }
  switch (SURFACE_[destino]) {
    case '1':
    case '3':
    case '7':
    tarea=-1;
    break;
  }

}
void Agent::buscarPK(){
  for(int i=1;i<10;i++){//Buscar PK en la vista
    if(VISTA_[i]=='K'){
      destino=i;
      tarea=1; //ir a destino
      paso=0;
    }
  }
}

void Agent::buscarPersonajes(){
  for(int i=2;i<10;i++){//Buscar PK en la vista
    if((SURFACE_[i]>='e' && SURFACE_[i]<='p' ) || VISTA_[i]=='D'){
            destino=i;
            tarea=1;
            paso=0;
            //cout << "Guardando posción de personaje: " << x_ << " / " << y_ << endl;

            //guardarPersonaje(SURFACE_[i]);
    }
  }
}

void Agent::guardarPersonaje(char p,int x,int y){
  switch (p) {
    case 'e': // Aldenao de frente
    case 'f': // Aldeano de espaldas
      personajes[0].x=x;
      personajes[0].y=y;
      break;
    case 'g': // Princesa Capichosa
    case 'h': // Princesa Caprichosa
      personajes[1].x=x;
      personajes[1].y=y;
      break;
    case 'i': // Leonardo Di Caprio
    case 'j': // Leonardo Di Caprio
      personajes[2].x=x;
      personajes[2].y=y;
      break;
    case 'k': // Princeso Valeroso
    case 'l': // Princeso Valeroso
      personajes[3].x=x;
      personajes[3].y=y;
      break;
    case 'm': // Bruja Malvada
    case 'n': // Bruja Malvada
      personajes[4].x=x;
      personajes[4].y=y;
      break;
    case 'o': // Profe IA
    case 'p': // Profe IA
      personajes[5].x=x;
      personajes[5].y=y;
      break;

    break;
    }
}

void Agent::guardarPuerta(int x,int y){
  coger_llave=true;

  for(int i=0;i<num_puertas;i++){
    if(puertas[i].x==x && puertas[i].y==y)
      return;
  }
  if(num_puertas==9)
    return;

  puertas[num_puertas].x=x;
  puertas[num_puertas].y=y;
  puertas[num_puertas].padre=0;

  num_puertas++;

}

void Agent::pasandoPorPuerta(){
  for(int i=0;i<num_puertas;i++){
    if(puertas[i].x==x_ && puertas[i].y==y_){
      puertas[i].padre++;
      if(puertas[i].padre%2==0)
      dejar_llave=true;
    }
  }
}

void Agent::objetoDePersonaje(){
  switch (SURFACE_[1]) {
    case 'e': // Aldenao de frente
    case 'f': // Aldeano de espaldas
      if(EN_USO_=='7'){
        tarea=8;//DAR
      }else if(tengo('7')){
        tarea=6;
        paso=0;
      }
      break;
    case 'g': // Princesa Capichosa
    case 'h': // Princesa Caprichosa
        if(EN_USO_=='4'){
          tarea=8;//DAR
        }else if(tengo('4')){
          tarea=6;
          paso=0;
        }
      break;
    case 'i': // Leonardo Di Caprio
    case 'j': // Leonardo Di Caprio
        if(EN_USO_=='5'){
          tarea=8;//DAR
        }else if(tengo('5')){
          tarea=6;
          paso=0;
        }
      break;

    case 'k': // Princeso Valeroso
    case 'l': // Princeso Valeroso
      if(EN_USO_=='4'){
        tarea=8;//DAR
      }else if(tengo('4')){
        tarea=6;
        paso=0;

      }
      break;
    case 'm': // Bruja Malvada
    case 'n': // Bruja Malvada
      if(EN_USO_=='8'){
        tarea=8;//DAR
      }else if(tengo('8')){
        tarea=6;
        paso=0;
      }
      break;
    case 'o': // Profe IA
    case 'p': // Profe IA
      if(EN_USO_=='9'){
        tarea=8;//DAR
      }else if(tengo('9')){
        tarea=6;//Cambiar
        paso=0;
      }
      break;
    }

}

void Agent::sobreObjeto(){
  if(EN_USO_=='-' && cosas_mochila<=3)
    tarea=4;//Manos vacias --> recoger
  else if(EN_USO_!='-' && cosas_mochila<=2) //Si la mochila no esta llena
      tarea=5;//Manos llenas --> Guardar --> recoger
    else
      tarea=-1;

      switch (SURFACE_[0]) {
        case '1':
        case '3':
        case '7':
        tarea=-1;
        break;
        case '2':
          llave.x=x_;
          llave.y=y_;
          if(!coger_llave)
            tarea=-1;
        break;
      }
      if(tarea==4){
        switch (SURFACE_[0]) {
          case '4':
            rutaDeliberativa(personajes[1].x,personajes[1].y);
          break;
          case '5':
            rutaDeliberativa(personajes[2].x,personajes[2].y);
          break;
          case '8':
            rutaDeliberativa(personajes[4].x,personajes[4].y);
          break;
          case '9':
            rutaDeliberativa(personajes[5].x,personajes[5].y);
          break;
          case '2':
            if(coger_llave){
              for(int i=0;i<num_puertas;i++){
              if(puertas[i].padre==0){
                  rutaDeliberativa(puertas[i].x,puertas[i].y);
                }
              }
              llave.x=0;
              llave.y=0;
              coger_llave=false;
            }else{
              tarea=-1;
            }
          break;
        }
      }

}

void Agent::pulgarcito(int i /*distancia*/){
  switch (orientacion_) {
    case 0: // norte
        //Lejos
        //Delante
        if( y_-i>=0){
          casillas[0]=mapa_int[y_-i][x_];
            if(mapa_objetos_[y_-i][x_]>='e' && mapa_objetos_[y_-i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
              casillas[0]=7000;
            }
          letras[0]=mapa_entorno_[y_-i][x_]; //delante
        }else{
          casillas[0]=0;
          letras[0]='P';
        }
        //IZQ
        if( x_-i>=0){
          casillas[1]=mapa_int[y_][x_-i];
            if(mapa_objetos_[y_][x_-i]>='e' && mapa_objetos_[y_][x_-i]<='z'){ //Si hay un personaje en esa casilla en ese momento
              casillas[1]=7000;
            }
          letras[1]=mapa_entorno_[y_][x_-i]; //izq
        }else{
          casillas[1]=0;
          letras[1]='P';
        }
        //Derecha
        if( x_+i<=199){
        casillas[2]=mapa_int[y_][x_+i];
          if(mapa_objetos_[y_][x_+i]>='e' && mapa_objetos_[y_][x_+i]<='z'){ //Si hay un personaje en esa casilla en ese momento
            casillas[2]=7000;
          }
        letras[2]=mapa_entorno_[y_][x_+i]; //Derecha
        }else{
          casillas[2]=0;
          letras[2]='P';
        }
      break;
    case 1: // este
      //Lejos
      if( x_+i<=199){
        casillas[0]=mapa_int[y_][x_+i]; //delante
        if(mapa_objetos_[y_][x_+i]>='e' && mapa_objetos_[y_][x_+i]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[0]=7000;
        }
        letras[0]=mapa_entorno_[y_][x_+i]; //delante
      }else{
        casillas[0]=0;
        letras[0]='P';
      }
      if( y_-i>=0){
        casillas[1]=mapa_int[y_-i][x_]; //izq
        if(mapa_objetos_[y_-i][x_]>='e' && mapa_objetos_[y_-i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[1]=7000;
        }
        letras[1]=mapa_entorno_[y_-i][x_]; //izq
      }else{
        casillas[1]=0;
        letras[1]='P';
      }
      if( y_+i<=199){
        casillas[2]=mapa_int[y_+i][x_]; //Derecha
        if(mapa_objetos_[y_+i][x_]>='e' && mapa_objetos_[y_+i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[2]=7000;
        }
        letras[2]=mapa_entorno_[y_+i][x_]; //Derecha
      }else{
          casillas[2]=0;
          letras[2]='P';
        }
    break;
    case 2: // sur
      //Lejos
      if( y_+i<=199){
        casillas[0]=mapa_int[y_+i][x_]; //delante
        if(mapa_objetos_[y_+i][x_]>='e' && mapa_objetos_[y_+i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[0]=7000;
        }
        letras[0]=mapa_entorno_[y_+i][x_]; //delante
      }else{
          casillas[0]=0;
          letras[0]='P';
      }
      if( x_+i<=199){
        casillas[1]=mapa_int[y_][x_+i]; //izq
        if(mapa_objetos_[y_][x_+i]>='e' && mapa_objetos_[y_][x_+i]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[1]=7000;
        }
        letras[1]=mapa_entorno_[y_][x_+i]; //izq
      }else{
        casillas[1]=0;
        letras[1]='P';
      }
      if( y_-i>=0){
        casillas[2]=mapa_int[y_][x_-i]; //Derecha
        if(mapa_objetos_[y_][x_-i]>='e' && mapa_objetos_[y_][x_-i]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[2]=7000;
        }
        letras[2]=mapa_entorno_[y_][x_-i]; //Derecha
      }else{
        casillas[2]=0;
        letras[2]='P';
      }

      break;
    case 3: // oeste
        //Lejos
      if( x_-i>=0){
        casillas[0]=mapa_int[y_][x_-i]; //delante
        if(mapa_objetos_[y_][x_-i]>='e' && mapa_objetos_[y_][x_-i]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[0]=7000;
        }
        letras[0]=mapa_entorno_[y_][x_-i]; //delante
      }else{
        casillas[0]=0;
        letras[0]='P';
      }
      if( y_+i<=199){
        casillas[1]=mapa_int[y_+i][x_]; //izq
        if(mapa_objetos_[y_+i][x_]>='e' && mapa_objetos_[y_+i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[1]=7000;
        }
        letras[1]=mapa_entorno_[y_+i][x_]; //izq
      }else{
        casillas[1]=0;
        letras[1]='P';
      }
      if( y_-i>=0){
        casillas[2]=mapa_int[y_-i][x_]; //Derecha
        if(mapa_objetos_[y_-i][x_]>='e' && mapa_objetos_[y_-i][x_]<='z'){ //Si hay un personaje en esa casilla en ese momento
          casillas[2]=7000;
        }
        letras[2]=mapa_entorno_[y_-i][x_]; //Derecha
      }else{
        casillas[2]=0;
        letras[2]='P';
      }
    break;
  }

}




void Agent::rutaDeliberativa(int xd, int yd/*Posicion del personaje*/){
    if(xd<1||yd<1||xd>199||yd>199)
      return ;

  class pilaCuadrados{
    public:
      cuadrado  * pila;
      int punt,ultimo;
      bool esta(int x,int y){
        for(int i=0;i<=ultimo;i++){
          if(pila[i].x==x && pila[i].y==y)
          return true;
          }
        return false;
      }
      pilaCuadrados(){
        pila = new cuadrado[10000];
        punt = 0;
        ultimo = 0;
      }

    };

    pilaCuadrados * pCu = new pilaCuadrados;
    cout << "///////////////" << endl;
    cout << "Calculando ruta" << endl;
    cout << "///////////////" << endl;
    cout << "salida: " << x_ << " / " << y_ << endl;
    cout << "destino: " << xd << " / " << yd << endl;
    cout << "///////////////" << endl;

      pCu->punt=0;
      pCu->ultimo=0;
      pCu->pila[0].x=x_;
      pCu->pila[0].y=y_;
      pCu->pila[0].padre=-1;
      //cout << "inicializado correctamente " << endl;
      while((pCu->pila[pCu->punt].x!=xd || pCu->pila[pCu->punt].y!=yd) && pCu->punt<=pCu->ultimo && pCu->ultimo<9995 ){
        //cout<<"puntero: " << pCu->punt << endl;
        //Comprobar nodo viable
        if(pCu->pila[pCu->punt].y<=199   \
          && pCu->pila[pCu->punt].y>=0   \
          && pCu->pila[pCu->punt].x<=199 \
          && pCu->pila[pCu->punt].x>=0   \
          && mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]!='?' \
        ){


        if(mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=='S' \
          ||mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=='T'  \
          ||mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=='K'  \
          ||(mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=='B' &&(EN_USO_=='6'||tengo('6') )) \
          ||(mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=='D' && (EN_USO_=='2'||tengo('2') ) ) \
        ){
          //NORTE
          if(!pCu->esta(pCu->pila[pCu->punt].x,pCu->pila[pCu->punt].y-1)){
            pCu->ultimo++;
            pCu->pila[pCu->ultimo].x=pCu->pila[pCu->punt].x;
            pCu->pila[pCu->ultimo].y=pCu->pila[pCu->punt].y-1;
            pCu->pila[pCu->ultimo].padre=pCu->punt;
          }
          //ESTE
          if(!pCu->esta(pCu->pila[pCu->punt].x+1,pCu->pila[pCu->punt].y)){
            pCu->ultimo++;
            pCu->pila[pCu->ultimo].x=pCu->pila[pCu->punt].x+1;
            pCu->pila[pCu->ultimo].y=pCu->pila[pCu->punt].y;
            pCu->pila[pCu->ultimo].padre=pCu->punt;
          }
          //SUR
          if(!pCu->esta(pCu->pila[pCu->punt].x,pCu->pila[pCu->punt].y+1)){
            pCu->ultimo++;
            pCu->pila[pCu->ultimo].x=pCu->pila[pCu->punt].x;
            pCu->pila[pCu->ultimo].y=pCu->pila[pCu->punt].y+1;
            pCu->pila[pCu->ultimo].padre=pCu->punt;
          }
          //OESTE
          if(!pCu->esta(pCu->pila[pCu->punt].x-1,pCu->pila[pCu->punt].y)){
            pCu->ultimo++;
            pCu->pila[pCu->ultimo].x=pCu->pila[pCu->punt].x-1;
            pCu->pila[pCu->ultimo].y=pCu->pila[pCu->punt].y;
            pCu->pila[pCu->ultimo].padre=pCu->punt;
          }
        }
      }
        pCu->punt++;
      }
      //Crear camino
      if(pCu->pila[pCu->punt].x==xd && pCu->pila[pCu->punt].y==yd){
        cout << "Camino encontrado" << endl;
        cout << "Construyendo ruta" << endl;
      while(pCu->pila[pCu->punt].padre!=-1){
        //cout << "punto :" << pCu->punt << "/ " << pCu->pila[pCu->punt].x  << "/ " <<  pCu->pila[pCu->punt].y << endl;
        mapa_int[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]=-2;
        mapa_entorno_[pCu->pila[pCu->punt].y][pCu->pila[pCu->punt].x]='?';
        pCu->punt=pCu->pila[pCu->punt].padre;
      }
      cout << "///////////////" << endl;
      cout << "Ruta creada" << endl;
    }else{
      cout << "Camino NO encontrado" << endl;
    }
      delete [] pCu->pila;
      delete pCu;
      cout << "///////////////" << endl;



}
// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
  	if (REINICIADO_){
  		// Lo que tengas que hacer si eres reposicionado en el juego


          for (int i=0;i<200;i++)
      		    for(int j=0;j<200;j++){
      		      mapa_entorno_[i][j]='?';
      		      mapa_objetos_[i][j]='?';
                mapa_int[i][j]=-1;
      		    }

              for (int i=0;i<7;i++){
          				personajes[i].x==-1;
                  personajes[i].y==-1;
                }

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


              cosas_mochila=0;

              REINICIADO_=false;
              cout << "HAS SIDO REINICIADO" << endl;
              cout << MENSAJE_ << endl;
  	}
  if(MENSAJE_!="Has chocado con un obstaculo movil. "){
      	switch(last_accion_){
    	  case 0: //avanzar
    	  switch(orientacion_){
    	    case 0: // norte
    		    y_--;
    		    break;
    	    case 1: // este
    		    x_++;
    		    break;
    	    case 2: // sur
    		    y_++;
    		    break;
    	    case 3: // este
    		    x_--;
    		    break;
    	  }
        if(orientado)
        switch(orientacion_real){
    	    case 0: // norte
    		    y_real--;
    		    break;
    	    case 1: // este
    		    x_real++;
    		    break;
    	    case 2: // sur
    		    y_real++;
    		    break;
    	    case 3: // este
    		    x_real--;
    		    break;
    	  }
    	  break;
    	  case 1: // girar izq
    		  orientacion_=(orientacion_+3)%4;
          if(orientado)
          orientacion_real=(orientacion_real+3)%4;

    		  break;
    	  case 2: // girar dch
    		  orientacion_=(orientacion_+1)%4;
          if(orientado)
          orientacion_real=(orientacion_real+1)%4;

    		  break;
    	}
    }

    	// Comprobacion para no salirme del rango del mapa
    	bool algo_va_mal=false;
    	if (y_<0){
    		y_=0;
    		algo_va_mal=true;
    	}
    	else if (y_>199){
    		y_=199;
    		algo_va_mal=true;
    	}
    	if (x_<0){
    		x_=0;
    		algo_va_mal=true;
    	}
    	else if (x_>199){
    		x_=199;
    		algo_va_mal=true;
    	}

    	if (algo_va_mal){
    		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
    	}

    	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
    	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);
      //Pasar vista al mapa int
      PasarVectoraMapaCaracteresInt(y_,x_,mapa_int,VISTA_,orientacion_);

      //Pasar vista al mapa solucion si estamos orientados
      if(orientado)
      PasarVectoraMapaCaracteresSolucion(y_real,x_real,mapa_solucion_,VISTA_,orientacion_real);

    	env->ActualizarMatrizUsuario(mapa_entorno_);


}

// -----------------------------------------------------------
Agent::ActionType Agent::Think()
{
	Agent::ActionType accion = actFORWARD; // Por defecto avanza
  bool reevaluar=false,personaje_delante=false;
  string str1,str2;
  int aux_x,aux_y,menor;

	// tomar accion
  do{

    reevaluar=false;
    if(last_accion_==actFORWARD)
      mapa_int[y_][x_]++;

    //----------------------------------------------------------------------------------------------------------------//
    //----------------------------------------------------------------------------------------------------------------//

      buscarPersonajes();

    //Buscar objetos en la vista
    if(cosas_mochila<3){
        buscarObjetos();
    }
      //----------------------------------------------------------------------------------------------------------------//
      //----------------------------------------------------------------------------------------------------------------//

    //Si tenemos que calcular la Orientacion
  if(pk<=1){
      if(tarea!=1)
        buscarPK();

        //if(pk==1) //Calcular si es el pk1 para no volver a ir
          //checkPK1();
      //}
  }
  //----------------------------------------------------------------------------------------------------------------//
  //----------------------------------------------------------------------------------------------------------------//



  //----------------------------------------------------------------------------------------------------------------//
  //----------------------------------------------------------------------------------------------------------------//

  //SI la siguiente casilla esta bloqueada por un personaje

  if(SURFACE_[1]>='e' && SURFACE_[1]<='q'){
    switch(orientacion_){
        case 0: // norte
        aux_y=y_-1;
        aux_x=x_;
        break;
        case 1: // este
        aux_y=y_;
        aux_x=x_+1;
          break;
        case 2: // sur
        aux_y=y_+1;
        aux_x=x_;
          break;
        case 3: // oeste
          aux_y=y_;
          aux_x=x_-1;
          break;
      }
      guardarPersonaje(SURFACE_[1],aux_x,aux_y);
      personaje_delante=true;
      objetoDePersonaje();
  }else{
      personaje_delante=false;
  }
  //DELANTE DE PUERTA
  if(VISTA_[1]=='D'){
    switch(orientacion_){
        case 0: // norte
        aux_y=y_-1;
        aux_x=x_;
        break;
        case 1: // este
        aux_y=y_;
        aux_x=x_+1;
          break;
        case 2: // sur
        aux_y=y_+1;
        aux_x=x_;
          break;
        case 3: // oeste
          aux_y=y_;
          aux_x=x_-1;
          break;
      }
      guardarPuerta(aux_x,aux_y);
      //if(EN_USO_!='2' && !tengo('2') && llave.x!=0 && llave.y!=0 )
        //rutaDeliberativa(llave.x,llave.y);

      }

  if(VISTA_[0]=='D'){
    pasandoPorPuerta();
  }
  //----------------------------------------------------------------------------------------------------------------//
  //----------------------------------------------------------------------------------------------------------------//

  //Estoy sobre un objeto
  if(SURFACE_[0]!='?'){
      sobreObjeto();
  }
  //----------------------------------------------------------------------------------------------------------------//
  //----------------------------------------------------------------------------------------------------------------//

  if( tarea==-1  \
      || (tarea==1) && \
      ( (VISTA_[1]=='B'  && EN_USO_!='6' ) \
      || (VISTA_[1]=='A' && EN_USO_!='0' ) \
      || VISTA_[1]=='P' || VISTA_[1]=='M' || VISTA_[1]=='D' \
      || (SURFACE_[1]>='e' && SURFACE_[1]<='q') ) \
    ){

          //pulgarcitoCerca();
          for(int i=0;i<3;i++)
      			despejado[i]=true;


          int j=1;
          do{
            j++;

            pulgarcito(j);
            for(int i=0;i<3;i++){
              if((letras[i]=='B' && /* !tengo('6')  && */ EN_USO_!='6') \
              ||(letras[i]=='A' && /* !tengo('0') && */ EN_USO_!='0')  \
              ||letras[i]=='M'||letras[i]=='P'||letras[i]=='D'   \
              || casillas[i]>=7000 \
            ){
                despejado[i]=false;
              }
            }
            tarea=7;
            menor=7000;
            destino=-1;
            for(int i=0;i<3;i++){
              if(casillas[i]<menor && despejado[i]){
                 menor=casillas[i];
                destino=i;
              }
          }

        }while(menor>-1 && j<99);
          //Buscar el mejor destino
            //if(j!=rango)
              //cout << "rango: " << j << endl;

            rango = j;

            pulgarcito(1);
          if( !despejado[destino]                       \
            || casillas[destino]>=7000                  \
            || segundo_for && last_accion_!=actFORWARD  \
            || menor>-1                                 \
            || (letras[destino]=='B'&& EN_USO_!='6')    \
            || (letras[destino]=='A'&& EN_USO_!='0')    \
            || (letras[destino]=='D'&& EN_USO_!='2')    \
            || personaje_delante || j==99               \
            || casillas[0]==-2||casillas[1]==-2         \
            ||casillas[2]==-2                           \
            ||dejar_llave                               \
          ){

              tarea=7;
              ok=false;
              while(!ok){
              menor=7000;
              destino=-1;
              for(int i=0;i<3;i++){
                //cout << "Segundo for: "<< "pos: " << i << "valor: " << casillas[i] << endl;
                if(casillas[i]<menor){
                  menor=casillas[i];
                  destino=i;
                }
              }

              ok=true;

              switch (letras[destino]) {
                case 'B':
                  if(EN_USO_=='6'){
                    ok=true;
                  }else if(tengo('6') && (VISTA_[0]=='T' || VISTA_[0]=='S' || VISTA_[0]=='K' || VISTA_[0]=='B')  ){
                    ok=true;
                    tarea=6;
                    paso=0;
                  }else{
                    ok=false;
                    casillas[destino]=7000;
                  }
                break;
                case 'A':
                  if(EN_USO_=='0'){
                    ok=true;
                  }else if(tengo('0') && (VISTA_[0]=='T' || VISTA_[0]=='S' || VISTA_[0]=='K')){
                    ok=true;
                    tarea=6;
                    paso=0;
                  }else{
                    ok=false;
                    casillas[destino]=7000;
                  }
                break;
                case 'D':
                  if(EN_USO_=='2'){
                    ok=true;
                  }else if(tengo('2')){
                    ok=true;
                    tarea=6;
                    paso=0;
                  }else if(llave.x!=0 && llave.y!=0){
                    ok=false;
                    casillas[destino]=7000;
                    rutaDeliberativa(llave.x,llave.y);
                  }else{
                    ok=false;
                    casillas[destino]=7000;
                  }
                break;
              }
              if(personaje_delante && destino==0){
                casillas[0]=7000;
                ok=false;
              }

            }
            if((EN_USO_=='2' || tengo('2')) && dejar_llave && VISTA_[0]!='D'){
                if(EN_USO_=='2'){
                  tarea=9;
                  llave.x=x_;
                  llave.y=y_;
                  coger_llave=false;
                  dejar_llave=false;
                }else if(tengo('2')){
                  tarea=6;
                }
              }




              segundo_for=true;
            }else{
              segundo_for=false;
            }



    }
  //----------------------------------------------------------------------------------------------------------------//

  //----------------------------------------------------------------------------------------------------------------//
  //Estoy sobre un pk
    if(VISTA_[0]=='K'){
      if(pk<1)
        tarea=2;//Primer pk
      else if(pk<2 && (pk1_x!=x_ || pk1_y!=y_)) //Segundo pk diferente del primero
        tarea=3;//Segundo pk
    }

  //----------------------------------------------------------------------------------------------------------------//
  //SALIDA POR PANTALLA
  if(tarea_ant!=tarea){

    cout << "///////////////" << endl;

    switch (tarea) {
      case 1:
        cout << "He visto algo voy a por el!! " <<endl;
      break;
      case 2:
        cout << "El primer pk que veo, lo recordare. " <<endl;
      break;
      case 3:
        cout << "El segundo pk que veo, ya puedo saber la orientación!" <<endl;
      break;
      case 4:
        cout << "Me llevo esto, por si acaso. " <<endl;
      break;
      case 5:
        cout << "Guardando objeto la mochila. " <<endl;

      break;
      case 6:
        cout << "Nunca encuentro nada en la mochila, Donde estara?!!. " <<endl;
      break;
      case 7:
        cout << "Explorando el mundo " <<endl;
      break;
      case 8:
        cout << "Toma un regalo!! " <<endl;
      break;
      case 9:
        cout << "Dejo esto!" <<endl;
      break;

    }
    cout << "MOCHILA" << endl;
      for(int i=0;i<5;i++)
        cout <<" " << MOCHILLA_[i];
    cout << endl;
    cout << "En uso: " << EN_USO_ << endl;
    cout << "--------------" << endl;
    cout << MENSAJE_ << endl;
    cout << "///////////////" << endl;

  }
  tarea_ant=tarea;
  //----------------------------------------------------------------------------------------------------------------//

//TAREAS
  switch (tarea) {
    case 1: //Ir a destino
        switch (destino) {
            case 4:
              paso=1;
            case 8:
            case 9:
              lado=actTURN_R;
          break;
            case 2:
              paso=1;
            case 5:
            case 6:
              lado=actTURN_L;
          break;
            case 1:
            case 3:
            case 7:
              paso=0;
            break;
          }
          //cout << "destino: " << destino << "paso: " << paso << endl;

        switch (paso) {
          case 0:
          case 1:
          case 2:
            accion=actFORWARD;
            paso++;
            destino=-1;
          break;
          case 3:
            accion=lado;
            paso=0;
            destino=-1;
            tarea=-1;
          break;
        }
    break;
    case 2://Primera ocurrencia de PK
      pk1_x=x_;
      pk1_y=y_;
      pk++;
      reevaluar=true;
      tarea=-1;
      //Extracción de pos del mensaje
      str1=MENSAJE_.substr(8,3);
      str2=MENSAJE_.substr(MENSAJE_.find("na:")+4,3);
      pk1_y_real= stoi(str1,nullptr,0);
      pk1_x_real= stoi(str2,nullptr,0);
      //

      tarea=-1;
    break;
    case 3: //Segunda ocurrencia de PK
      pk2_y=y_;
      pk2_x=x_;
      pk++;
      //-------------------//
      //Extracción pos del mensaje
      str1="";
      str2="";
      str1=MENSAJE_.substr(MENSAJE_.find(":")+2,(MENSAJE_.find("c")-1)-(MENSAJE_.find(":")+1));
      str2=MENSAJE_.substr(MENSAJE_.find("na:")+4,(MENSAJE_.find("."))-(MENSAJE_.find("na:")+4));
      pk2_y_real= stoi(str1,nullptr,0);
      pk2_x_real= stoi(str2,nullptr,0);


      x_real=pk2_x_real;
      y_real=pk2_y_real;
      orientado=true;

      //-------------------//

      if(pk2_x_real-pk1_x_real==pk2_x-pk1_x && pk2_y_real-pk1_y_real==pk2_y-pk1_y){
        cout << "Orientación norte" << endl; //NORTE

          orientacion_real=orientacion_;

          //-------------------//
          pk2_y=pk2_y-pk2_y_real;
          pk2_x=pk2_x-pk2_x_real;
          //-------------------//

          for(int i=0;i<100;i++)
            for(int j=0;j<100;j++){
              if(mapa_solucion_[i][j]=='?')
                mapa_solucion_[i][j]=mapa_entorno_[pk2_y+i][pk2_x+j];
            }

          mapa_orientacion=0;
          //-------------------//

      }else if(pk2_x_real-pk1_x_real==(-1)*(pk2_x-pk1_x) && pk2_y_real-pk1_y_real==(-1)*(pk2_y-pk1_y)){
          //-------------------//
          cout << "Orientación sur" << endl;
          //-------------------//

          //-------------------//
          orientacion_real=(orientacion_+2)%4;

          pk2_y=pk2_y+pk2_y_real;
          pk2_x=pk2_x+pk2_x_real;

          for(int i=0;i<100;i++)
            for(int j=0;j<100;j++)
            if(mapa_solucion_[i][j]=='?')
              mapa_solucion_[i][j]=mapa_entorno_[pk2_y-i][pk2_x-j];

              mapa_orientacion=2;
          //-------------------//


          //SUR
      }else if(pk2_x_real-pk1_x_real==(-1)*(pk2_y-pk1_y) && pk2_y_real-pk1_y_real==(pk2_x-pk1_x)){
          //-------------------//
          cout << "Orientación este" << endl;
          //-------------------//

          //-------------------//
          orientacion_real=(orientacion_+1)%4;
          //ESTE//
          aux_y=pk2_y+pk2_x_real;
          aux_x=pk2_x-pk2_y_real;

          for(int i=0;i<100;i++)
            for(int j=0;j<100;j++)
            if(mapa_solucion_[i][j]=='?')
              mapa_solucion_[i][j]=mapa_entorno_[aux_y-j][aux_x+i];
          //ESTE//
          mapa_orientacion=1;
          //-------------------//


      }else if(pk2_x_real-pk1_x_real==(pk2_y-pk1_y) && pk2_y_real-pk1_y_real==(-1)*(pk2_x-pk1_x)){
          //-------------------//
          cout << "Orientación oeste" << endl;
          //-------------------//

          //-------------------//
          orientacion_real=(orientacion_+3)%4;
          //OESTE
              aux_y=pk2_y-pk2_x_real;
              aux_x=pk2_x+pk2_y_real;

              for(int i=0;i<100;i++)
                for(int j=0;j<100;j++)
                if(mapa_solucion_[i][j]=='?')
                  mapa_solucion_[i][j]=mapa_entorno_[aux_y+j][aux_x-i];
              //OESTE//
              mapa_orientacion=3;
              //OESTE//
            //-------------------//

      }else{ //Si no se puede calcular la orientacion se descarta el punto
        //-------------------//

        pk=1;
        orientado=false;
        //-------------------//
      }
      //Poner precipicios y suelo a S//
      for(int i=0;i<100;i++)
        for(int j=0;j<100;j++){
          if(i<3||i>96||j<3||j>96)
            mapa_solucion_[i][j]='P';
        }
      //-------------------//

      reevaluar=true;
      tarea=-1;
    break;
    case 4: //recoger objeto
      accion=actPICKUP;
      tarea=-1;
      paso=0;
    break;
    case 5: //Guardar en mochila
      accion=actPUSH;
      cosas_mochila++;
      tarea=-1;
      paso=0;
    break;
    case 6: //Cambiar objeto ----|
        if(EN_USO_=='-')
          paso=1;
        switch (paso) {
          case 0:
            accion=actPUSH;
            cosas_mochila++;
            paso++;
          break;
          case 1:
            accion=actPOP;
            cosas_mochila--;
            paso=0;
            tarea=-1;
          break;
        }
    break;
    case 7://Ir por lado menor
      switch (destino) {
        case 0:
          accion=actFORWARD;
        break;
        case -1:
        case 1:
          accion=actTURN_L;
        break;
        case 2:
          accion=actTURN_R;
        break;
      }
      tarea=-1;
      paso=0;
    break;
    case 8: //Dar Objeto
      accion=actGIVE;
      tarea=-1;
      paso=0;
    break;
    case 9: //Soltar Objeto
      accion=actPUTDOWN;
      tarea=-1;
      paso=0;
      break;
    default:
      accion=actFORWARD;
      tarea=-1;
      paso=0;
    break;
  }
}while(reevaluar);


	// recuerdo la ultima accion realizada
	last_accion_ = accion;

	return accion;

}
