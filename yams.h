void debut_partie();
void lancer_des(int des[5], int nbdes);
void afficher_des(int des[5]);
void relancer(int des[5], int joueur, int tour);
void choix_combinaison(int des[5], int combinaisons[13], int scores[13]);

void afficher_entete(int joueur, int tour);
void afficher_scores(int scores[13], int joueur);
void afficher_combinaisons(int combinaisons[13]);

int calculer_score(int combinaison, int des[5], int combinaisons[13], int points[13]);

void fin_partie(int points_j1[13], int points_j2[13]);
