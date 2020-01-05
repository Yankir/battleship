//Batalha Naval - Trabalho 1 Oficina - Pedro Boccardo - set/2017
#include "functions.h"

int main()
{

	int menuOption;
	//mostrar menu ate sair do jogo
	do
	{
		//printando menu e lendo a opcao desejada
		menu1();
		scanf("%d", &menuOption);

		switch(menuOption)
		{
			//Jogar
			case(1):

				menuOption = 0;
				//ficar no loop ate voltar para o menu anterior
				for(;;)
				{
					//jogador nao quis jogar denovo
					if(menuOption != 1)
					{
						menu2();
						scanf("%d", &menuOption);
					}
					
					//PvCOM
					if(menuOption == 1)
					{
						system("clear");

						char nick[25];
						puts("Digite seu nick:");
						scanf("%s", nick);

						//criar os 2 campos e inicializa-los
						field fieldNpc, fieldPlayer;
						startField(&fieldPlayer);
						inputPlayer(&fieldPlayer);
						startField(&fieldNpc);
						inputNpc(&fieldNpc);

						//comecar o jogo sem revelar os campos
						clearMatrix(&fieldPlayer);
						clearMatrix(&fieldNpc);

						//lancar moeda para ver quem vai comecar o jogo
						coinFlip(&fieldPlayer,nick);

						int win = 0;
						do
						{
							playerShot(&fieldNpc);

							//se player ganhou, npc nao faz a jogada e sai do loop
							if(fieldNpc.end == 5)
							{
								win = 1;
								break;
							}

							npcShot(&fieldPlayer,nick);
						}
						while(fieldPlayer.end < 5);

						//resultados do jogo
						puts("---------------------------------------");
						result(&fieldPlayer,nick);
						puts("---------------------------------------");
						result(&fieldNpc,"COMPUTER");
						puts("---------------------------------------");

						sleep(30);

						do
						{
							system("clear");

							if(win)
								puts("Você ganhou!");
							else
								puts("Você perdeu!");

							puts("");
							menu3();
							scanf("%d", &menuOption);
						}
						while((menuOption != 1)&&(menuOption != 2));
					}
					
					//Voltar
					if(menuOption == 2)
					{
						system("clear");
						break;
					}
				}

				break;

			//Sobre
			case(2):
				about();
				break;

			//Sair
			case(3):
				break;

			default:
				system("clear");
				break;
		}
	}
	while(menuOption != 3);
}
