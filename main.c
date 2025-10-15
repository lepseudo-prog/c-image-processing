#define _CRT_SECURE_NO_WARNINGS
#include "image.h"

//------------------------------------------------------------------------------
// Code source pour le projet d'UE035
// description : (les fonctions sont d�finit dans image.h)
//
// les pointeurs images dans ce code sont de type : struct fichierimage *
//
// fonction struct fichierimage * charger(char *)
// permet de charger une image presente sur le disque en memoire vive, la fonction
// renvoie un pointeur de type : struct fichierimage *
//
// fonction int enregistrer(struct fichierimage *,char *)
// permet d'enregistrer une image sur le disque sous le nom donn� en arg2, cette
// image est contenue dans une pointeur de type : struct fichierimage * fournit en arg1
//
// fonction struct fichierimage * nouveau(int,int)
// permet de creer une image en memoire de largeur arg1 et de hauteur arg2, la fonction
// retourne un pointeur de type : struct fichierimage *
//------------------------------------------------------------------------------

int main()
{
    // variable permettant le parcours d'une image
            // int i,j;

    // exemple de d�claration d'un pointeur image
            //struct fichierimage *fichier=NULL;

    // exemple pour effectuer un copier coller
    /*
    fichier=charger("image.bmp");
    enregistrer("resultat.bmp",fichier);
    free(fichier);
    */

    // modification ou lecture de pixels d'une image
    /*
    fichier=nouveau(100,100);
    for(i=fichier->entetebmp.hauteur;i>=0;i--)
    for(j=0;j<fichier->entetebmp.largeur;j++)
                    {
                    fichier->image[i][j].r=0;
                    fichier->image[i][j].g=255;
                    fichier->image[i][j].b=255;
                    }

    enregistrer("resultat.bmp",fichier);
    free(fichier);
    */

    //Programme principal
    int choix;
    printf("*******************************\n");
    printf("*   Traitement d'image   *\n");
    printf("*******************************\n\n");
    printf("1:  Seuillage                2:  Symetrie\n");
    printf("3:  Bordure                  4:  Rotation 90\n");
    printf("5:  Contraste                6:  Filtre Median\n");
    printf("7:  LUT1                     8:  LUT2\n");
    printf("9:  Agrandissement           10: Caracteristiques img\n");
    printf("11: Negatif                  12: Transfo en niveaux de gris\n");
    printf("13: Mirroir                  14: Monochrome\n");
    printf("15: Reduction                16: Histogramme\n");
    printf("17: Augmenter Luminosite     18: Inversion\n");

    printf("\nChoisir le traitement : ");
    if (scanf("%d", &choix) != 1) {
        printf("Entree invalide. Veuillez entrer un nombre.\n");
        return 1;
    }
    struct fichierimage* image = NULL;
    image = interface_selection_fichier();
    switch (choix) {
    case 1:
        seuillage(image);
        break;
    case 2:
        symetrie(image);
        break;
    case 3:
        bordure(image);
        break;
    case 4:
        rotation90(image);
        break;
    case 5:
        contraste(image);
        break;
    case 6:
        filtre_median(image);
        break;
    case 7:
        LUT1(image);
        break;
    case 8:
        LUT2(image);
        break;
    case 9:
        agrandissement(image);
        break;
    case 10:
        caracteristiques_image(image);
        break;
    case 11:
        negatif(image);
        break;

    case 12:
        transfo_nv_gris(image);
        break;
    case 13:
        mirroir(image);
        break;
    case 14:
        monochrome(image);
        break;
    case 15:
        reduction(image);
        break;
    case 16: {
        int hist[256];
        histogramme(image, hist);
        break;
    }
    case 17:
        augmenter_luminosite(image);
        break;
    case 18:
        inversion(image);
        break;
    default:
        printf("Option non reconnue. Fin du programme.\n");
        free(image);
        return 0;
    }
    free(image);
}