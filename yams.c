#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "yams.h"

// Lancement de la partie
void start_game()
{
    // Seed utilisé pour la fonction de random
    srand(time(NULL));

	int des[5];
    int score_joueur1[13];
    int score_joueur2[13];

    for(int turn = 0; turn < 14; turn++)
    {
        for (int i = 1; i < 2; i++) {
            // PLAYER 1
            // Clear du terminal
            system("cls");

            printf("==== Joueur %d ====\n", i);
            roll_dice(des);
            print_dices(des);
            reroll(des, 5, i, turn);

            // Clear du terminal
            system("cls");
            printf("==== Joueur %d ====\n", i);
            print_score((i == 1 ? score_joueur1 : score_joueur2), i);
        }
    }

	printf("La partie est terminée");
    // [TO-DO] Appel de la fonction de fin de partie
}


// Lancement des dès
void roll_dice(int des[5])
{
	printf("Lancement des des...\n\n");

    // Lancement de 
	for (int i = 0; i < 5; i++) {
        des[i] = rand() % 6 + 1;
    }
}


// Affichage des valeurs des dés
void print_dices(int des[5])
{
    printf("Des:");
    for (int i = 0; i < 5; i++)
    {
        printf("  %d", des[i]);
    }

    printf("\n");
}


// Affichage des scores 
void print_score(int scores[13], int joueur)
{
    int total = 0;

    // Affichage des 13 lignes de scores
    for (int i = 0; i < 13; i++) {
        total += scores[i];
    }

    printf("Le joueur %d à %d points.\n", joueur, total);
}


// Relancer les dés
void reroll(int des[5], int size, int joueur, int tour)
{
	int nbdes = -1;
	int dices_reroll = 0;

	for (int i = 0; i < 2; i++)
	{
        // Remise a -1 de la variable pour ne pas passer directement dans le while en dessous
        nbdes = -1;

        // Demander a l'utilisateur de rentrer un numbéro entre 0 et 5 (nombre de dés a relancer)
        while (nbdes < 0 || nbdes > 5)
		{
			printf("Combien de des voulez-vous relancez ? [0-5] ");
			scanf("%d", &nbdes);
		}

        // Sortir de la boucle si aucune dés n'est relancés
        if (nbdes == 0) break;

        // Pour chaque dés a relancer
        for (int j = 0; j < nbdes; j++)
        {
            // Demander à l'utilisateur de rentrer un numéro entre 1 et 5 (numéro du dé à relancer)
            while (dices_reroll < 1 || dices_reroll > 5)
            {
                printf("Quel des voulez vous relancer (position de gauche a droite) ? [1-5]");

                scanf("%d", &dices_reroll);
                printf("%d", dices_reroll);

                // Nouveau lancé de dés pour ce dés
                des[dices_reroll-1] = rand() % 6 + 1;
            }
        }

        // Clear du terminal
        system("cls");

        // Affichage des nouvelles valeurs
        printf("==== Joueur %d ====\n", joueur);
        printf("==== Tour %d ====\n\n", tour);
        print_dices(des, 5);
	}
}
