#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999991.0, menosinf=-9999999991.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}




// ------------------- Los tres metodos anteriores no se pueden modificar


int vertical(const Environment &estado, int fil, int col, int jugador) {
	int seguidas=0;
	for (int i=fil; seguidas<4 && i<7;i++) {
		if (estado.See_Casilla(i,col)%3 == jugador  || estado.See_Casilla(i,col) == 0)
      seguidas++;
      else
        break;
	}

	if (seguidas>=4)
		return 1;

	return 0;
}

int horizontal(const Environment &estado, int fil, int col, int jugador) {
	int seguidas=0;
	for (int j=col; seguidas<4 && j<7; j++) {
		if (estado.See_Casilla(fil,j)%3 == jugador || estado.See_Casilla(fil,j) == 0)
    seguidas++;
    else
      break;
	}
   int seguidas2=0;
  for (int j=col; seguidas2<4 && j>=0; j--) {
    if (estado.See_Casilla(fil,j)%3 == jugador || estado.See_Casilla(fil,j) == 0)
    seguidas2++;
    else
      break;
  }

	if (seguidas2 >= 4 && seguidas >=4)
		return 2;
  else if(seguidas >=4 || seguidas2 >=4 )
    return 1;
	return 0;
}

int diagonal_ABIZQ(const Environment &estado, int fil, int col, int jugador) {

	int seguidas = 0;

	int fila = fil;
  int columna = col;
  //Diagonal abajo izq
  for(int i=0; fila >=0 && columna >=0 && i<4;i++){
      if (estado.See_Casilla(fila,columna)%3 == jugador  || estado.See_Casilla(fila,columna) == 0)
        seguidas++;
      else
        break;

        fila--;
        columna--;
  }

  if (seguidas>=4)
    return 1;

  return 0;

}

int diagonal_ABDER(const Environment &estado, int fil, int col, int jugador) {

	int seguidas = 0;

	int fila = fil;
  int columna = col;
  //Diagonal abajo izq
  for(int i=0; fila >=0 && columna <=6 && i<4;i++){
      if (estado.See_Casilla(fila,columna)%3 == jugador  || estado.See_Casilla(fila,columna) == 0)
        seguidas++;
      else
        break;

        fila--;
        columna++;
  }

  if (seguidas>=4)
    return 1;

  return 0;

}
int diagonal_ARRDER(const Environment &estado, int fil, int col, int jugador) {

	int seguidas = 0;

	int fila = fil;
  int columna = col;
  //Diagonal abajo izq
  for(int i=0; fila <=6 && columna <=6 && i<4;i++){
      if (estado.See_Casilla(fila,columna)%3 == jugador  || estado.See_Casilla(fila,columna) == 0)
        seguidas++;
        else
          break;

        fila++;
        columna++;
  }

  if (seguidas>=4)
    return 1;

  return 0;

}

int diagonal_ARRIZQ(const Environment &estado, int fil, int col, int jugador) {

	int seguidas = 0;

	int fila = fil;
  int columna = col;
  //Diagonal abajo izq
  for(int i=0; fila <=6 && columna >=0 && i<4;i++){
      if (estado.See_Casilla(fila,columna)%3 == jugador  || estado.See_Casilla(fila,columna) == 0)
        seguidas++;
        else
          break;

        fila++;
        columna--;
  }

  if (seguidas>=4)
    return 1;

  return 0;

}



// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double valoracion(const Environment &estado, int jugador){
  int jugador_opuesto = 1;
  	if (jugador == 1)
  		jugador_opuesto = 2;

      int mios = 0;
      int suyos = 0;
      int num_fichas_mias = 0;
      int num_fichas_suyas = 0;

    	for (int i=0; i<7;i++) {
    		for (int j=0; j<7;j++) {
    			if (estado.See_Casilla(i,j) == jugador) {
            mios += vertical(estado, i, j, jugador);
    				mios += horizontal(estado, i, j, jugador);
            //cout << "Diagonales:" << endl;
            //cout << "Diagonales ARRIZQ" << endl;
    				mios += diagonal_ARRIZQ(estado, i, j, jugador);
            //cout << "Diagonales ARRDER" << endl;

            mios += diagonal_ARRDER(estado, i, j, jugador);
            //cout << "Diagonales ABIZQ" << endl;

            mios += diagonal_ABIZQ(estado, i, j, jugador);
            //cout << "Diagonales ABDER" << endl;

            mios += diagonal_ABDER(estado, i, j, jugador);
            num_fichas_mias++;
            //cout << "//Diagonales:" << endl;

    			}
    		}
    	}


  	for (int i=0; i<7;i++) {
  		for (int j=0; j<7;j++) {
  			if (estado.See_Casilla(i,j) == jugador_opuesto) {
          suyos += vertical(estado, i, j, jugador_opuesto);
  				suyos += horizontal(estado, i, j, jugador_opuesto);
  				suyos += diagonal_ARRIZQ(estado, i, j, jugador_opuesto);
          suyos += diagonal_ARRDER(estado, i, j, jugador_opuesto);
          suyos += diagonal_ABIZQ(estado, i, j, jugador_opuesto);
          suyos += diagonal_ABDER(estado, i, j, jugador_opuesto);
          num_fichas_suyas++;

  			}
  		}
  	}


    return (suyos - mios) + (num_fichas_suyas - num_fichas_mias);

}

// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return masinf; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return menosinf; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
      return valoracion(estado,jugador);

}




// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}

double Poda_AlfaBeta(Environment  &tablero,int jug,int limite,int profundidad,Environment::ActionType &accion,double alpha,double beta){

Environment::ActionType accion_sig;
  if(profundidad==limite || tablero.JuegoTerminado()){
      return ValoracionTest(tablero,jug);
    }
      int ultacc=6;
      Environment hijo = tablero.GenerateNextMove(ultacc);
      bool poda = false;
      double valor;
      ultacc=-1;
      while(ultacc<7 && !poda){
        if(!(tablero==hijo)){
          valor=Poda_AlfaBeta(hijo,jug,limite,profundidad-1,accion_sig,alpha,beta);
          //if(valor>=masinf)
            //valor=valor+profundidad;
          if(profundidad%2==0){
            if(valor>alpha){
              alpha=valor;
              accion = (ultacc < 0) ? static_cast <Environment::ActionType > (7) : static_cast <Environment::ActionType > (ultacc);
            }
          }else{
            beta = (beta < valor ) ? beta : valor;
          }
        }
        if(beta<=alpha) poda=true;
        else{
            hijo = tablero.GenerateNextMove(ultacc);
          }
      }
      if(profundidad%2==0){
        return alpha;
      }else{
        return beta;

      }


  }





// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;


    //--------------------- COMENTAR Desde aqui
    /*
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }
         */
    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    // valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);
    //cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;

    valor = Poda_AlfaBeta(actual_, jugador_, 0, PROFUNDIDAD_ALFABETA, accion, alpha, beta);

    int valor_actual = valoracion(actual_,jugador_);

    cout << "Valor a/b: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    cout << "valor actual:" << valor_actual << endl;


    return accion;
}
