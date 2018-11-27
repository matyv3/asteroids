#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>

// posiciones jugadores
int posJ1[2];
int posJ2[2];
// limites
int fondo;
int minXJ1;
int maxXJ1;
int minXJ2;
int maxXJ2;
int limiteYSuperior;
int limiteYInferior;
// tablero
int vidasJ1;
int vidasJ2;
int puntosJ1;
int puntosJ2;

void damePosicion(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void tableroSuperior(){
    damePosicion(2, 2);
    printf("JUGADOR 1");
    damePosicion(2, 4);
    printf("Vidas: %i", vidasJ1);
    damePosicion(16,4);
    printf("Puntos: %i", puntosJ1);

    damePosicion(138, 2);
    printf("JUGADOR 2");
    damePosicion(122, 4);
    printf("Vidas: %i", vidasJ2);
    damePosicion(138,4);
    printf("Puntos: %i", puntosJ2);

    damePosicion(70, 2);
    printf("ASTEROIDS");
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

void nave1(){
    damePosicion(posJ1[0], posJ2[1]);
    printf("    /\\ ");
    damePosicion(posJ1[0], posJ2[1]+1);
    printf("   %c%c%c%c",186,178,178,186);
    damePosicion(posJ1[0], posJ2[1]+2);
    printf("  <%cP1%c>",178,178);
}
void nave2(){
    damePosicion(posJ2[0], posJ2[1]);
    printf("    /\\ ");
    damePosicion(posJ2[0], posJ2[1]+1);
    printf("   %c%c%c%c",186,178,178,186);
    damePosicion(posJ2[0], posJ2[1]+2);
    printf("  <%cP2%c>",178,178);
}


void mover(char tecla){

    // teclas
    //char flechaArriba = 'H';
    char flechaIzquierda = 'K';
    char flechaDerecha = 'M';
    // jugador 1
    if(tecla == flechaDerecha && posJ2[0] < maxXJ2 ){
        damePosicion(posJ2[0],posJ2[1]+2);
        printf(" ");
        posJ2[0] ++;
        nave2();
    }
    if(tecla == flechaIzquierda && posJ2[0] > minXJ2){
        damePosicion(posJ1[0],posJ1[1]+2);
        printf(" ");
        posJ2[0] --;
        nave2();
    }
    // jugador 2
    if(tecla == 'a' && posJ1[0] > minXJ1){
        damePosicion(posJ1[0],posJ1[1]+2);
        printf(" ");
        posJ1[0] --;
        nave1();
    }
    if(tecla == 'd' && posJ1[0] < maxXJ1){
        damePosicion(posJ1[0],posJ1[1]+2);
        printf(" ");
        posJ1[0] ++;
        nave1();
    }

}

void disparar(int jugador){
    if(jugador == 1){
        int trayectoriaX = posJ1[0] + 4;
        int trayectoriaY = posJ1[1] - 1;
        while(trayectoriaY > limiteYSuperior){
            int aux = trayectoriaY;
            damePosicion(trayectoriaX, trayectoriaY--);
            printf("*");
            usleep(20000);
            damePosicion(trayectoriaX, aux);
            printf(" ");
        }
    }
    if(jugador == 2){
        damePosicion(posJ2[0], posJ2[1]);
    }
}

int main()
{
    // tablero
    puntosJ1 = 0;
    puntosJ2 = 0;
    vidasJ1 = 3;
    vidasJ2 = 3;

    // posiciones jugadores
    fondo = 47;
    posJ1[0] = 30;
    posJ1[1] = fondo;
    posJ2[0] = 105;
    posJ2[1] = fondo;

    char teclaDisparoJ1 = 'w';
    char teclaDisparoJ2 = 'H';

    minXJ1 = 2;
    maxXJ1 = 64;
    minXJ2 = 75;
    maxXJ2 = 138;

    limiteYSuperior = 6;
    limiteYInferior = 50;

    nave1();
    nave2();

    //nave1(posJ1[0],posJ1[1]);
    //nave2(posJ2[0],posJ2[1]);
    tableroSuperior();
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
                mover(tecla);

                if(tecla == teclaDisparoJ1){
                    disparar(1);
                }
                if(tecla == teclaDisparoJ2){
                    disparar(2);
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
