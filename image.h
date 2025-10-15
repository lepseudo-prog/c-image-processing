#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// structure d'entete du fichier
struct entete_fichier
       {
       char idformat[2];
       int taille_fichier;
       int reserve;
       int debut;
       };

// structure d'entete de l'image
struct entete_bmp
       {
       int taille_image;
       int largeur;
       int alignement;
       int hauteur;
       short plans;
       short profondeur;
       int compression;
       int taille_image_totale;
       int resolutionh;
       int resolutionv;
       int nbrcouleur;
       int nbrcouleuri;
       };

// structure d'un pixel
struct pixels
       {
       unsigned char b;
       unsigned char g;
       unsigned char r;
       };

// structure du fichier
struct fichierimage
       {
       struct entete_fichier entetefichier;
       struct entete_bmp entetebmp;
       struct pixels image[5000][5000];
       };

struct fichierimage *charger(char *nom)
{
       FILE *f;
       int i,j,k;
       unsigned char zero;
       unsigned char *buffer;
       int position=0;
       int longueur=0;
       struct fichierimage *fichier=(struct fichierimage *)malloc(sizeof(struct fichierimage));

       f=fopen(nom,"rb");
       fseek(f,0,SEEK_END);
       longueur=ftell(f);
       fseek(f,0,SEEK_SET);
       buffer=(unsigned char *)malloc(longueur*sizeof(unsigned char));
       fread((unsigned char *)buffer,1,longueur,f);
       fclose(f);

       // lecture de l'entete du fichier

       memcpy(&fichier->entetefichier.idformat,(buffer+position),2);
       position+=2;
       memcpy(&fichier->entetefichier.taille_fichier,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetefichier.reserve,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetefichier.debut,(buffer+position),4);
       position+=4;

       /*
       printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
       printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
       printf("reserve                  :%d\n",fichier->entetefichier.reserve);
       printf("debut                    :%d\n",fichier->entetefichier.debut);
       */

       // lecture de l'entete de l'image

       memcpy(&fichier->entetebmp.taille_image,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.largeur,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.hauteur,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.plans,(buffer+position),2);
       position+=2;
       memcpy(&fichier->entetebmp.profondeur,(buffer+position),2);
       position+=2;
       memcpy(&fichier->entetebmp.compression,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.taille_image_totale,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.resolutionh,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.resolutionv,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.nbrcouleur,(buffer+position),4);
       position+=4;
       memcpy(&fichier->entetebmp.nbrcouleuri,(buffer+position),4);
       position+=4;

       /*
       printf("taille image             :%d\n",fichier->entetebmp.taille_image);
       printf("largeur                  :%d\n",fichier->entetebmp.largeur);
       printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
       printf("plans                    :%d\n",fichier->entetebmp.plans);
       printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
       printf("compression              :%d\n",fichier->entetebmp.compression);
       printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
       printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
       printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
       printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
       printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
       */

       if(fichier->entetebmp.plans!=1||fichier->entetebmp.profondeur!=24||fichier->entetebmp.compression!=0||fichier->entetebmp.nbrcouleur!=0||fichier->entetebmp.nbrcouleuri!=0)
       {
       printf("Impossible de charger l'image\n");
       free(fichier);
       free(buffer);
       return 0;
       }

       // mise de l'image en memoire

       for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
       {
       for(j=0;j<fichier->entetebmp.largeur;j++)
                                   {
                                   memcpy(&fichier->image[i][j].b,(buffer+position),1);
                                   position+=1;
                                   memcpy(&fichier->image[i][j].g,(buffer+position),1);
                                   position+=1;
                                   memcpy(&fichier->image[i][j].r,(buffer+position),1);
                                   position+=1;
                                   }
       for(k=0;k<fichier->entetebmp.largeur%4;k++)
                                                 {
                                                 memcpy(&zero,(buffer+position),1);
                                                 position+=1;
                                                 }
       }

       free(buffer);
       return fichier;
}

int enregistrer(char *nom,struct fichierimage *fichier)
{
       FILE *f;
       int i,j,k;
       unsigned char zero=(unsigned char)0;
       unsigned char *buffer;
       int position=0;
       int longueur=14+fichier->entetefichier.taille_fichier;
       buffer=(unsigned char *)malloc(longueur*sizeof(unsigned char));

       // ecriture de l'entete du fichier

       /*
       printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
       printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
       printf("reserve                  :%d\n",fichier->entetefichier.reserve);
       printf("debut                    :%d\n",fichier->entetefichier.debut);
       */

       memcpy((buffer+position),&fichier->entetefichier.idformat,2);
       position+=2;
       memcpy((buffer+position),&fichier->entetefichier.taille_fichier,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetefichier.reserve,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetefichier.debut,4);
       position+=4;

       // ecriture de l'entete de l'image

       /*
       printf("taille image             :%d\n",fichier->entetebmp.taille_image);
       printf("largeur                  :%d\n",fichier->entetebmp.largeur);
       printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
       printf("plans                    :%d\n",fichier->entetebmp.plans);
       printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
       printf("compression              :%d\n",fichier->entetebmp.compression);
       printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
       printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
       printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
       printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
       printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
       */

       memcpy((buffer+position),&fichier->entetebmp.taille_image,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.largeur,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.hauteur,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.plans,2);
       position+=2;
       memcpy((buffer+position),&fichier->entetebmp.profondeur,2);
       position+=2;
       memcpy((buffer+position),&fichier->entetebmp.compression,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.taille_image_totale,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.resolutionh,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.resolutionv,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.nbrcouleur,4);
       position+=4;
       memcpy((buffer+position),&fichier->entetebmp.nbrcouleuri,4);
       position+=4;

       if(fichier->entetebmp.plans!=1||fichier->entetebmp.profondeur!=24||fichier->entetebmp.compression!=0||fichier->entetebmp.nbrcouleur!=0||fichier->entetebmp.nbrcouleuri!=0)
       {
       printf("Impossible d'enregistrer l'image\n");
       free(buffer);
       return 0;
       }

       for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
       {
       for(j=0;j<fichier->entetebmp.largeur;j++)
                                   {
                                   memcpy((buffer+position),&fichier->image[i][j].b,1);
                                   position+=1;
                                   memcpy((buffer+position),&fichier->image[i][j].g,1);
                                   position+=1;
                                   memcpy((buffer+position),&fichier->image[i][j].r,1);
                                   position+=1;
                                   }
       for(k=0;k<fichier->entetebmp.largeur%4;k++)
                                                 {
                                                 memcpy((buffer+position),&zero,1);
                                                 position+=1;
                                                 }
       }

       f=fopen(nom,"wb");
       fwrite((unsigned char *)buffer,1,longueur,f);
       fclose(f);
       free(buffer);
       return 1;
}

struct fichierimage *nouveau(int largeur,int hauteur)
{
       int i,j;
       struct fichierimage *fichier;
       int longueur;

       if(largeur>5000||hauteur>5000||largeur<=0||hauteur<=0)
	{
	return(NULL);
	}

       longueur=14+40+3*largeur*hauteur+(largeur%4)*hauteur;
       fichier=(struct fichierimage *)malloc(sizeof(struct fichierimage));

       // ecriture de l'entete du fichier

       fichier->entetefichier.idformat[0]='B';
       fichier->entetefichier.idformat[1]='M';
       fichier->entetefichier.taille_fichier=40+3*largeur*hauteur+(largeur%4)*hauteur;
       fichier->entetefichier.reserve=0;
       fichier->entetefichier.debut=54;

       // ecriture de l'entete de l'image

       fichier->entetebmp.taille_image=40;
       fichier->entetebmp.largeur=largeur;
       fichier->entetebmp.hauteur=hauteur;
       fichier->entetebmp.plans=1;
       fichier->entetebmp.profondeur=24;
       fichier->entetebmp.compression=0;
       fichier->entetebmp.taille_image_totale=40+3*largeur*hauteur+(largeur%4)*hauteur;
       fichier->entetebmp.resolutionh=1;
       fichier->entetebmp.resolutionv=1;
       fichier->entetebmp.nbrcouleur=0;
       fichier->entetebmp.nbrcouleuri=0;

       // lecture de l'ente du fichier

       /*
       printf("id format                :%c%c\n",fichier->entetefichier.idformat[0],fichier->entetefichier.idformat[1]);
       printf("taille fichier           :%d\n",fichier->entetefichier.taille_fichier);
       printf("reserve                  :%d\n",fichier->entetefichier.reserve);
       printf("debut                    :%d\n",fichier->entetefichier.debut);
       */

       // lecture de l'ente de l'image

       /*
       printf("taille image             :%d\n",fichier->entetebmp.taille_image);
       printf("largeur                  :%d\n",fichier->entetebmp.largeur);
       printf("hauteur                  :%d\n",fichier->entetebmp.hauteur);
       printf("plans                    :%d\n",fichier->entetebmp.plans);
       printf("profondeur               :%d\n",fichier->entetebmp.profondeur);
       printf("compression              :%d\n",fichier->entetebmp.compression);
       printf("taille image totale      :%d\n",fichier->entetebmp.taille_image_totale);
       printf("resolution h             :%d\n",fichier->entetebmp.resolutionh);
       printf("resulution v             :%d\n",fichier->entetebmp.resolutionv);
       printf("nbr couleurs             :%d\n",fichier->entetebmp.nbrcouleur);
       printf("nbr couleurs importantes :%d\n",fichier->entetebmp.nbrcouleuri);
       */

       // mise de l'image en memoire

       for(i=fichier->entetebmp.hauteur-1;i>=0;i--)
       {
       for(j=0;j<fichier->entetebmp.largeur;j++)
                                   {
                                   fichier->image[i][j].b=0;
                                   fichier->image[i][j].g=0;
                                   fichier->image[i][j].r=0;
                                   }
       }

       return fichier;
}

void caracteristiques_image(struct fichierimage *fichier) {
    char *caracteristiques[] = {
        "Taille Fichier", "Taille Image", "Largeur", "Alignement", "Hauteur",
        "Plans", "Profondeur", "Compression", "Taille Image Totale", "Resolution H",
        "Resolution V", "Nbr Couleur", "Nbr Couleur i"
    };

    char tableau[2][13][50];

    for (int i = 0; i < 13; i++) {
        strncpy(tableau[0][i], caracteristiques[i], 50);
    }

    snprintf(tableau[1][0], 50, "%d", fichier->entetefichier.taille_fichier);
    snprintf(tableau[1][1], 50, "%d", fichier->entetebmp.taille_image);
    snprintf(tableau[1][2], 50, "%d", fichier->entetebmp.largeur);
    snprintf(tableau[1][3], 50, "%d", fichier->entetebmp.alignement);
    snprintf(tableau[1][4], 50, "%d", fichier->entetebmp.hauteur);
    snprintf(tableau[1][5], 50, "%d", fichier->entetebmp.plans);
    snprintf(tableau[1][6], 50, "%d", fichier->entetebmp.profondeur);
    snprintf(tableau[1][7], 50, "%d", fichier->entetebmp.compression);
    snprintf(tableau[1][8], 50, "%d", fichier->entetebmp.taille_image_totale);
    snprintf(tableau[1][9], 50, "%d", fichier->entetebmp.resolutionh);
    snprintf(tableau[1][10], 50, "%d", fichier->entetebmp.resolutionv);
    snprintf(tableau[1][11], 50, "%d", fichier->entetebmp.nbrcouleur);
    snprintf(tableau[1][12], 50, "%d", fichier->entetebmp.nbrcouleuri);

    for (int i = 0; i < 13; i++) {
        printf("%-3s ", tableau[0][i]); // Aligner les caractéristiques avec un espacement fixe
    }
    printf("\n");

    for (int j = 0; j < 13; j++) {
        printf("%-13s", tableau[1][j]); 
    }
    printf("\n");
    free(fichier);
}


struct fichierimage *interface_selection_fichier() {
    char touche;
    char c;
    printf("Le programme va afficher votre répertoire d'image.\n");
    printf("Appuyez sur une touche pour continuer ou sur Entree pour quitter...\n");
    touche = getch(); // Attendre une touche sans nécessiter Entrée
    if (touche == '\r') {  // '\r' correspond à la touche Entrée
        printf("Sortie du programme...\n");
        return NULL;
    }
    system("dir \"images source\"");

    char nomFichier[100];
    int i = 0;
    

    const char chemin[] = "images source/";
    while ((c = getchar()) != '\n' && c != EOF);  // Vider le tampon de l'ancienne entrée, seule solution que j'ai trouvé

    while (chemin[i] != '\0') {
        nomFichier[i] = chemin[i];  // ajouter le chemin
        i++;
    }

    printf("Entrez le nom du fichier (sans extension) : ");

    // lire chaque caractère avec getchar()
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < 100 - 1) {
            nomFichier[i++] = c;
        }
    }
    if (i == 14) {
        // si i = 14 l'utilsateur a juste appuyé sur entrée
        printf("Aucun nom de fichier saisi. Sortie du programme...\n");
        return 0;
    }

    // Ajouter l'extension .bmp
    nomFichier[i++] = '.';
    nomFichier[i++] = 'b';
    nomFichier[i++] = 'm';
    nomFichier[i++] = 'p';
    nomFichier[i] = '\0';

    printf("Nom du fichier chargé : %s\n", nomFichier);
    struct fichierimage* image_source = NULL;
    image_source = charger(nomFichier);
    char commande[100];
    sprintf(commande, "start \"\" \"%s\"", nomFichier);
    system(commande);
    return image_source;

}
int interface_enregistrement(struct fichierimage* image_a_enregistrer) {
    int z = 0;
    char nomFichierResult[100];
    char c;
    const char chemin_result[] = "images resultat/";

    while (chemin_result[z] != '\0') {
        nomFichierResult[z] = chemin_result[z];  // ajouter le chemin
        z++;
    }

    while ((c = getchar()) != '\n' && c != EOF);
    printf("Entrez le nom du fichier resultat (sans extension) : ");
    while ((c = getchar()) != '\n' && c != EOF) {
            nomFichierResult[z++] = c;
    }
    if (z == 16) {
        printf("Aucun nom de fichier saisi pour le resultat. Sortie du programme...\n");
        free(image_a_enregistrer);
        return 0;
    }

    // Ajouter l'extension .bmp au fichier résultat
    nomFichierResult[z++] = '.';
    nomFichierResult[z++] = 'b';
    nomFichierResult[z++] = 'm';
    nomFichierResult[z++] = 'p';
    nomFichierResult[z] = '\0';
    printf("Nom du fichier enregistre : %s", nomFichierResult);
    enregistrer(nomFichierResult, image_a_enregistrer);
    char commande[100];
    sprintf(commande, "start \"\" \"%s\"", nomFichierResult);
    system(commande);
}
void seuillage(struct fichierimage* image_source) {
    struct fichierimage* copie = NULL;
    copie = nouveau(image_source->entetebmp.largeur, image_source->entetebmp.hauteur);
    int choix;
    printf("Entrez le seuil : ...");
    scanf("%d", &choix);
    for (int y = 0; y < image_source->entetebmp.hauteur; y++) {
        for (int x = 0; x < image_source->entetebmp.largeur; x++) {
            if (image_source->image[x][y].r > choix) {
                copie->image[y][x].r = 0;
                copie->image[y][x].g = 0;
                copie->image[y][x].b = 0;
            }
            else {
                copie->image[y][x].r = 255;
                copie->image[y][x].g = 255;
                copie->image[y][x].b = 255;
            }
        }
    }
    interface_enregistrement(copie);
    free(copie);
}
int symetrie(struct fichierimage* image_source) {
    /*
    Procédure symétrie:
    résultat: fonctionne correctement, il faudrait réviser les accents.
    */
    struct fichierimage* copie = NULL;
    copie = nouveau(image_source->entetebmp.largeur, image_source->entetebmp.hauteur);

    printf("Choisissez le type de symetrie :\n");
    printf("1 - Symetrie verticale\n");
    printf("2 - Symetrie horizontale\n");
    printf("Appuyez sur Entree pour quitter... :");
    char choix = getchar();

    if (choix == '\n') {
        printf("Sortie du programme...\n");
        free(image_source);
        free(copie);
        return 0;
    }

    int largeur = image_source->entetebmp.largeur;
    int hauteur = image_source->entetebmp.hauteur;

    switch (choix) {
    case '1': // Symétrie verticale
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                copie->image[y][x].r = image_source->image[y][largeur - 1 - x].r;
                copie->image[y][x].g = image_source->image[y][largeur - 1 - x].g;
                copie->image[y][x].b = image_source->image[y][largeur - 1 - x].b;
            }
        }
        printf("Symetrie verticale effectuee\n");
        break;

    case '2': // Symétrie horizontale
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                copie->image[y][x].r = image_source->image[hauteur - 1 - y][x].r;
                copie->image[y][x].g = image_source->image[hauteur - 1 - y][x].g;
                copie->image[y][x].b = image_source->image[hauteur - 1 - y][x].b;
            }
        }
        printf("Symetrie horizontale effectuee\n");
        break;

    default:
        printf("Option non valide\n");
        free(image_source);
        free(copie);
        return 0;
    }
    interface_enregistrement(copie);
    free(copie);

}


int bordure(struct fichierimage* image_source) {
    /*
    * Procédure bordure:
    * Résultat: le sous programme fonctionne correctement, cependant il
    * n'affiche pas le dossier et n'affiche pas le résultat. Il faudra revoir l'interface.
    * Autheur: PHOULCHAND Mathieu
    * Date de création: 13/11/2024
    * Date de modification: 18/11/2024
    */
  
    struct fichierimage* copie = NULL;
    int choix;
    copie = nouveau(image_source->entetebmp.largeur+2, image_source->entetebmp.hauteur+2);
    int largeur = image_source->entetebmp.largeur;
    int hauteur = image_source->entetebmp.hauteur;
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i+1][j+1].r = image_source->image[i][j].r;
            copie->image[i+1][j+1].g = image_source->image[i][j].g;
            copie->image[i+1][j+1].b = image_source->image[i][j].b;
        }
    }
    printf("Choisissez le type de bordure :\n");
    printf("1 - Remplissage avec pixels 0\n");
    printf("2 - Remplissage avec pixels voisins\n");
    printf("Appuyez sur Entree pour quitter... :");
    char input = getchar();

    if (input == '\n') {
        printf("Sortie du programme...\n");
        free(copie);
        return 0;
    }
    switch (input) {
    case '1': // Remplissage avec pixels 0
        for (int i = 0; i < hauteur+2; i++) {
            
            copie->image[i][0].r = 0;
            copie->image[i][0].g = 0;
            copie->image[i][0].b = 0;

            copie->image[i][largeur+1].r = 0;
            copie->image[i][largeur+1].g = 0;
            copie->image[i][largeur+1].b = 0;

            
        }
        for (int j = 0; j < largeur+2; j++) {
            
            copie->image[0][j].r = 0;
            copie->image[0][j].g = 0;
            copie->image[0][j].b = 0;

            copie->image[hauteur+1][j].r = 0;
            copie->image[hauteur+1][j].g = 0;
            copie->image[hauteur+1][j].b = 0;


        }
        break;

    case '2': // remplissage avec pixels voisin
        for (int i = 0; i < hauteur; i++) {
            copie->image[i+1][0].r = image_source->image[i][0].r;
            copie->image[i+1][0].g = image_source->image[i][0].g;
            copie->image[i+1][0].b = image_source->image[i][0].b;

            copie->image[i+1][largeur + 1].r = image_source->image[i][largeur - 1].r;
            copie->image[i+1][largeur + 1].g = image_source->image[i][largeur - 1].g;
            copie->image[i+1][largeur + 1].b = image_source->image[i][largeur-1].b;
        }
        for (int j = 0; j < largeur; j++) {
            copie->image[0][j+1].r = image_source->image[0][j].r;
            copie->image[0][j+1].g = image_source->image[0][j].g;
            copie->image[0][j+1].b = image_source->image[0][j].b;

            copie->image[hauteur + 1][j+1].r = image_source->image[hauteur-1][j].r;
            copie->image[hauteur + 1][j+1].g = image_source->image[hauteur-1][j].g;
            copie->image[hauteur + 1][j+1].b = image_source->image[hauteur-1][j].b;
        }
        copie->image[0][0] = image_source->image[0][0];  // Coin haut-gauche
        copie->image[0][largeur + 1] = image_source->image[0][largeur - 1];  // Coin haut-droit
        copie->image[hauteur + 1][0] = image_source->image[hauteur - 1][0];  // Coin bas-gauche
        copie->image[hauteur + 1][largeur + 1] = image_source->image[hauteur - 1][largeur - 1];  // Coin bas-droit
        break;

    default:
        printf("Option non valide\n");
        free(copie);
        return 0;
    }
    interface_enregistrement(copie);
    free(copie);
}
int rotation90(struct fichierimage* img_originale) {
        printf("Choisir la rotation: \n");
        printf("D - Rotation 90 degres droite\n");
        printf("G - Rotation 90 degres gauche\n");
        int largeur = img_originale->entetebmp.largeur;
        int hauteur = img_originale->entetebmp.hauteur;
        // copie
        struct fichierimage* rotated = nouveau(hauteur, largeur);

        char choice;
        choice = getchar();


        switch (choice) {
        case 'D':
        case 'd':
            for (int i = 0; i < hauteur; i++) {
                for (int j = 0; j < largeur; j++) {
                    rotated->image[j][hauteur - 1 - i] = img_originale->image[i][j];
                }
            }
            break;

        case 'G':
        case 'g':
            for (int i = 0; i < hauteur; i++) {
                for (int j = 0; j < largeur; j++) {
                    rotated->image[largeur - 1 - j][i] = img_originale->image[i][j];
                }
            }
            break;


        default:
            printf("Choix incorrect\n");
            free(rotated);
            return NULL;
        }
        interface_enregistrement(rotated);
        free(rotated);

    }
void contraste(struct fichierimage* fichier) {
    /*Objectif: Implémenter en C un programme pour appliquer un traitement de contraste.
    Résultat: le programme fonctionne.
    Remarque: avec Grains2, les pixels clairs ne ressortissent pas très bien.
    Autheur: PHOULCHAND Mathieu
    Date de modification: 26/11/2024*/

    //Variation entre niveaux de gris min et max

    struct fichierimage* copie = NULL;
    int largeur = fichier->entetebmp.largeur;
    int hauteur = fichier->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);

    float max = 0;
    float min = 255;

    // Recherche des niveaux min et max et moyenne
    float somme = 0;
    int total_pixels = largeur * hauteur;
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            float pixel = fichier->image[i][j].r;
            if (pixel > max) max = pixel;
            if (pixel < min) min = pixel;
            somme += pixel;
        }
    }
    float moyenne = somme / total_pixels;
    float C = (max - min) / (max + min);
    float composantetemp;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            float pixel = fichier->image[i][j].r;
            if (pixel > moyenne) {
                 composantetemp = ((pixel - min) / (max - min)) * 255 * C;
            }
            else {
                composantetemp = ((pixel - min) / (max + min)) * 255 * C;
            }
            
            if (composantetemp > 255) composantetemp = 255;
            if (composantetemp < 0) composantetemp = 0;

            copie->image[i][j].r = composantetemp;
            copie->image[i][j].g = composantetemp;
            copie->image[i][j].b = composantetemp;
        }
    }

    interface_enregistrement(copie);
    free(copie);
}
void filtre_median(struct fichierimage* fichier2) {
    /*Objectif: Appliquer un filtre médian afin de réduire le bruit d'une image.
    Résultat: le sous-programme fonctionne correctement.
    Remarque 1: le traitement de l'image prend du temps, il n'est pas optimal et nécéssite une optimisation
    Remarque 2: le resultat ne supprime pas entierement le bruit comme vu en cours, il y a sans doute une autre méthode à employer.
    Date de creation: 23/11/2024
    Date de modification: 26/11/2024
    Autheur: Mathieu PHOULCHAND*/
    struct fichierimage* copiemedian = NULL;
    int largeur = fichier2->entetebmp.largeur;
    int hauteur = fichier2->entetebmp.hauteur;
    copiemedian = nouveau(largeur, hauteur);
    int tableau[3][3];
    int mediane;
    int tableau_9_trie[9];

    // Copie de l'image originale
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copiemedian->image[i][j].r = fichier2->image[i][j].r;
            copiemedian->image[i][j].g = fichier2->image[i][j].g;
            copiemedian->image[i][j].b = fichier2->image[i][j].b;
        }
    }

    // Application du filtre médian
    for (int i = 1; i < hauteur - 1; i++) {
        for (int j = 1; j < largeur - 1; j++) {
            // Récupération des 9 pixels du voisinage
            int m = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    tableau_9_trie[m] = copiemedian->image[i + k][j + l].r;
                    m++;
                }
            }

            // Tri du tableau
            for (int k = 0; k < 9 - 1; k++) {
                for (int l = 0; l < 9 - k - 1; l++) {
                    if (tableau_9_trie[l] > tableau_9_trie[l + 1]) {
                        int temp = tableau_9_trie[l];
                        tableau_9_trie[l] = tableau_9_trie[l + 1];
                        tableau_9_trie[l + 1] = temp;
                    }
                }
            }

            // Récupération de la médiane
            mediane = tableau_9_trie[4];

            // Mise à jour du pixel
            copiemedian->image[i][j].r = mediane;
            copiemedian->image[i][j].g = mediane;
            copiemedian->image[i][j].b = mediane;
        }
    }

    interface_enregistrement(copiemedian);
    free(copiemedian);
}

void LUT1(struct fichierimage * originale) {
    /*Objectif : Création d'une LUT et modifier chaque composantes de chaques pixels.
    Résultat: le sous programme fonctionne correctement.
    Methodes employées: 
    Date : 5/12/2024
    Auteur: Mathieu PHOULCHAND
    */
    int LUT[3][256];

    for (int i = 0; i < 256; i++) {
        //min 0,255 c'est pour normaliser, on prend 255 si c'est sup a 255
        LUT[0][i] = min(255,(0.393 * i + 0.769 * i + 0.189 * i));
        LUT[1][i] = min(255,(0.349 * i + 0.686 * i + 0.168 * i));
        LUT[2][i] = min(255,(0.272 * i + 0.534 * i + 0.131 * i));
    }

    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = LUT[0][originale->image[i][j].r];
            copie->image[i][j].g = LUT[1][originale->image[i][j].g];
            copie->image[i][j].b = LUT[2][originale->image[i][j].b];
        }
    }

    interface_enregistrement(copie);
    free(copie);

}

void LUT2(struct fichierimage* originale) {
    /*Objectif : Création d'une LUT et modifier chaque composantes de chaques pixels.
    Résultat: le sous programme semble fonctionner correctement.
    Methodes employées:
    Date : 5/12/2024
    Auteur: Mathieu PHOULCHAND
    */
    int LUT[3][256];

    for (int i = 0; i < 256; i++) {
        LUT[0][i] = pow(i, 2) / 255;
        LUT[1][i] = sqrt(i);
        LUT[2][i] = 255 - i;
    }

    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = LUT[0][originale->image[i][j].r];
            copie->image[i][j].g = LUT[1][originale->image[i][j].g];
            copie->image[i][j].b = LUT[2][originale->image[i][j].b];
        }
    }

    interface_enregistrement(copie);
    free(copie);

}
void agrandissement(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    int echelle;
    printf("Entrez l'echelle: ");
    scanf("%d", &echelle);
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur*echelle, hauteur*echelle);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            for (int k = i*echelle; k < (i+1)*echelle; k++) {
                for (int l = j*echelle; l < (j+1)*echelle; l++) {
                    copie->image[k][l].r = originale->image[i][j].r;
                    copie->image[k][l].g = originale->image[i][j].g;
                    copie->image[k][l].b = originale->image[i][j].b;
                }
            }
        }
    }
    interface_enregistrement(copie);
    free(copie);
}
void negatif(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = 255 - originale->image[i][j].r;
            copie->image[i][j].g = 255 - originale->image[i][j].g;
            copie->image[i][j].b = 255 - originale->image[i][j].b;
        }
    }
    interface_enregistrement(copie);
    free(copie);
}

void transfo_nv_gris(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    int moyenne_temp;
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            moyenne_temp = (originale->image[i][j].r + originale->image[i][j].g + originale->image[i][j].b) / 3;
            copie->image[i][j].r = moyenne_temp;
            copie->image[i][j].g = moyenne_temp;
            copie->image[i][j].b = moyenne_temp;
        }
    }
    interface_enregistrement(copie);
    free(copie);
}

void mirroir(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = originale->image[i][largeur - j - 1].r;
            copie->image[i][j].g = originale->image[i][largeur - j - 1].g;
            copie->image[i][j].b = originale->image[i][largeur - j - 1].b;
        }
    }
    interface_enregistrement(copie);
    free(copie);
}

void monochrome(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    int couleur;
    printf("Entrez la couleur: ");
    scanf("%d", &couleur);
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (couleur == 1) {
                copie->image[i][j].r = originale->image[i][j].r;
                copie->image[i][j].g = 0;
                copie->image[i][j].b = 0;
            }
            else if (couleur == 2) {
                copie->image[i][j].r = 0;
                copie->image[i][j].g = originale->image[i][j].g;
                copie->image[i][j].b = 0;
            }
            else if (couleur == 3) {
                copie->image[i][j].r = 0;
                copie->image[i][j].g = 0;
                copie->image[i][j].b = originale->image[i][j].b;
            }
        }
    }
    interface_enregistrement(copie);
    free(copie);
}

void reduction(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    int echelle;
    printf("Entrez l'echelle: ");
    scanf("%d", &echelle);
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    int new_largeur = largeur / echelle;
    int new_hauteur = hauteur / echelle;
    copie = nouveau(new_largeur, new_hauteur);
    for (int i = 0; i < new_hauteur; i++) {
        for (int j = 0; j < new_largeur; j++) {
            int r = 0, g = 0, b = 0;
            for (int x = 0; x < echelle; x++) {
                for (int y = 0; y < echelle; y++) {
                    r += originale->image[i * echelle + x][j * echelle + y].r;
                    g += originale->image[i * echelle + x][j * echelle + y].g;
                    b += originale->image[i * echelle + x][j * echelle + y].b;
                }
            }
            r /= (echelle * echelle);
            g /= (echelle * echelle);
            b /= (echelle * echelle);

            copie->image[i][j].r = r;
            copie->image[i][j].g = g;
            copie->image[i][j].b = b;
        }
    }
    interface_enregistrement(copie);
    free(copie);
}
void histogramme(struct fichierimage* originale, int histogramme[256]) {
    /*Résultat: le sous programme fonctionne.
    * Remarque : l'affichage pourrait être amélioré
    Auteur:  PHOULCHAND Mathieu*/
    for (int i = 0; i < 256; i++) {
        histogramme[i] = 0; // Initialisation
    }

    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int niveau_gris = (originale->image[i][j].r +
                originale->image[i][j].g +
                originale->image[i][j].b) / 3;
            histogramme[niveau_gris]++;
        }
    }

    printf("Histogramme :\n");
    for (int i = 0; i < 256; i++) {
        printf("Intensite %d : %d\n", i, histogramme[i]);
    }

}
void augmenter_luminosite(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    int valeur;
    printf("Entrez la valeur: ");
    scanf("%d", &valeur);
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = fmin(255, fmax(0, originale->image[i][j].r + valeur));
            copie->image[i][j].g = fmin(255, fmax(0, originale->image[i][j].g + valeur));
            copie->image[i][j].b = fmin(255, fmax(0, originale->image[i][j].b + valeur));
        }
    }
    interface_enregistrement(copie);
    free(copie);
}

void inversion(struct fichierimage* originale) {
    /*Résultat: le sous programme fonctionne.
    Auteur:  PHOULCHAND Mathieu*/
    struct fichierimage* copie = NULL;
    int largeur = originale->entetebmp.largeur;
    int hauteur = originale->entetebmp.hauteur;
    copie = nouveau(largeur, hauteur);
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            copie->image[i][j].r = originale->image[i][j].b;
            copie->image[i][j].g = originale->image[i][j].r;
            copie->image[i][j].b = originale->image[i][j].g; 
        }
    }
    interface_enregistrement(copie);
    free(copie);
}