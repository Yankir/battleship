//criacao das structs e declaracao das funcoes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define sizeMatrix 10

//struct de cada posicao da matriz
typedef struct
{
	//letra do elemento
	char element;
	//checar se posicao ja foi atingida
	int hit;
	//mostrar a "real" letra do elemento
	int reveal;
}
node;

//struct da matriz e guardar hits, misses e quando acaba o jogo
typedef struct
{
	node matrix[sizeMatrix][sizeMatrix];
	//hits em cada embarcacao
	int hitp,hitn,hitc,hits,hitd;
	//numero de tiros na agua
	int miss;
	//jogo acaba quando end == 5
	int end;
}
field;

//funcoes
void menu1();
void menu2();
void menu3();
void about();
void startField(field *field);
void upperCase(char *lowerCase);
int cantPlace(int line, int column, char direction, int size, field *field);
void inputMatrix(int line, int column, char direction, int size, field *field, char ship);
void printMatrix(field *field);
void clearMatrix(field *field);
void coinFlip(field *fieldPlayer, char *nick);
void destroyed(field *field, char ship);
void result(field *field, char *nick);
void result(field *field, char *nick);
void inputPlayer(field *fieldPlayer);
void placePlayer(char ship, field *fieldPlayer);
void playerShot(field *fieldNpc);
void inputNpc(field *fieldNpc);
void placeNpc(char ship, field *fieldNpc);
void npcShot(field *fieldPlayer,char *nick);
