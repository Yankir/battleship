//funcoes que usam struct do npc
#include "functions.h"

//mudar letra dependendo da embarcacao
void inputNpc(field *fieldNpc)
{
	char ship = 'P';
	placeNpc(ship,*&fieldNpc);

	ship = 'N';
	placeNpc(ship,*&fieldNpc);

	ship = 'C';
	placeNpc(ship,*&fieldNpc);

	ship = 'S';
	placeNpc(ship,*&fieldNpc);

	ship = 'D';
	placeNpc(ship,*&fieldNpc);
}

//chute de posicoes aleatorias para a matrizNpc
void placeNpc(char ship, field *fieldNpc)
{
	//toda vez que jogar, troca os numeros aleatorios
	srand(time(NULL));

	int size;
	switch(ship)
	{
		case('P'):
			size = 4;
			break;
		case('N'):
			size = 3;
			break;
		case('C'):
			size = 2;
			break;
		case('S'):
			size = 2;
			break;
		case('D'):
			size = 1;
			break;
	}

	int  line, column;
	char direction;

	//linha, coluna e direcao aleatorias
	do
	{
		line = rand() % sizeMatrix;
		column = rand() % sizeMatrix;
		direction = rand() % 4;
		
		switch(direction)
		{
			case(0):
				direction = 'W';
				break;
			case(1):
				direction = 'A';
				break;
			case(2):
				direction = 'S';
				break;
			case(3):
				direction = 'D';
				break;
		}
	}
	while(cantPlace(line,column,direction,size,*&fieldNpc));

	//possivel por na matriz
	inputMatrix(line,column,direction,size,*&fieldNpc,ship);
}

//tiro aletorio do npc no campo do player
void npcShot(field *fieldPlayer,char *nick)
{
	//toda vez q jogar troca os numeros aleatorios
	srand(time(NULL));

	int line, column;

	do
	{
		line = rand() % sizeMatrix;
		column = rand() % sizeMatrix;
	}
	while(fieldPlayer->matrix[line][column].hit);

	//posicao ainda nao foi acertada, mudar campo do player
	fieldPlayer->matrix[line][column].hit = 1;
	
	//agua
	if(fieldPlayer->matrix[line][column].element == 'o')
	{
		fieldPlayer->miss++;
		fieldPlayer->matrix[line][column].reveal = 1;
		printf("Campo de %s:\n", nick);
		printMatrix(*&fieldPlayer);
		puts("Água!");
		sleep(4);
		system("clear");
	}

	//navio
	else
	{
		//checar qual embarcacao pegou
		switch(fieldPlayer->matrix[line][column].element)
		{
			case('P'):
				//incrementar acerto no porta-avioes
				fieldPlayer->hitp++;

				//se acertar todo o porta-avioes
				if(fieldPlayer->hitp == 5)
				{
					//revela todas as posicoes que destruiu
					destroyed(*&fieldPlayer,'P');
					//como afundou embarcacao, incrementa end
					fieldPlayer->end++;

					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Afundou o Porta-aviões!");
					sleep(6);
					system("clear");
				}

				else
				{
					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;

			case('N'):
				fieldPlayer->hitn++;

				if(fieldPlayer->hitn == 4)
				{
					destroyed(*&fieldPlayer,'N');
					fieldPlayer->end++;

					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Afundou a Embarcação de Guerra!");
					sleep(6);
					system("clear");
				}

				else
				{
					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;

			case('C'):
				fieldPlayer->hitc++;

				if(fieldPlayer->hitc == 3)
				{
					destroyed(*&fieldPlayer,'C');
					fieldPlayer->end++;

					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Afundou o Cruzador!");
					sleep(6);
					system("clear");
				}

				else
				{
					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;

			case('S'):
				fieldPlayer->hits++;

				if(fieldPlayer->hits == 3)
				{
					destroyed(*&fieldPlayer,'S');
					fieldPlayer->end++;

					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Afundou o Submarino!");
					sleep(6);
					system("clear");
				}

				else
				{
					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;

			case('D'):
				fieldPlayer->hitd++;

				if(fieldPlayer->hitd == 2)
				{
					destroyed(*&fieldPlayer,'P');
					fieldPlayer->end++;

					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Afundou o Destruidor!");
					sleep(6);
					system("clear");
				}

				else
				{
					printf("Campo de %s:\n", nick);
					printMatrix(*&fieldPlayer);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;
		}
	}
}
