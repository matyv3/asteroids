#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

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

char teclaDisparoJ1 = 'w';
char teclaDisparoJ2 = 'H';

int posicionAsteroide1X;
int posicionAsteroide1Y;
int posicionAsteroide2X;
int posicionAsteroide2Y;

bool disparoJ1;
bool disparoJ2;

int trayectoriaDisparo1X;
int trayectoriaDisparo1Y;
int trayectoriaDisparo2X;
int trayectoriaDisparo2Y;

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
    printf("  /\\ ");
    damePosicion(posJ1[0], posJ2[1]+1);
    printf(" %c%c%c%c",186,178,178,186);
    damePosicion(posJ1[0], posJ2[1]+2);
    printf("<%cP1%c>",178,178);
}
void nave2(){
    damePosicion(posJ2[0], posJ2[1]);
    printf("  /\\ ");
    damePosicion(posJ2[0], posJ2[1]+1);
    printf(" %c%c%c%c",186,178,178,186);
    damePosicion(posJ2[0], posJ2[1]+2);
    printf("<%cP2%c>",178,178);
}

void moverIzq(int jugador){
    if(jugador == 1){
        if( posJ1[0] > minXJ1 && posJ1[0] < maxXJ1){
            damePosicion(posJ1[0], posJ1[1]+1);
            printf("       ");
            damePosicion(posJ1[0], posJ1[1]+2);
            printf("        ");
            posJ1[0]--;
        }
        nave1();
    }
    if(jugador == 2){
        if( posJ2[0] > minXJ2 && posJ1[0] < maxXJ2){
            damePosicion(posJ2[0], posJ2[1]+1);
            printf("       ");
            damePosicion(posJ2[0], posJ2[1]+2);
            printf("        ");
            posJ2[0]--;
        }
        nave2();
    }
    return;
}

void moverDer(int jugador){
    if(jugador == 1){
        if( posJ1[0] > minXJ1 && posJ1[0] < maxXJ1){
            damePosicion(posJ1[0], posJ1[1]+1);
            printf("       ");
            damePosicion(posJ1[0], posJ1[1]+2);
            printf("        ");
            posJ1[0]++;
        }
        nave1();
    }
    if(jugador == 2){
        if( posJ2[0] > minXJ2 && posJ1[0] < maxXJ2){
            damePosicion(posJ2[0], posJ2[1]+1);
            printf("       ");
            damePosicion(posJ2[0], posJ2[1]+2);
            printf("        ");
            posJ2[0]++;
        }
        nave2();
    }
    return;
}


void resultado(){
    usleep(20000);
    damePosicion(70, 30);
    printf("         ");
    damePosicion(70, 31);
    if(puntosJ1 > puntosJ2){
        printf("Ganador Jugador 1 !");
    }else if(puntosJ2 == puntosJ1){
        printf("Empate!");
    }else{
        printf("Ganador Jugador 2 !");
    }
    damePosicion(70, 32);
    printf("         ");
}

void disparar1(){
    trayectoriaDisparo1X = posJ1[0];
    trayectoriaDisparo1Y = posJ1[1];
    disparoJ1 = true;
    return;
}

void disparar2(){
    trayectoriaDisparo2X = posJ2[0];
    trayectoriaDisparo2Y = posJ2[1];
    disparoJ2 = true;
    return;
}

bool gameStart;

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

    minXJ1 = 2;
    maxXJ1 = 68;
    minXJ2 = 75;
    maxXJ2 = 142;

    limiteYSuperior = 6;
    limiteYInferior = 50;

    nave1();
    nave2();

    disparoJ1 = false;

    tableroSuperior();
    dibujarTablero();

    gameStart = false;

	bool gameOver = false;
	while(!gameOver){


        /*if(gameStart){
            usleep(10000);
            gameStart = false;
        }*/
        usleep(20000);

        // asteroides
        srand(time(NULL));
        posicionAsteroide1X = minXJ1 + rand() % (maxXJ1 + 1 - minXJ1);
        if(posicionAsteroide1Y < limiteYInferior){
            usleep(10000);
            damePosicion(posicionAsteroide1X, posicionAsteroide1Y);
            printf(" ");
            damePosicion(posicionAsteroide1X, posicionAsteroide1Y+1);
            printf("*");
            posicionAsteroide1Y++;
        }else{
            posicionAsteroide1Y = limiteYSuperior;
        }


        // disparo 1
        if(disparoJ1){
            damePosicion(trayectoriaDisparo1X, trayectoriaDisparo1Y+1);
            printf(" ");
            damePosicion(trayectoriaDisparo1X, trayectoriaDisparo1Y);
            printf("*");
        }

        if( trayectoriaDisparo1Y > limiteYSuperior ){
            trayectoriaDisparo1Y--;
        }else{
            damePosicion(trayectoriaDisparo1X, trayectoriaDisparo1Y);
            printf(" ");
            trayectoriaDisparo1Y = posJ1[1];
            disparoJ1 = false;
        }

        // disparo 2
        if(disparoJ2){
            damePosicion(trayectoriaDisparo2X, trayectoriaDisparo2Y+1);
            printf(" ");
            damePosicion(trayectoriaDisparo2X, trayectoriaDisparo2Y);
            printf("*");
        }

        if( trayectoriaDisparo2Y > limiteYSuperior ){
            trayectoriaDisparo2Y--;
        }else{
            damePosicion(trayectoriaDisparo2X, trayectoriaDisparo2Y);
            printf(" ");
            trayectoriaDisparo2Y = posJ2[1];
            disparoJ2 = false;
        }

        if(kbhit()){
            char tecla = getch();
            if(tecla == 'g'){
                gameStart = true;
            }

            if( tecla == 'a' && vidasJ1 > 0 ){
                moverIzq(1);
            }
            if( tecla == 'd' && vidasJ1 > 0 ){
                moverDer(1);
            }
            if( tecla == 'K' && vidasJ2 > 0){
                moverIzq(2);
            }
            if( tecla == 'M' && vidasJ2 > 0){
                moverDer(2);
            }

            if(tecla == teclaDisparoJ1 && vidasJ1 > 0 && !disparoJ1){
                disparar1();
            }
            if(tecla == teclaDisparoJ2 && vidasJ2 > 0 && !disparoJ2){
                disparar2();
            }
        }

        if(vidasJ1 == 0 && vidasJ2 == 0){
            gameOver = true;
            resultado();
        }
	}

    char teclaCerrar;
    while(teclaCerrar != 'c'){
        teclaCerrar = getch();
    }

    return 0;
}
