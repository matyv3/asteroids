#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

void damePosicion(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void dibujarTablero(){
    // fila superior
    for(int i = 2; i < 148; i++){
        damePosicion(i, 5);
        printf("%c", 205);
    }
    // esquinas superiores
    damePosicion(1, 5);
    printf("%c", 201);
    damePosicion(148, 5);
    printf("%c", 187);
    // columnas
    for(int i = 6; i < 50; i++){
        damePosicion(1, i);
        printf("%c", 186); // imprime ||
    }
    //columna medio
    for(int i = 6; i < 50; i++){
        damePosicion(74, i);
        printf("%c", 186);
    }
    for(int i = 6; i < 50; i++){
        damePosicion(148, i);
        printf("%c", 186);
    }
    // esquinas inferiores
    damePosicion(1, 50);
    printf("%c", 200);
    damePosicion(148, 50);
    printf("%c", 188);
    // fila inferior
    for(int i = 2; i < 148; i++){
        damePosicion(i, 50);
        printf("%c", 205);
    }
    damePosicion(74, 50);
    printf("%c", 202);
    damePosicion(74, 5);
    printf("%c", 203);
}

void nave1(int x, int y){
    damePosicion(x, y);
    printf("    /\\ ");
    damePosicion(x, y+1);
    printf("  %c_%c%c_%c",186,178,178,186);
    damePosicion(x, y+2);
    printf("<%c%c%cP1%c%c%c>",178,178,178,178,178,178,178,178);
}
void nave2(int x, int y){
    damePosicion(x, y);
    printf("    /\\ ");
    damePosicion(x, y+1);
    printf("  %c_%c%c_%c",186,178,178,186);
    damePosicion(x, y+2);
    printf("<%c%c%cP2%c%c%c>",178,178,178,178,178,178,178,178);
}

void moverDerecha(int x, int y){
    nave1(x,y);
}

int main()
{
    // teclas
    char flechaArriba = 'H';
    char flechaIzquierda = 'K';
    char flechaDerecha = 'M';
    // posiciones
    int fondo = 47;
    int posJ1[2] = {30, fondo};
    int posJ2[2] = {105, fondo};

    nave1(posJ1[0],posJ1[1]);
    nave2(posJ2[0],posJ2[1]);

    dibujarTablero();



    //Preparar pantalla, dibujar bordes, vidas, puntaje, asteroide y personaje.
	//Inicializar las variables que sean necesarias para mi programa.

	bool gameOver = false;
	while(!gameOver){

		//En la primera iteración del programa, la condición del while se va a cumplir y siempre va a entrar acá.
		//Acá van todos los comandos que tienen que ocurrir segundo a segundo mientras el programa se ejecuta.
		//Por ejemplo: Mover las piedras hacia abajo o las balas hacia arriba; detectar las colisiones entre piedras y el personaje,
		//entre las piedras y las balas, o cuando una piedra llega al límite de la pantalla;

		//Si apretan un botón:
        if(kbhit()){
            char tecla = getch();
			//Dicho botón se va a guardar en la variable tecla.
			//Luego hay que realizar las acciones correspondientes si la tecla es la que esperamos.
			//Por ejemplo: mover el personaje o disparar.

                if( tecla == flechaDerecha){
                    moverDerecha(posJ1[0]+1, posJ1[1]);
                }
			}

		//Si se queda sin vida, se debe cambiar el valor de la variable gameOver para que salga del while.
	}
	//Pauso para que solo se cierre la pantalla con la letra c
    char teclaCerrar;
    while(teclaCerrar != 'c'){
        teclaCerrar = getch();
    }

    return 0;
}
