//funcoes que usam struct do player
#include "functions.h"

//mudar letra da embarcacao, dependendo de qual esta sendo posicionada
void inputPlayer(field *fieldPlayer)
{
	//P == porta avioes
	placePlayer('P',*&fieldPlayer);

	//N == Embarcação de Guerra
	placePlayer('N',*&fieldPlayer);

	//C == Cruzador
	placePlayer('C',*&fieldPlayer);

	//S == Submarino
	placePlayer('S',*&fieldPlayer);

	//D == Destruidor
	placePlayer('D',*&fieldPlayer);

	//mostrar ultima embarcacao
	system("clear");
	puts("Seu campo:");
	printMatrix(*&fieldPlayer);
	sleep(4);
}

//posicionar embarcacoes
void placePlayer(char ship, field *fieldPlayer)
{
	int size;
	char shipName[25];

	//troca shipName e size, dependendo da embarcacao sendo posicionada no momento
	//(size-1) da embarcacao para por nas funcoes
	switch(ship)
	{
		case('P'):
			size = 4;
			strcpy(shipName,"Porta-aviões");
			break;

		case('N'):
			size = 3;
			strcpy(shipName,"Embarcação de Guerra");
			break;

		case('C'):
			size = 2;
			strcpy(shipName,"Cruzador");
			break;

		case('S'):
			size = 2;
			strcpy(shipName,"Submarino");
			break;

		case('D'):
			size = 1;
			strcpy(shipName,"Destruidor");
			break;
	}

	int column, invalidPosition = 0;
	char line, direction;
	do
	{
		char check;
		do
		{
			system("clear");
			printMatrix(*&fieldPlayer);

			if(invalidPosition)
				puts("Posição inválida! Escolha outra posição.");

			printf("Você está posicionando \"%s\" (Tamanho = %d):\n", shipName,size+1);

			//linha
			do
			{
				printf("Informe a linha (A-J): ");
				scanf(" %c", &line);
				puts("");
				upperCase(&line);
			}
			while((line != 'A')&&(line != 'B')&&(line != 'C')&&(line != 'D')&&(line != 'E')&&(line != 'F')&&(line != 'G')&&(line != 'H')&&(line != 'I')&&(line != 'J'));

			//coluna
			do
			{
				printf("Informe a coluna (0-9): ");
				scanf(" %d", &column);
				puts("");
			}
			while((column != 0)&&(column != 1)&&(column != 2)&&(column != 3)&&(column != 4)&&(column != 5)&&(column != 6)&&(column != 7)&&(column != 8)&&(column != 9));

			//direcao
			do
			{
				printf("Informe a direção (W,A,S,D): ");
				scanf(" %c", &direction);
				puts("");
				upperCase(&direction);
			}
			while((direction != 'W')&&(direction != 'A')&&(direction != 'S')&&(direction != 'D'));

			//texto dependendo da direcao escolhida
			switch(direction)
			{
				case('W'):
					printf("Confirmar coordenada (%c-%d para cima) para \"%s\"? (S/N): ", line,column,shipName);
					scanf(" %c", &check);
					break;

				case('A'):
					printf("Confirmar coordenada (%c-%d para esquerda) para \"%s\"? (S/N): ", line,column,shipName);
					scanf(" %c", &check);
					break;

				case('S'):
					printf("Confirmar coordenada (%c-%d para baixo) para \"%s\"? (S/N): ", line,column,shipName);
					scanf(" %c", &check);
					break;

				case('D'):
					printf("Confirmar coordenada (%c-%d para direita) para \"%s\"? (S/N): ", line,column,shipName);
					scanf(" %c", &check);
					break;
			}
			upperCase(&check);
			puts("");
			//se nao quiser confirmar posicao, entao nao eh posicao invalida
			invalidPosition = 0;
		}
		while(check != 'S');
		
		//se o laco recomecar, entao a posicao eh invalida
		invalidPosition = 1;
		//tirar linha do "modo" ascii para transformar em posicao da matriz
		line -= 65;
	}
	while(cantPlace(line,column,direction,size,*&fieldPlayer));

	//possivel por na matriz
	inputMatrix(line,column,direction,size,*&fieldPlayer,ship);
}

//tiro do player no campo do npc
void playerShot(field *fieldNpc)
{
	puts("Campo de COMPUTER:");
	printMatrix(*&fieldNpc);

	int column, invalidPosition = 0;
	char line;

	do
	{
		//se a posicao ja foi atingida antes, avisa erro
		if(invalidPosition)
		{
			system("clear");
			puts("Campo de COMPUTER:");
			printMatrix(*&fieldNpc);
			puts("Posição inválida! Escolha outra posição.");
		}

		//linha
		do
		{
			printf("Informe a linha (A-J): ");
			scanf(" %c", &line);
			puts("");
			upperCase(&line);
		}
		while((line != 'A')&&(line != 'B')&&(line != 'C')&&(line != 'D')&&(line != 'E')&&(line != 'F')&&(line != 'G')&&(line != 'H')&&(line != 'I')&&(line != 'J'));

		//coluna
		do
		{
			printf("Informe a coluna (0-9): ");
			scanf(" %d", &column);
			printf("%d\n", column);
			puts("");
		}
		while((column != 0)&&(column != 1)&&(column != 2)&&(column != 3)&&(column != 4)&&(column != 5)&&(column != 6)&&(column != 7)&&(column != 8)&&(column != 9));

		//mudar linha para valor de 0 a 9
		line -= 65;
		//se voltar o loop, entao a posicao eh invalida
		invalidPosition = 1;
	}
	while(fieldNpc->matrix[line][column].hit);

	system("clear");
	fieldNpc->matrix[line][column].hit = 1;

	//agua
	if(fieldNpc->matrix[line][column].element == 'o')
	{
		fieldNpc->miss++;
		fieldNpc->matrix[line][column].reveal = 1;

		puts("Campo de COMPUTER:");
		printMatrix(*&fieldNpc);
		puts("Água!");
		sleep(4);
		system("clear");
	}

	//navio
	else
	{
		//checar qual embarcacao pegou
		switch(fieldNpc->matrix[line][column].element)
		{
			case('P'):
				//incrementar acerto no porta-avioes
				fieldNpc->hitp++;

				//se acertar todo o porta-avioes
				if(fieldNpc->hitp == 5)
				{
					//revela todas as posicoes que destruiu
					destroyed(*&fieldNpc,'P');
					//como afundou embarcacao, incrementa end
					fieldNpc->end++;

					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Afundou o Porta-aviões!");
					sleep(6);
					system("clear");
				}

				else
				{
					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}

				break;

			case('N'):
				fieldNpc->hitn++;

				if(fieldNpc->hitn == 4)
				{
					destroyed(*&fieldNpc,'N');
					fieldNpc->end++;

					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Afundou a Embarcação de Guerra!");
					sleep(6);
					system("clear");
				}

				else
				{
					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}
				
				break;
				
			case('C'):
				fieldNpc->hitc++;

				if(fieldNpc->hitc == 3)
				{
					destroyed(*&fieldNpc,'C');
					fieldNpc->end++;

					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Afundou o Cruzador!");
					sleep(6);
					system("clear");
				}

				else
				{
					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}
				
				break;
			
			case('S'):
				fieldNpc->hits++;

				if(fieldNpc->hits == 3)
				{
					destroyed(*&fieldNpc,'S');
					fieldNpc->end++;

					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Afundou o Submarino!");
					sleep(6);
					system("clear");
				}

				else
				{
					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}
				
				break;
				
			case('D'):
				fieldNpc->hitd++;

				if(fieldNpc->hitd == 2)
				{
					destroyed(*&fieldNpc,'D');
					fieldNpc->end++;

					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Afundou o Destruidor!");
					sleep(6);
					system("clear");
				}

				else
				{
					puts("Campo de COMPUTER:");
					printMatrix(*&fieldNpc);
					puts("Fogo!");
					sleep(5);
					system("clear");
				}
				
				break;
		}
	}
}
