#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// threads https://askubuntu.com/questions/568068/multithreading-in-codeblocks

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

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_t thread_game, thread_asteroide1, thread_asteroide2, thread_disparo1, thread_disparo2, thread_mover1, thread_mover2;

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

void mover1(char tecla){
    if(tecla == 'a' && posJ1[0] > minXJ1){
        damePosicion(posJ1[0],posJ1[1]+1);
        printf("       ");
        damePosicion(posJ1[0],posJ1[1]+2);
        printf("        ");
        posJ1[0] --;
        nave1();
    }
    if(tecla == 'd' && posJ1[0] < maxXJ1){
        damePosicion(posJ1[0],posJ1[1]+2);
        printf(" ");
        posJ1[0] ++;
        nave1();
    }
   // pthread_exit(NULL);
    return;
}
void mover2(char tecla){
    // teclas
    char flechaIzquierda = 'K';
    char flechaDerecha = 'M';

    if(tecla == flechaDerecha && posJ2[0] < maxXJ2 ){
        damePosicion(posJ2[0],posJ2[1]+2);
        printf(" ");
        posJ2[0] ++;
        nave2();
    }
    if(tecla == flechaIzquierda && posJ2[0] > minXJ2){
        damePosicion(posJ2[0],posJ2[1]+1);
        printf("       ");
        damePosicion(posJ2[0],posJ2[1]+2);
        printf("        ");
        posJ2[0] --;
        nave2();
    }
    //pthread_exit(NULL);
    return;
}
/**

    DISPAROS

*/
int trayectoriaDisparo1X;
int trayectoriaDisparo1Y;
int trayectoriaDisparo2X;
int trayectoriaDisparo2Y;

void disparar1(){
    trayectoriaDisparo1X = posJ1[0] + 2;
    trayectoriaDisparo1Y = posJ1[1] - 1;
    while(trayectoriaDisparo1Y > limiteYSuperior){
        int aux = trayectoriaDisparo1Y;
        damePosicion(trayectoriaDisparo1X, trayectoriaDisparo1Y--);
        printf("*");
        usleep(20000);
        damePosicion(trayectoriaDisparo1X, aux);
        printf(" ");
        if(posicionAsteroide1X == trayectoriaDisparo1X && posicionAsteroide1Y == trayectoriaDisparo1Y){
            damePosicion(trayectoriaDisparo1X, trayectoriaDisparo1Y);
            printf(" ");
            return;
        }
    }
    trayectoriaDisparo1X = 0;
    trayectoriaDisparo1Y = 0;
}


void disparar2(){
    trayectoriaDisparo2X = posJ2[0] + 2;
    trayectoriaDisparo2Y = posJ2[1] - 1;
    while(trayectoriaDisparo2Y > limiteYSuperior){
        int aux = trayectoriaDisparo2Y;
        damePosicion(trayectoriaDisparo2X, trayectoriaDisparo2Y--);
        printf("*");
        usleep(20000);
        damePosicion(trayectoriaDisparo2X, aux);
        printf(" ");
        if(posicionAsteroide2X == trayectoriaDisparo2X && posicionAsteroide2Y == trayectoriaDisparo2Y){
            damePosicion(trayectoriaDisparo2X, trayectoriaDisparo2Y);
            printf(" ");
            return;
        }
    }
    trayectoriaDisparo2X = 0;
    trayectoriaDisparo2Y = 0;
}

/**

    ASTEROIDES

*/
void asteroide1(){
    if(vidasJ1 == 0){
        damePosicion(30,30);
        printf("te muriste!!!");
        pthread_exit(NULL);
        return;
    }
    srand(time(NULL));
    posicionAsteroide1X = minXJ1 + rand() % (maxXJ1 + 1 - minXJ1);
    posicionAsteroide1Y = limiteYSuperior + 1;
    while(posicionAsteroide1Y < limiteYInferior){
        int aux = posicionAsteroide1Y;
        pthread_mutex_lock( &mutex2 );
        damePosicion(posicionAsteroide1X, posicionAsteroide1Y++);
        pthread_mutex_unlock( &mutex2 );
        printf("%c",184);
        usleep(100000);
        pthread_mutex_lock( &mutex2 );
        damePosicion(posicionAsteroide1X, aux);
        pthread_mutex_unlock( &mutex2 );
        printf(" ");

        if(posicionAsteroide1X == trayectoriaDisparo1X && posicionAsteroide1Y == trayectoriaDisparo1Y){
            puntosJ1++;
            tableroSuperior();
            break;
        }

        if( (posicionAsteroide1X== posJ1[0]
              || posicionAsteroide1X == posJ1[0]+1
              || posicionAsteroide1X == posJ1[0]+2
              || posicionAsteroide1X == posJ1[0]+3
              || posicionAsteroide1X == posJ1[0]+4
              || posicionAsteroide1X == posJ1[0]+5) && posicionAsteroide1Y == posJ1[1] ){
            pthread_mutex_lock( &mutex1 );
            vidasJ1--;
            tableroSuperior();
            pthread_mutex_unlock( &mutex1 );
            break;
        }
    }
    asteroide1();
    return;
}

void asteroide2(){
    if(vidasJ2 == 0){
        damePosicion(105,30);
        printf("te muriste!!!");
        pthread_exit(NULL);
        return;
    }
    srand(time(NULL));
    posicionAsteroide2X = minXJ2 + rand() % (maxXJ2 + 1 - minXJ2);
    posicionAsteroide2Y = limiteYSuperior + 1;
    while(posicionAsteroide2Y < limiteYInferior){
        int aux = posicionAsteroide2Y;
        pthread_mutex_lock( &mutex2 );
        damePosicion(posicionAsteroide2X, posicionAsteroide2Y++);
        pthread_mutex_unlock( &mutex2 );
        printf("%c",184);
        usleep(100000);
        pthread_mutex_lock( &mutex2 );
        damePosicion(posicionAsteroide2X, aux);
        pthread_mutex_unlock( &mutex2 );
        printf(" ");

        if(posicionAsteroide2X == trayectoriaDisparo2X && posicionAsteroide2Y == trayectoriaDisparo2Y){
            puntosJ2++;
            tableroSuperior();
            break;
        }

        if( (posicionAsteroide2X == posJ2[0]
             || posicionAsteroide2X == posJ2[0]+1
             || posicionAsteroide2X == posJ2[0]+2
             || posicionAsteroide2X == posJ2[0]+3
             || posicionAsteroide2X == posJ2[0]+4
             || posicionAsteroide2X == posJ2[0]+5 ) && posicionAsteroide2Y == posJ2[1] ){
            pthread_mutex_lock( &mutex1 );
            vidasJ2--;
            tableroSuperior();
            pthread_mutex_unlock( &mutex1 );
            break;
        }
    }
    asteroide2();
    return;
}

void resultado(){
    usleep(20000);
    damePosicion(70, 30);
    printf("         ");
    //printf("%c%c%c%c%c%c%c%c%c%c",201,205,205,205,205,205,205,205,205,205,187);
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

    tableroSuperior();
    dibujarTablero();

    gameStart = false;

	bool gameOver = false;
	while(!gameOver){


        if(gameStart){
            pthread_create( &thread_asteroide1, NULL, asteroide1, NULL);
            usleep(10000);
            pthread_create( &thread_asteroide2, NULL, asteroide2, NULL);
            gameStart = false;
        }

        if(kbhit()){
            char tecla = getch();
            if(tecla == 'g'){
                gameStart = true;
            }

            if( (tecla == 'a' || tecla == 'd') && vidasJ1 > 0){
                mover1(tecla);
                //void * ptr1 = NULL;
                //if( pthread_join(thread_mover1, &ptr1) != 0){
                   // pthread_create( &thread_mover1, NULL, mover1, (void*) tecla);
                //}
            }
            if( (tecla == 'K' || tecla == 'M') && vidasJ2 > 0){
                mover2(tecla);
                //void * ptr2 = NULL;
                //if( pthread_join(thread_mover2, &ptr2) != 0){
                    //pthread_create( &thread_mover2, NULL, mover2, (void*) tecla);
                //}
            }

            if(tecla == teclaDisparoJ1 && vidasJ1 > 0){
                disparar1();
                //pthread_create( &thread_disparo1, NULL, disparar, 1);
                /*
                void * ptr1 = NULL;
                if( pthread_join(thread_disparo1, &ptr1) != 0){
                    pthread_create( &thread_disparo1, NULL, disparar, 1);
                }
                */
            }
            if(tecla == teclaDisparoJ2 && vidasJ2 > 0){
                disparar2();
                //pthread_create( &thread_disparo2, NULL, disparar, 2);
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
