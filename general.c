//funcoes gerais, nao sao usadas especificamente pelo player ou npc
#include "functions.h"

void menu1()
{
	puts("1) Jogar");
	puts("2) Sobre o jogo");
	puts("3) Sair");
}

void menu2()
{
	system("clear");
	puts("1) PvCOM");
	puts("2) Voltar");
}

void menu3()
{
	puts("1) Jogar denovo");
	puts("2) Voltar ao menu inicial");
}

void about()
{
	system("clear");
	puts("----------------------------------------------------------------------------------------------------------");
	puts("                      Batalha Naval - Trabalho 1 Oficina - Pedro Boccardo - set/2017                      ");
	puts("");
	puts("                                               SOBRE O JOGO                                               ");
	puts("");
	puts("  Antes do jogo ser comercializado, os dois jogadores desenhavam navios em uma folha de papel, represen-");
	puts("tando um mar imaginário quadriculado, para que o outro jogador tentasse acertar as embarcações.");
	puts("  Apesar de muitas contradições com relação à origem do jogo, o jogo foi inventado, mas não patenteado,");
	puts("por Clifford Von Wickler, no começo do século XX (ainda antes da 1a Guerra Mundial). Outra fonte cita");
	puts("que talvez a origem esteja no jogo francês da 1a Guerra Mundial \"L'Attaque\".");
	puts("  O jogo foi lançado em 1931, pela Starex Novelty Co., com o título de SALVO. Durante a 2a Guerra, em");
	puts("1943, o jogo foi lançado novamente, com o nome que ficou mais conhecido nos EUA: Battleship. Foi somente");
	puts("em 1967 que o jogo começou a ser comercializado como jogo de tabuleiro.");
	puts("");
	puts("                                                COMO JOGAR                                                ");
	puts("");
	puts("  No início, cada jogador posiciona suas 5 embarcações numa matriz quadriculada com dimensão 10x10. Os");
	puts("navios só podem ser colocados na direção horizontal ou vertical. As posições livres representam água. Os");
	puts("jogadores jogam alternadamente, tentando acertar as posições onde estão os navios do adversário.");
	puts("");
	puts("Nome e número de células que as embarcações ocupam:");
	puts("  Porta-aviões (P): 5 quadrados");
	puts("  Embarcação de Guerra (N): 4 quadrados");
	puts("  Cruzador (C): 3 quadrados");
	puts("  Submarino (S): 3 quadrados");
	puts("  Destruidor (D): 2 quadrados");
	puts("");
	puts("  Para dar um disparo no campo do inimigo, são dadas coordenadas, com uma letra e um número (e.g. F 5).");
	puts("Para a posição dada, o adversário diz se acertou água ou alguma embarcação. Quando um navio for totalmen-");
	puts("te atingido, o adversário deve revelar qual foi a embarcação destruída.");
	puts("  O jogador que afundar todas as embarcações do adversário primeiro, ganha o jogo.");
	puts("----------------------------------------------------------------------------------------------------------");
}

//iniciar todas as variaveis dos fields com os valores corretos
void startField(field *field)
{
	field->hitp = field->hitn = field->hitc = field->hits = field->hitd = field->miss = field->end = 0;
	
	//Dentro da matriz
	for(int i=0; i<sizeMatrix; i++)
	{
		for(int j=0; j<sizeMatrix; j++)
		{
			field->matrix[i][j].element = 'o';
			field->matrix[i][j].hit = field->matrix[i][j].reveal = 0;
		}
	}
}

//troca minuscula por maiuscula
void upperCase(char *lowerCase)
{
	switch(*lowerCase)
	{
		case('a'):
			*lowerCase = 'A';
			break;

		case('b'):
			*lowerCase = 'B';
			break;

		case('c'):
			*lowerCase = 'C';
			break;

		case('d'):
			*lowerCase = 'D';
			break;

		case('e'):
			*lowerCase = 'E';
			break;

		case('f'):
			*lowerCase = 'F';
			break;

		case('g'):
			*lowerCase = 'G';
			break;

		case('h'):
			*lowerCase = 'H';
			break;

		case('i'):
			*lowerCase = 'I';
			break;

		case('j'):
			*lowerCase = 'J';
			break;

		case('k'):
			*lowerCase = 'K';
			break;

		case('n'):
			*lowerCase = 'N';
			break;

		case('s'):
			*lowerCase = 'S';
			break;

		case('w'):
			*lowerCase = 'W';
			break;

		default:
			break;
	}
}

//checar se eh possivel por a embarcacao na matriz
int cantPlace(int line, int column, char direction, int size, field *field)
{
	switch(direction)
	{
		case('W'):
			for(int i=line; i>=line-size; i--)
			{
				//lugar ocupado na matriz
				if(field->matrix[i][column].element != 'o')
					return 1;
				//lugar fora da matriz
				if(i<0)
					return 1;
			}
			return 0;

		case('A'):
			for(int j=column; j>=column-size; j--)
			{
				if(field->matrix[line][j].element != 'o')
					return 1;
				if(j<0)
					return 1;
			}
			return 0;

		case('S'):
			for(int i=line; i<=line+size; i++)
			{
				if(field->matrix[i][column].element != 'o')
					return 1;
				if(i>9)
					return 1;
			}
			return 0;

		case('D'):
			for(int j=column; j<=column+size; j++)
			{
				if(field->matrix[line][j].element != 'o')
					return 1;
				if(j>9)
					return 1;
			}
			return 0;
	}
}

//colocar embarcacoes na matriz
void inputMatrix(int line, int column, char direction, int size, field *field, char ship)
{
	switch(direction)
	{
		case('W'):
			for(int i=line; i>=line-size; i--)
			{
				field->matrix[i][column].element = ship;
				field->matrix[i][column].reveal = 1;
			}
			break;

		case('A'):
			for(int j=column; j>=column-size; j--)
			{
				field->matrix[line][j].element = ship;
				field->matrix[line][j].reveal = 1;
			}
			break;

		case('S'):
			for(int i=line; i<=line+size; i++)
			{
				field->matrix[i][column].element = ship;
				field->matrix[i][column].reveal = 1;
			}
			break;

		case('D'):
			for(int j=column; j<=column+size; j++)
			{
				field->matrix[line][j].element = ship;
				field->matrix[line][j].reveal = 1;
			}
			break;
	}
}

//mostra campo escolhido
void printMatrix(field *field)
{
	for(int i=-1; i<sizeMatrix; i++)
	{
		puts("---------------------------------------------");
		printf("| ");
		for(int j=-1; j<sizeMatrix; j++)
		{
			//posicao vazia da matriz
			if(i==-1 && j==-1)
				printf(" ");
				
			else
			{
				//primeira linha escreve os numeros 1-9
				if(i==-1)
					printf("%d", j);

				else
				{
					//primeira coluna escreve as letras A-J
					if(j==-1)
						printf("%c", i+65);

					//posicoes do jogo
					else
					{
						//printar letra da embarcacao quando for destruida
						if(field->matrix[i][j].reveal)
							printf("%c", field->matrix[i][j].element);
						else
						{
							//se embarcacao foi acertada, printar x
							if(field->matrix[i][j].hit)
								printf("X");
							else
								printf(" ");
						}
					}
				}
			}
			printf(" | ");
			
			if(j==9)
				puts("");
		}
		if(i==9)
			puts("---------------------------------------------");
	}
}

//tirar reveal == 1 da matriz, para comecar o jogo sem revelar as posicoes
void clearMatrix(field *field)
{
	for(int i=0; i<sizeMatrix; i++)
	{
		for(int j=0; j<sizeMatrix; j++)
		{
			field->matrix[i][j].reveal = 0;
		}
	}
}

//joga moeda, se npc ganha ou player nao quer jogar, npc comeca o jogo
void coinFlip(field *fieldPlayer, char *nick)
{
	//toda vez q jogar troca os numeros aleatorios
	srand(time(NULL));
	system("clear");

	char headsOrTails;
	do
	{
		printf("Cara ou coroa? (K/C): ");
		scanf(" %c", &headsOrTails);
		upperCase(&headsOrTails);
		puts("");
	}
	while((headsOrTails != 'K')&&(headsOrTails != 'C'));

	system("clear");
	int coin  = rand()%2;

	switch(coin)
	{
		case(0):
			//ganhou no cara ou coroa
			if(headsOrTails == 'K')
			{
				char playerStarts;
				do
				{
					printf("Ganhou! Deseja começar? (S/N): ");
					scanf(" %c", &playerStarts);
					upperCase(&playerStarts);
				}
				while((playerStarts != 'S')&&(playerStarts != 'N'));

				system("clear");
				//nao quer comecar
				if(playerStarts == 'N')
					npcShot(*&fieldPlayer,nick);

				//se quiser comecar, o npc nao faz a jogada, entao player atira por primeiro
			}

			//perdeu no cara ou coroa
			else
			{
				puts("Perdeu! COMPUTER começou a partida.");
				npcShot(*&fieldPlayer,nick);
			}

			break;

		case(1):
			if(headsOrTails == 'C')
			{
				char playerStarts;
				do
				{
					printf("Ganhou! Deseja começar? (S/N): ");
					scanf(" %c", &playerStarts);
					upperCase(&playerStarts);
				}
				while((playerStarts != 'S')&&(playerStarts != 'N'));

				system("clear");
				if(playerStarts == 'N')
					npcShot(*&fieldPlayer,nick);
			}

			else
			{
				puts("Perdeu! COMPUTER começou a partida.");
				npcShot(*&fieldPlayer,nick);
			}

			break;
	}
}

//procura a embarcacao destruida na matriz e reveal = 1 para essa embarcacao
void destroyed(field *field, char ship)
{
	for(int i=0; i<sizeMatrix; i++)
	{
		for(int j=0; j<sizeMatrix; j++)
		{
			if(field->matrix[i][j].element == ship)
				field->matrix[i][j].reveal = 1;
		}
	}
}

//printa os resultados de cada jogador na tela
void result(field *field, char *nick)
{
	printf("Campo de %s:\n", nick);
	puts("");

	int shots = field->hitp + field->hitn + field->hitc + field->hits + field->hitd + field->miss;
	printf("Número total de disparos: %d\n", shots);
	printf("Disparos na água: %d\n", field->miss);

	puts("");

	puts("Disparos nas embarcações:");
	if(field->hitd > 0)
		printf("  Disparos no Destruidor: %d\n", field->hitd);
	if(field->hits > 0)
		printf("  Disparos no Submarino: %d\n", field->hits);
	if(field->hitc > 0)
		printf("  Disparos no Cruzador: %d\n", field->hitc); 
	if(field->hitn > 0)
		printf("  Disparos na Embarcação de Guerra: %d\n", field->hitn);
	if(field->hitp > 0)
		printf("  Disparos no Porta-aviões: %d\n", field->hitp);

	puts("");

	puts("Embarcações afundadas:");
	if(field->hitd == 2)
		puts("  Destruidor");
	if(field->hits == 3)
		puts("  Submarino");
	if(field->hitc == 3)
		puts("  Cruzador");
	if(field->hitn == 4)
		puts("  Embarcação de Guerra");
	if(field->hitp == 5)
		puts("  Porta-aviões");
}
