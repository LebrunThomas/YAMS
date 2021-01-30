#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "yams.h"

const char* const COMBINAISONS[] = {"As", "Deux", "Trois", "Quatre", "Cinq", "Six", "Brelan", "Carre", "Full", "Petite suite", "Grande suite", "Yams", "Chance"};

/**
 * Fonction utilisée pour le tri avec QSort pour comparer les deux nombres et indiquer le sens de tri
 * https://stackoverflow.com/questions/3893937/sorting-an-array-in-c
 * @param a
 * @param b
 * @return
 */
int compare( const void* a, const void* b)
{
    int int_a = *((int*) a);
    int int_b = *((int*) b);

    // an easy expression for comparing
    return (int_a > int_b) - (int_a < int_b);
}


/**
 * Fonction permettant de lancer la partie
 */
void debut_partie()
{
    //printf("\U+2611");
    // Seed utilisé pour la fonction de random
    srand(time(NULL));

	int des[5];
    int score_joueur1[13] = {0};
    int score_joueur2[13] = {0};
    int combinaisons_joueur1[13] = {0};
    int combinaisons_joueur2[13] = {0};
    int tour = 1;


    while(tour <= 14)
    {
        // Pour joueur 1 et joueur 2
        for (int joueur = 1; joueur <= 2; joueur++) {
            system("cls");
            afficher_entete(joueur, tour);

            lancer_des(des, 5);

            relancer(des, (int) (joueur == 1 ? combinaisons_joueur1 : combinaisons_joueur2), tour);

            afficher_combinaisons((joueur == 1 ? combinaisons_joueur1 : combinaisons_joueur2));

            choix_combinaison(des, (joueur == 1 ? combinaisons_joueur1 : combinaisons_joueur2), (joueur == 1 ? score_joueur1 : score_joueur2));

            afficher_scores((joueur == 1 ? score_joueur1 : score_joueur2), joueur);

            system("pause");
        }

        tour++;
    }

    fin_partie(score_joueur1, score_joueur2);
}

/**
 * Afficher l'entete au début de chaque tour
 * @param joueur Joueur actuel
 * @param tour Tour actuel
 */
void afficher_entete(int joueur, int tour) {
    printf("==== Joueur %d ====\n", joueur);
    printf("==== Tour %d ====\n\n", tour);
}

/**
 * Lance les dés
 * @param des
 * @param nbdes Nombre de dés a lancer
 */
void lancer_des(int des[5], int nbdes)
{
	printf("Lancement des des...\n\n");

	for (int i = 0; i < nbdes; i++) {
        des[i] = rand() % 6 + 1;
    }
}

/**
 * Affiche les des passés en paramètre
 * @param des
 */
void afficher_des(int des[5])
{
    printf("Des:");
    for (int i = 0; i < 5; i++)
    {
        printf("  %d", des[i]);
    }

    printf("\n\n");
}

/**
 * Propose a l'utilisateur de relancer un certain nombre de dés/lesquels
 * @param des
 * @param joueur
 * @param tour
 */
void relancer(int des[5], int joueur, int tour)
{
	int nbdes = -1;
	int des_relance = -1;

	for (int i = 0; i < 2; i++)
	{
	    // Remise a zéro des compteurs
        nbdes = -1;
        des_relance = -1;

        while (nbdes < 0 || nbdes > 5)
		{
            // Affichage des dés lancés
            afficher_des(des);
            printf("Combien de des voulez-vous relancez ? [0-5]");
			scanf("%d", &nbdes);
		}

		if (nbdes != 0)
		{
			for (int j = 0; j < nbdes; j++)
			{
			    printf("%d\n", j);

                des_relance = -1;

                while (des_relance < 1 || des_relance > 5)
                {
                    printf("Quel des voulez vous relancer (position de gauche a droite) ? [1-5]");
                    scanf("%d", &des_relance);
                    des[des_relance-1] = rand() % 6 + 1;
                }
			}
		}
        system("cls");
        afficher_entete(joueur, tour);
	}
}

/**
 * Demande a l'utilisateur de rentrer la combinaisons dans lequel il souhaite rentrer son score
 *
 * @param des
 * @param combinaisons
 * @param scores
 */
void choix_combinaison(int des[5], int combinaisons[13], int scores[13]) {
	int selection = 0;
    int valide = 0;

	afficher_des(des);

    while(valide == 0) {
		printf("Entrez la combinaison que vous souhaitez utiliser : ");
		scanf("%d", &selection);

        valide = calculer_score(selection, des, combinaisons, scores);
	}
}

/**
 * Affiche la fiche d'un joueur
 * @param combinaisons Liste des combinaisons du joueur
 */
void afficher_combinaisons(int combinaisons[13])
{
    printf("=======================\n");
    for (int i = 0; i < 13; i++) {
        printf("%d. %s %s\n", i + 1, COMBINAISONS[i], (combinaisons[i] != 0 ? "(Fait)" : ""));
    }
    printf("=======================\n\n");
}

/**
 * Affiche le score d'un joueur
 * @param scores Liste des scores du joueur
 * @param joueur Joueur
 */
void afficher_scores (int scores[13], int joueur)
{
    int somme = 0;
    for (int i = 0; i < 13; i++) {
        somme += scores[i];
    }
    printf("\nLe joueur %d a %d points.\n\n", joueur, somme);
}

/**
 * Calcul le score d'un utilisateur
 * @param combinaison Combinaison voulu par l'utilisateur
 * @param des Liste des dés lancés
 * @param combinaisons Liste des combinaisons du joueur
 * @param points Liste des points du joueur
 * @return Entier indiquant si la combinaison a pu être réalisée ou non
 */
int calculer_score(int combinaison, int des[5], int combinaisons[13], int points[13]) {
    int valide = 0;
    int valeur_combinaison = 0;

    // Si la combinaison choisie est entre 1 et 6
    if (combinaison <= 6) {
        // Si la combinaison n'a pas déjà été utilisée
        if (combinaisons[combinaison - 1] == 0) {
            // Changement de la valeur de cette combinaison à 1 (jouée)
            combinaisons[combinaison - 1] = 1;

            // Pour chaques dés
            for (int i = 0; i < 5; i++)
                // Si le dés est égal a la valeur de la combinaison choisies
                if (des[i] == combinaison)
                    // Ajout de sa valeur
                    valeur_combinaison = valeur_combinaison + combinaison;

            // Les points de la combinaison lui sont ajoutés dans le tableau a la position qui lui est associé
            points[combinaison - 1] = valeur_combinaison;

            // Confirmation que le coup était possible
            valide = 1;
        }
    }

    // Si la combinaison choisie est un suite (10 et 11)
    if (combinaison == 10 || combinaison == 11) {
        // Si la combinaison n'a pas déjà été utilisée
        if (combinaisons[combinaison - 1] == 0) {
            // Changement de la valeur de cette combinaison à 1 (jouée)
            combinaisons[combinaison - 1] = 1;

            // Trie des dés
            qsort(des, 5, sizeof(int), compare);

            // Récupération du nombre de dés qui se suivent
            for (int i = 0; i < 4; i++)
                if (des[i] == des[i + 1] - 1)
                    valeur_combinaison++;

            // Ajout des points (30 = petite suite, 40 = grande suite)
            if (combinaison == 10 && valeur_combinaison >= 3) {
                points[9] = 30;
                valide = 1;
            } else if (combinaison == 11 && valeur_combinaison >= 4) {
                points[10] = 40;
                valide = 1;
            }
        }
    }

    // Si la combinaison est un brelan, un carre ou un yams (7, 8, 12)
    if (combinaison == 7 || combinaison == 8 || combinaison == 12) {
        // Si la combinaison n'a pas déjà été utilisée
        if (combinaisons[combinaison - 1] == 0)
        {
            // Changement de la valeur de cette combinaison à 1 (jouée)
            combinaisons[combinaison - 1] = 1;

            for (int i = 1; i < 7; i++)
            {
                // Reinitialisation de la variable comptant le nombre de dés identiques
                valeur_combinaison = 0;

                // Nombre de dés identiques
                for (int j = 0; j < 5; j++)
                    if (des[j] == i)
                        valeur_combinaison++;

                // Ajouter les points (7=Brelan=Total, 8=Carre=Total, 12=Yams=50)
                if (combinaison == 7 && valeur_combinaison >= 3) {
                    points[combinaison - 1] = des[0] + des[1] + des[2] + des[3] + des[4];

                    // Confirmation que le coup était possible
                    valide = 1;
                    break;
                } else if (combinaison == 8 && valeur_combinaison >= 4) {
                    points[combinaison - 1] = des[0] + des[1] + des[2] + des[3] + des[4];

                    // Confirmation que le coup était possible
                    valide = 1;
                    break;
                } else if (combinaison == 12 && valeur_combinaison >= 5) {
                    points[combinaison - 1] = 50;

                    // Confirmation que le coup était possible
                    valide = 1;
                    break;
                }
            }
        }
    }

    // Si la combinaison est un Full
    if (combinaison == 9) {
        // Si la combinaison n'a pas déjà été utilisée
        if (combinaisons[combinaison - 1] == 0) {
            int valeur1 = 0;
            int valeur2 = 0;

            // Changement de la valeur de cette combinaison à 1 (jouée)
            combinaisons[combinaison - 1] = 1;

            // Pour chaque valeur de dé
            for (int i = 1; i < 7; i++)
            {
                valeur1 = 0;

                // Pour chaque dés, compter combien on la valeur i
                for (int j = 0; j < 5; j++)
                    if (des[j] == i)
                        valeur1++;


                // Si 3 dés ont été lancés avec la même valeur, quitte la boucle
                if (valeur1 == 3)
                    break;
            }

            // Pour chaque valeur de dé
            for (int i = 1; i < 7; i++)
            {
                valeur2 = 0;

                // Pour chaque dés, compter combien on la valeur i
                for (int j = 0; j < 5; j++)
                    if (des[j] == i)
                        valeur2++;

                // Si 3 dés ont été lancés avec la même valeur à la première boucle
                // et si 2 dés ont été lancés avec la même valeur dans cette boucle
                if (valeur2 == 2 && valeur1 == 3)
                {
                    // On ajoute les points a l'utilisateur
                    points[combinaison - 1] = 25;

                    // Confirmation que le coup était possible
                    valide = 1;

                    // Quitte la boucle
                    break;
                }
            }
        }
    }


    // Si la combinaison est la chance
    if (combinaison == 13) {
        if (combinaisons[combinaison - 1] == 0) {
            combinaisons[combinaison - 1] = 1;

            points[combinaison - 1] = des[0] + des[1] + des[2] + des[3] + des[4];

            valide = 1;
        }
    }

    // Retourner si la combinaison était valide ou non avec le lancé
    return valide;
}

/**
 * Gère la fin de partie
 * @param points_joueur1 Liste des points du joueur 1
 * @param points_joueur2 Liste des points du joueur 2
 */
void fin_partie (int points_joueur1[13], int points_joueur2[13])
{
	int somme_joueur1 = 0, somme_joueur2 = 0, gagnant = 0, bonus_joueur1 = 0;

    system("cls");
	printf("==== Fin de la partie ====\n\n");

	// Calcul des points du joueur 1
	for (int i = 0; i < 13; i++)
        somme_joueur1 += points_joueur1[i];

	// Calcul des points du joueur 2
	for (int i = 0; i < 13; i++)
        somme_joueur2 += points_joueur2[i];

	// Ajout du bonus du joueur 1
	if ((points_joueur1[0] + points_joueur1[1] + points_joueur1[2] + points_joueur1[3] + points_joueur1[4] + points_joueur1[5]) > 63){
        somme_joueur1 += 35;
	}

    // Ajout du bonus du joueur 2
	if ((points_joueur2[0] + points_joueur2[1] + points_joueur2[2] + points_joueur2[3] + points_joueur2[4] + points_joueur2[5]) > 63){
        somme_joueur2 += 35;
	}

	// Déclaration du gagnant
	gagnant = (somme_joueur1 > somme_joueur2 ? 1 : (somme_joueur2 > somme_joueur1 ? 2 : -1));

	if (gagnant == -1) {
	    printf("Egalite ! Les deux joueurs ont %d points.\n\n", somme_joueur1);
	} else {
	    printf("Le joueur %d a gagne avec %d points !\nLe joueur %d a %d points.\n\n",
            gagnant,
            (gagnant == 1 ? somme_joueur1 : somme_joueur2),
            (gagnant == 1 ? 2 : 1),
            (gagnant == 1 ? somme_joueur2 : somme_joueur1)
        );
	}

	system("pause");
}
