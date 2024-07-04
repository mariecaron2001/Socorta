#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TAILLENOM 25
#define TAILLERUE 50
#define TAILLEPRENOM 30
#define TAILLEVILLE 20
#define TAILLESPECIALITE 20
#define TAILLEHEURE 9
#define TAILLEGERANT 3
#define TAILLEDATE 11
#define TAILLENUMREG 16
#define TAILLEFICHIEROUVRIERS 100
#define TAILLEFICHIERCHANTIERS 50
#define NOMFICHIEROUVRIERS "Ouvriers.dat"
#define NOMFICHIERESTOCCUPE "EstOccupe.dat"
#define NOMFICHIERCHANTIER "Chantiers.dat"

typedef struct
{
    short jour;
    short mois;
    short annee;
}Date;

typedef struct
{
    int NumReg;
    char Nom[TAILLENOM];
    char Prenom[TAILLEPRENOM];
    char Rue[TAILLERUE];
    int CodePostal;
    char Ville[TAILLEVILLE];
    char Specialite[TAILLESPECIALITE];
    Date DateNaissance;
    Date DateEngagement;
}Ouvriers;

typedef struct
{
    int NumReg;
    char NomOuvrier[TAILLENOM];
    char PrenomOuvrier[TAILLEPRENOM];
    int position;
}IndexOuvriers;

typedef struct
{
    long NumChantier;
    char NomChantier[TAILLENOM];
    char Rue[TAILLERUE];
    int CodePostal;
    char Ville[TAILLEVILLE];
    char MaitreOuvrage[TAILLEPRENOM];
    float Montant;
    int Duree;
    char Gerant[TAILLEGERANT];
}Chantier;

typedef struct
{
    long NumChantier;
    char NomChantier[TAILLENOM];
    float Montant;
    int position;
}IndexChantier;

typedef struct
{
    int NumReg;
    long NumChantier;
    Date Date;
    char Heure[TAILLEHEURE];
}EstOccupe;

//Prototypes des fonctions qui concernent les ouvriers
void AjoutOuvrier(IndexOuvriers *,short);
void SupprimeOuvrier(IndexOuvriers *,short);
void ModifOuvrier(IndexOuvriers *,short);
void AfficheIndexOuvriers(IndexOuvriers *,short);
void AfficheUnOuvrier(IndexOuvriers *,short);
void Tri_IndexOuvriers(IndexOuvriers *,short);
void InitIndexOuvriers(IndexOuvriers *,short);
void BidonnageFichierOuvriers();
void MiseAJourIndexOuvriers(IndexOuvriers *,short);
short VerifNumReg(int,IndexOuvriers *,short);
short RechercheOuvrier(char *,IndexOuvriers *,short);
short MenuModif();

//Prototypes des fonctions qui concernent les chantiers
void AjoutChantier(IndexChantier *,IndexOuvriers *,short);
void AfficheIndexChantiers(IndexChantier *,short);
void Tri_IndexChantier(IndexChantier *,short);
void InitIndexChantier(IndexChantier *,short);
void BidonnageFichierChantier();
void MiseAJourIndexChantier(IndexChantier *,short);
short VerifNumChantier(int,IndexChantier *,short);

//Protypes des fonctions qui concernent EstOccupe
void AjoutEstOccupe(IndexChantier *,IndexOuvriers *);
void AfficheEstOccupe();
short VerifEstOccupe(long,long,Date);
short RechercheEstOccupe(int);

//Prototypes des fonctions de saisie des chaînes de caractères
void LireChaine(char *,short);
void LireRue(char *,short);
void SaisieDate(Date *);
void SaisieSpecialite(char *);
void LireGerant(char *,short);
void SaisieHeure(char *,short);

int main()
{
    short choix=0;
    short continuer=1;
    FILE *fOuvriers,*fChantiers,*fEstOccupe;
    IndexOuvriers indexOuvriers[TAILLEFICHIEROUVRIERS];
    IndexChantier indexChantiers[TAILLEFICHIERCHANTIERS];

    fOuvriers=fopen(NOMFICHIEROUVRIERS,"rb");
    if(fOuvriers==(FILE *)NULL)
    {
        BidonnageFichierOuvriers();
    }
    fclose(fOuvriers);

    fChantiers=fopen(NOMFICHIERCHANTIER,"rb");
    if(fChantiers==(FILE *)NULL)
    {
        BidonnageFichierChantier();
    }
    fclose(fChantiers);

    fEstOccupe=fopen(NOMFICHIERESTOCCUPE,"rb");
    if(fEstOccupe==(FILE *)NULL)
    {
        fEstOccupe=fopen(NOMFICHIERESTOCCUPE,"ab");
    }
    fclose(fEstOccupe);

    InitIndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);
    MiseAJourIndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);

    InitIndexChantier(indexChantiers,TAILLEFICHIERCHANTIERS);
    MiseAJourIndexChantier(indexChantiers,TAILLEFICHIERCHANTIERS);

    while(continuer==1)
    {
        printf("\nQue souhaitez-vous faire?");
        printf("\n1. Ajouter un ouvrier.");
        printf("\n2. Supprimer un ouvrier.");
        printf("\n3. Modifier un ouvrier.");
        printf("\n4. Afficher vos ouvriers.");
        printf("\n5. Ajouter un chantier.");
        printf("\n6. Afficher vos chantiers.");
        printf("\n7. Ajouter un horaire.");
        printf("\n8. Afficher les horaires.");
        printf("\n9. Quitter.");
        printf("\nVotre choix :");
        fflush(stdin);
        scanf("%hd",&choix);

        switch(choix)
        {
            case 1:
                {
                    AjoutOuvrier(indexOuvriers,TAILLEFICHIEROUVRIERS);
                    MiseAJourIndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);
                }
                break;

            case 2:
                {
                    SupprimeOuvrier(indexOuvriers,TAILLEFICHIEROUVRIERS);
                    MiseAJourIndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);
                }
                break;

            case 3:
                {
                    ModifOuvrier(indexOuvriers,TAILLEFICHIEROUVRIERS);
                }
                break;

            case 4:
                {
                    Tri_IndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);
                    AfficheIndexOuvriers(indexOuvriers,TAILLEFICHIEROUVRIERS);
                }
                break;

            case 5:
                {
                    AjoutChantier(indexChantiers,indexOuvriers,TAILLEFICHIERCHANTIERS);
                    MiseAJourIndexChantier(indexChantiers,TAILLEFICHIERCHANTIERS);
                }
                break;

            case 6:
                {
                    Tri_IndexChantier(indexChantiers,TAILLEFICHIERCHANTIERS);
                    AfficheIndexChantiers(indexChantiers,TAILLEFICHIERCHANTIERS);
                }
                break;

            case 7:
                {
                    AjoutEstOccupe(indexChantiers,indexOuvriers);
                }
                break;

            case 8:
                {
                    AfficheEstOccupe();
                }
                break;

            case 9:
                {
                    continuer=0;
                }
                break;

            default:
                {
                    printf("\nChoix pas valide,recommencez.\n");
                }
                break;
        }
    }

    return 0;
}

/*
INPUT : Pointeur de l'index des ouvriers + taille max de celui-ci
PROCESS : Ajout d'un ouvrier
OUTPUT : /
*/
void AjoutOuvrier(IndexOuvriers *pIOuvriers,short limite)
{
    FILE *fOuvriers;
    short i=0;
    short saisie=0;
    short offset=-1;
    Ouvriers mesouvriers;
    char chaine[TAILLENOM];
    int NumeroRegistreNational=0;
    IndexOuvriers *pTemporaire=pIOuvriers;

    while(i<TAILLEFICHIEROUVRIERS && saisie==0)
    {
        if(i==TAILLEFICHIEROUVRIERS)
        {
            printf("\nEspace libre non trouve.\n");
        }
        else
        {
            if(pIOuvriers->NumReg==-1)
            {
                fOuvriers=fopen(NOMFICHIEROUVRIERS,"r+b");

                if(fOuvriers==(FILE *)NULL)
                {
                    printf("\nImpossible d'ouvrir le fichier ouvriers.\n");
                }
                else
                {
                    printf("\nEncodage d'un nouvel ouvrier:\n");

                    while(offset==-1)
                    {
                        printf("\nEntrez son numero de registre national:\n");
                        fflush(stdin);
                        scanf("%d",&NumeroRegistreNational);

                        offset=VerifNumReg(NumeroRegistreNational,pTemporaire,TAILLEFICHIEROUVRIERS);

                        if(offset!=-1)
                        {
                            printf("\nLe numero de registre national existe deja!\n");
                            offset=-1;
                        }
                        else
                        {
                            offset=0;
                        }
                    }

                    pIOuvriers->NumReg=NumeroRegistreNational;
                    printf("\nEntrez son nom:\n");
                    LireChaine(chaine,TAILLENOM);
                    strcpy(pIOuvriers->NomOuvrier,chaine);
                    printf("\nEntrez son prenom:\n");
                    LireChaine(chaine,TAILLEPRENOM);
                    strcpy(pIOuvriers->PrenomOuvrier,chaine);

                    strcpy(mesouvriers.Nom,pIOuvriers->NomOuvrier);
                    strcpy(mesouvriers.Prenom,pIOuvriers->PrenomOuvrier);
                    mesouvriers.NumReg=pIOuvriers->NumReg;

                    printf("\nEntrez sa rue\n");
                    LireRue(mesouvriers.Rue,TAILLERUE);

                    do
                    {
                        printf("\nEntrez son code postal:\n");
                        fflush(stdin);
                        scanf("%d",(&mesouvriers.CodePostal));
                    }
                    while(mesouvriers.CodePostal<1000 || mesouvriers.CodePostal>9999);

                    printf("\nEntrez sa localite:\n");
                    LireChaine(mesouvriers.Ville,TAILLEVILLE);
                    printf("\nEntrez sa specialite:");
                    SaisieSpecialite(mesouvriers.Specialite);

                    do
                    {
                        printf("\nEntrez sa date de naissance (JJ/MM/AAAA):\n");
                        SaisieDate(&mesouvriers.DateNaissance);
                        printf("\nEntrez sa date d'engagement (JJ/MM/AAAA):\n");
                        SaisieDate(&mesouvriers.DateEngagement);

                        if((mesouvriers.DateNaissance.annee+16)>mesouvriers.DateEngagement.annee)
                        {
                            printf("\nDate d'engagement plus grande que date de naissance!");
                        }
                    }
                    while((mesouvriers.DateNaissance.annee+16)>mesouvriers.DateEngagement.annee);

                    fseek(fOuvriers,(pIOuvriers->position*((int)sizeof(Ouvriers))),SEEK_SET);
                    fwrite(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);
                    fclose(fOuvriers);
                    printf("\nOuvrier ajoute au fichier!\n");
                    saisie=1;
                }
            }
            else
            {
                i++;
                pIOuvriers++;
            }
        }
    }
}

/*
INPUT: Pointeur de l'index des ouvriers + taille max de celui-ci
PROCESS: Suppression d'un ouvrier
OUTPUT:/
*/
void SupprimeOuvrier(IndexOuvriers *pIOuvriers,short limite)
{
    FILE *fOuvriers;
    Ouvriers mesouvriers;
    short offset=-1,retour=-1;
    IndexOuvriers *pTemporaire;
    short confirmation=0;
    char nomTmp[TAILLENOM];

    printf("\nEntrez le nom de l'ouvrier a supprimer:\n");
    LireChaine(nomTmp,TAILLENOM);
    retour=RechercheOuvrier(nomTmp,pIOuvriers,TAILLEFICHIEROUVRIERS);

    if (retour==-1)
    {
        printf("\nOuvrier non trouve!\n");
    }
    else
    {
        pTemporaire=pIOuvriers+retour;
        offset=RechercheEstOccupe(pTemporaire->NumReg);

        if (offset==-1)
        {
            fOuvriers=fopen(NOMFICHIEROUVRIERS, "r+b");

            if (fOuvriers==(FILE*)NULL)
            {
                printf("\nImpossible d'ouvrir le fichier ouvriers.\n");
            }
            else
            {
                AfficheUnOuvrier(pTemporaire,TAILLEFICHIEROUVRIERS);

                printf("\nEtes-vous sur de vouloir le supprimer?");
                printf("\n1. Suppression annulee.");
                printf("\n2. Suppression comfirmee.");
                printf("\nFaites votre choix :\n");
                fflush(stdin);
                scanf("%hd", &confirmation);

                switch (confirmation)
                {
                    case 1:
                        {
                            printf("\nNous n'avons pas supprimer votre ouvrier.\n");
                        }
                        break;

                    case 2:
                        {
                            fseek(fOuvriers,pTemporaire->position*(int)sizeof(Ouvriers),SEEK_SET);
                            pTemporaire->NumReg = -1;
                            strcpy(pTemporaire->NomOuvrier, "VIDE");
                            strcpy(mesouvriers.Nom, pTemporaire->NomOuvrier);
                            mesouvriers.NumReg = pTemporaire->NumReg;
                            fwrite(&mesouvriers, sizeof(Ouvriers), 1, fOuvriers);
                            printf("\nVotre ouvrier a bien ete supprime!\n");
                        }
                        break;

                    default:
                        {
                            printf("\nChoix invalide.\n");
                        }
                        break;
                }

                fclose(fOuvriers);
            }
        }
        else
        {
            printf("\nImpossible de supprimer votre ouvrier car il a ete trouve dans un autre fichier.\n");
        }
    }
}

/*
INPUT: Pointeur de l'index des ouvriers + taille max de celui-ci
PROCESS: Modification d'un ouvrier
OUTPUT:/
*/
void ModifOuvrier(IndexOuvriers *pIOuvriers,short limite)
{
    FILE *fOuvriers;
    Ouvriers mesouvriers;
    short offset=-1;
    IndexOuvriers *pTemporaire;
    short retour=-1,choix=0,modif=1;
    int NumeroRegistreNational=0;
    char nomTmp[TAILLENOM];

    printf("\nEntrez le nom de l'ouvrier a modifier:\n");
    LireChaine(nomTmp,TAILLENOM);
    retour=RechercheOuvrier(nomTmp,pIOuvriers,TAILLEFICHIEROUVRIERS);

    if (retour==-1)
    {
        printf("\nOuvrier non trouve!\n");
    }
    else
    {
        fOuvriers=fopen(NOMFICHIEROUVRIERS, "r+b");

        if (fOuvriers==(FILE*)NULL)
        {
            printf("\nImpossible d'ouvrir le fichier ouvriers.\n");
        }
        else
        {
            pTemporaire=pIOuvriers+retour;

            while(modif==1)
            {
                fseek(fOuvriers,pTemporaire->position*((int)sizeof(Ouvriers)),SEEK_SET);
                fread(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);
                printf("\nVoici votre ouvrier:");
                printf("\nSon numero de registre national: %d",mesouvriers.NumReg);
                printf("\nSon nom: %s",mesouvriers.Nom);
                printf("\nSon prenom: %s",mesouvriers.Prenom);
                printf("\nSa date de naissance: %hd/%hd/%hd",mesouvriers.DateNaissance.jour,mesouvriers.DateNaissance.mois,mesouvriers.DateNaissance.annee);
                printf("\nSa rue: %s",mesouvriers.Rue);
                printf("\nSon code postal: %d",mesouvriers.CodePostal);
                printf("\nSa localite: %s",mesouvriers.Ville);
                printf("\nSa date d'engagement: %hd/%hd/%hd",mesouvriers.DateEngagement.jour,mesouvriers.DateEngagement.mois,mesouvriers.DateEngagement.annee);
                printf("\nSa specialite: %s\n",mesouvriers.Specialite);

                choix=MenuModif();

                switch(choix)
                {
                    case 1:
                        {
                            offset=RechercheEstOccupe(pTemporaire->NumReg);

                            if(offset==-1)
                            {
                                while(offset==-1)
                                {
                                    printf("\nEntrez son numero de registre national:\n");
                                    fflush(stdin);
                                    scanf("%d",&NumeroRegistreNational);

                                    offset=VerifNumReg(NumeroRegistreNational,pTemporaire,TAILLEFICHIEROUVRIERS);

                                    if(offset!=-1)
                                    {
                                        printf("\nLe numero de registre national existe deja!\n");
                                        offset=-1;
                                    }
                                    else
                                    {
                                        offset=0;
                                    }
                                }

                                pTemporaire->NumReg=NumeroRegistreNational;
                                mesouvriers.NumReg=pTemporaire->NumReg;
                            }
                            else
                            {
                                printf("\nImpossible de modifier le numero de registre national de votre ouvrier.\n");
                            }
                        }
                        break;

                    case 2:
                        {
                            printf("\nEntrez son nouveau nom:\n");
                            LireChaine(pTemporaire->NomOuvrier,TAILLENOM);
                            strcpy(mesouvriers.Nom,pTemporaire->NomOuvrier);
                        }
                        break;

                    case 3:
                        {
                            printf("\nEntrez son nouveau prenom:\n");
                            LireChaine(pTemporaire->PrenomOuvrier,TAILLEPRENOM);
                            strcpy(mesouvriers.Prenom,pTemporaire->PrenomOuvrier);
                        }
                        break;

                    case 4:
                        {
                          printf("\nEntrez sa nouvelle rue:\n");
                          LireRue(mesouvriers.Rue,TAILLERUE);
                        }
                        break;

                    case 5:
                        {
                            do
                            {
                                printf("\nEntrez son code postal:\n");
                                fflush(stdin);
                                scanf("%d",(&mesouvriers.CodePostal));
                            }
                            while(mesouvriers.CodePostal<1000 || mesouvriers.CodePostal>9999);
                        }
                        break;

                    case 6:
                        {
                          printf("\nEntrez sa nouvelle localite:\n");
                          LireChaine(mesouvriers.Ville,TAILLEVILLE);
                        }
                        break;

                    case 7:
                        {
                          printf("\nEntrez sa nouvelle specialite:");
                          SaisieSpecialite(mesouvriers.Specialite);
                        }
                        break;

                    case 8:
                        {
                          printf("\nEntrez sa nouvelle date de naissance:\n");
                          SaisieDate(&mesouvriers.DateNaissance);
                        }
                        break;

                    case 9:
                        {
                          printf("\nEntrez sa nouvelle date d'engagement:\n");
                          SaisieDate(&mesouvriers.DateEngagement);
                        }
                        break;

                    case 10:
                        {
                          modif=0;
                        }
                        break;

                    default:
                        {
                            printf("\nChoix pas valide,recommencez.\n");
                        }
                        break;
                }

                fseek(fOuvriers,pTemporaire->position*((int)sizeof(Ouvriers)),SEEK_SET);
                fwrite(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);
                printf("\nChamp modifie.\n");
            }
            fclose(fOuvriers);
        }
    }
}

/*
INPUT: Pointeur de l'index des ouvriers + taille max de celui-ci
PROCESS: Affichage de l'index
OUTPUT:/
*/
void AfficheIndexOuvriers(IndexOuvriers *pIOuvriers,short limite)
{
    short compteur=1;

    while(compteur<limite)
    {
        if(pIOuvriers->NumReg!=-1)
        {
            printf("\nVoici votre ouvrier %hd :",compteur);
            printf("\nSon numero de registre national: %d",pIOuvriers->NumReg);
            printf("\nSon nom: %s",pIOuvriers->NomOuvrier);
            printf("\nSon prenom: %s",pIOuvriers->PrenomOuvrier);
            printf("\nSa position: %d\n",pIOuvriers->position);
        }

        compteur++;
        pIOuvriers++;
    }
}

/*
INPUT: Pointeur vers l'index des ouvriers + taille max de celui-ci
PROCESS: Affiche un ouvrier
OUTPUT: /
*/
void AfficheUnOuvrier(IndexOuvriers *pIOuvriers,short limite)
{
    FILE *fOuvriers;
    Ouvriers mesouvriers;

    fOuvriers=fopen(NOMFICHIEROUVRIERS,"rb");

    if(fOuvriers==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier ouvrier.\n");
    }
    else
    {
        fseek(fOuvriers,(pIOuvriers->position*sizeof(Ouvriers)),SEEK_SET);
        fread(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);

        printf("\nVoici votre ouvrier:");
        printf("\nSon numero de registre national: %d", mesouvriers.NumReg);
        printf("\nSon nom: %s", mesouvriers.Nom);
        printf("\nSon prenom: %s", mesouvriers.Prenom);
        printf("\nSa date de naissance: %hd/%hd/%hd", mesouvriers.DateNaissance.jour, mesouvriers.DateNaissance.mois, mesouvriers.DateNaissance.annee);
        printf("\nSa rue: %s", mesouvriers.Rue);
        printf("\nSon code postal: %d", mesouvriers.CodePostal);
        printf("\nSa localite: %s", mesouvriers.Ville);
        printf("\nSa date d'engagement: %hd/%hd/%hd", mesouvriers.DateEngagement.jour, mesouvriers.DateEngagement.mois, mesouvriers.DateEngagement.annee);
        printf("\nSa specialite: %s\n", mesouvriers.Specialite);

        fclose(fOuvriers);
    }
}

/*
INPUT : Pointeur de la structure Index + taille maximale de celle-ci
PROCESS : Tri l'index par ordre croissant sur le nom et le prénom de l'ouvrier
OUTPUT : /
*/
void Tri_IndexOuvriers(IndexOuvriers *pIOuvriers, short limite)
{
    short i,j;
    char chaine[TAILLENOM];
    int temporaire;

    for(i=0;i<limite-1;i++)
    {
        for(j=0;j<limite-i-1 && pIOuvriers[j+1].NumReg!=-1;j++)
        {
            if(strcmp(pIOuvriers[j].NomOuvrier,pIOuvriers[j+1].NomOuvrier)>0 || (strcmp(pIOuvriers[j].NomOuvrier,pIOuvriers[j+1].NomOuvrier)==0
                && strcmp(pIOuvriers[j].PrenomOuvrier,pIOuvriers[j+1].PrenomOuvrier)> 0))
            {
                temporaire=pIOuvriers[j].NumReg;
                pIOuvriers[j].NumReg=pIOuvriers[j+1].NumReg;
                pIOuvriers[j+1].NumReg=temporaire;

                strcpy(chaine,pIOuvriers[j].NomOuvrier);
                strcpy(pIOuvriers[j].NomOuvrier,pIOuvriers[j+1].NomOuvrier);
                strcpy(pIOuvriers[j+1].NomOuvrier,chaine);

                strcpy(chaine,pIOuvriers[j].PrenomOuvrier);
                strcpy(pIOuvriers[j].PrenomOuvrier,pIOuvriers[j+1].PrenomOuvrier);
                strcpy(pIOuvriers[j+1].PrenomOuvrier,chaine);

                temporaire=pIOuvriers[j].position;
                pIOuvriers[j].position=pIOuvriers[j+1].position;
                pIOuvriers[j+1].position=temporaire;
            }
        }
    }
}

/*
INPUT : Pointeur de l'index des ouvriers + taille max de celui-ci
PROCESS : Initialisation de l'index des ouvriers en mettant leur identifiant à -1 et leur position dans le fichier
OUTPUT : /
*/
void InitIndexOuvriers(IndexOuvriers *pIOuvriers, short limite)
{
    short compteur = 0;

    while (compteur < limite)
    {
        pIOuvriers->NumReg = -1;
        strcpy(pIOuvriers->NomOuvrier, "VIDE");
        pIOuvriers->position = compteur;
        compteur++;
        pIOuvriers++;
    }
}

/*
INPUT : /
PROCESS : Initialisation du fichier contenant les ouvriers en mettant les différents champs à -1
OUTPUT : /
*/
void BidonnageFichierOuvriers()
{
    FILE *fOuvriers;
    Ouvriers mesouvriers;
    short compteur = 0;

    fOuvriers=fopen(NOMFICHIEROUVRIERS,"ab");

    if(fOuvriers==NULL)
    {
        printf("\nImpossible d'ouvrir le fichier ouvriers.\n");
    }
    else
    {
        memset(&mesouvriers,-1,sizeof(Ouvriers));

        while(compteur<TAILLEFICHIEROUVRIERS)
        {
            fwrite(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);
            compteur++;
        }
        fclose(fOuvriers);
    }
}

/*
INPUT: Pointeur vers l'index des ouvriers + taille maximale de celle-ci
PROCESS: Met à jour l'index des ouvriers avec les différentes valeurs du fichier ouvriers
OUTPUT:/
*/
void MiseAJourIndexOuvriers(IndexOuvriers *pIOuvriers,short limite)
{
    short i=0;
    FILE *fOuvriers;
    Ouvriers mesouvriers;

    fOuvriers=fopen(NOMFICHIEROUVRIERS, "rb");

    if (fOuvriers==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier ouvriers.\n");
    }
    else
    {
        fread(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);

        for (i=0;i<limite;i++,pIOuvriers++)
        {
            if (mesouvriers.NumReg != -1)
            {
                pIOuvriers->NumReg = mesouvriers.NumReg;
                strcpy(pIOuvriers->NomOuvrier, mesouvriers.Nom);
                strcpy(pIOuvriers->PrenomOuvrier, mesouvriers.Prenom);
                pIOuvriers->position=i;
            }

            fread(&mesouvriers,sizeof(Ouvriers),1,fOuvriers);
        }

        fclose(fOuvriers);
    }
}

/*
INPUT : Pointeur du numéro de registre national entré par l'utilisateur, pointeur vers l'index ouvrier + taille max de celui-ci
PROCESS : Cherche les numéros de registres nationaux des ouvriers pour voir si celui entré par l'utilisateur n'existe pas déjà
OUTPUT : Position à laquelle le numéro de registre national a été trouvé sinon -1
*/
short VerifNumReg(int NumReg,IndexOuvriers *pIOuvriers,short limite)
{
    int offset=-1,compteur=0;

    while(compteur<limite && offset==-1)
    {
        if(pIOuvriers->NumReg==NumReg)
        {
            offset=pIOuvriers->position;
        }
        else
        {
            compteur++;
            pIOuvriers++;
        }
    }

    return(offset);
}

/*
INPUT : Pointeur du nom de l'ouvrier à rechercher, pointeur vers l'index ouvriers + taille max de celui-ci
PROCESS: Parcours de l'index des ouvriers pour rechercher l'ouvrier
OUTPUT: Position à laquelle l'ouvrier à été trouvé sinon -1
*/
short RechercheOuvrier(char *pNom,IndexOuvriers *pIOuvriers,short limite)
{
    short offset=-1,compteur=0;

    while(compteur<limite && offset==-1)
    {
        if(strcmp(pIOuvriers->NomOuvrier,pNom)==0)
        {
            offset=pIOuvriers->position;
        }
        else
        {
            compteur++;
            pIOuvriers++;
        }
    }

    return(offset);
}

/*
INPUT : /
PROCESS : Menu proposé à l'utilisateur dans la modification
OUTPUT : Choix de l'utilisateur dans le menu
*/
short MenuModif()
{
    short choix=0;

    printf("\nQue souhaitez-vous modifier?");
    printf("\n1. Numero de registre national.");
    printf("\n2. Nom.");
    printf("\n3. Prenom.");
    printf("\n4. Rue.");
    printf("\n5. Code Postal.");
    printf("\n6. Localite.");
    printf("\n7. Specialite.");
    printf("\n8. Date de naissance.");
    printf("\n9. Date d'engagement.");
    printf("\n10. Arret de modifications.");
    printf("\nVotre choix:\n");
    fflush(stdin);
    scanf("%hd",&choix);

    return(choix);
}

/*
INPUT : Pointeur de l'index des chantiers, pointeur de l'index des ouvriers, taille maximale de l'index chantier
PROCESS : Ajout d'un chantier dans l'index et dans le fichier chantiers
OUTPUT : /
*/
void AjoutChantier(IndexChantier *pIChantier,IndexOuvriers *pIOuvriers,short limite)
{
    FILE *fChantier;
    short i=0;
    short saisie=0;
    short offset=-1;
    Chantier meschantiers;
    long NumeroChantier=0;
    IndexChantier *pTemporaire=pIChantier;

    while(i<TAILLEFICHIERCHANTIERS && saisie==0)
    {
        if(i==TAILLEFICHIERCHANTIERS)
        {
            printf("\nEspace libre non trouve.\n");
        }
        else
        {
            if(pIChantier->NumChantier==-1)
            {
                fChantier=fopen(NOMFICHIERCHANTIER,"r+b");

                if(fChantier==(FILE *)NULL)
                {
                    printf("\nImpossible d'ouvrir le fichier chantiers.\n");
                }
                else
                {
                    printf("\nEncodage d'un nouveau chantier:\n");

                    while(offset==-1)
                    {
                        printf("\nEntrez son numero:\n");
                        fflush(stdin);
                        scanf("%ld",&NumeroChantier);

                        offset=VerifNumChantier(NumeroChantier,pTemporaire,TAILLEFICHIERCHANTIERS);

                        if(offset!=-1)
                        {
                            printf("\nLe numero de chantier existe deja!\n");
                            offset=-1;
                        }
                        else
                        {
                            offset=0;
                        }
                    }

                    pIChantier->NumChantier=NumeroChantier;
                    printf("\nEntrez son nom:\n");
                    LireChaine(pIChantier->NomChantier,TAILLENOM);

                    do
                    {
                        printf("\nEntrez son montant:\n");
                        fflush(stdin);
                        scanf("%f",&pIChantier->Montant);
                    }
                    while(pIChantier->Montant<=0);

                    strcpy(meschantiers.NomChantier,pIChantier->NomChantier);
                    meschantiers.NumChantier=pIChantier->NumChantier;
                    meschantiers.Montant=pIChantier->Montant;

                    printf("\nEntrez sa rue\n");
                    LireRue(meschantiers.Rue,TAILLERUE);

                    do
                    {
                        printf("\nEntrez son code postal:\n");
                        fflush(stdin);
                        scanf("%d",(&meschantiers.CodePostal));
                    }
                    while(meschantiers.CodePostal<1000 || meschantiers.CodePostal>9999);

                    printf("\nEntrez sa localite:\n");
                    LireChaine(meschantiers.Ville,TAILLEVILLE);
                    printf("\nEntrez son maitre d'ouvrage:\n");
                    LireChaine(meschantiers.MaitreOuvrage,TAILLEFICHIEROUVRIERS);

                    do
                    {
                        printf("\nEntrez sa duree (maximum : 365 jours):\n");
                        fflush(stdin);
                        scanf("%d",&meschantiers.Duree);
                    }
                    while(meschantiers.Duree<=0 || meschantiers.Duree>365);

                    printf("\nEntrez son gerant:\n");
                    LireGerant(meschantiers.Gerant,TAILLEGERANT);

                    fseek(fChantier,(pIChantier->position*((int)sizeof(Chantier))),SEEK_SET);
                    fwrite(&meschantiers,sizeof(Chantier),1,fChantier);
                    fclose(fChantier);
                    printf("\nChantier ajoute au fichier!\n");
                    saisie=1;
                }
            }
            else
            {
                i++;
                pIChantier++;
            }
        }
    }
}

/*
INPUT: Pointeur de l'index chantier + taille max de celui-ci
PROCESS: Affiche l'index des chantiers
OUTPUT:/
*/
void AfficheIndexChantiers(IndexChantier *pIChantier,short limite)
{
    short compteur=1;

    while(compteur<limite && pIChantier->NumChantier!=-1)
    {
        printf("\nVoici votre chantier %hd :",compteur);
        printf("\nSon numero: %ld",pIChantier->NumChantier);
        printf("\nSon nom: %s",pIChantier->NomChantier);
        printf("\nSon montant: %.3f",pIChantier->Montant);
        printf("\nSa position: %d\n",pIChantier->position);
        compteur++;
        pIChantier++;
    }
}

/*
INPUT : Pointeur de la structure Index + taille maximale de celle-ci
PROCESS : Tri l'index par ordre croissant sur le nom et le prénom de l'ouvrier
OUTPUT : /
*/
void Tri_IndexChantier(IndexChantier *pIChantier, short limite)
{
    short i,j;
    char chaine[TAILLENOM];
    int temporaire;
    float MontantTmp;

    for(i=0;i<limite-1;i++)
    {
        for(j=0;j<limite-i-1 && pIChantier[j+1].NumChantier!=-1;j++)
        {
            if(pIChantier[j].Montant<pIChantier[j+1].Montant)
            {
                temporaire=pIChantier[j].NumChantier;
                pIChantier[j].NumChantier=pIChantier[j+1].NumChantier;
                pIChantier[j+1].NumChantier=temporaire;

                strcpy(chaine,pIChantier[j].NomChantier);
                strcpy(pIChantier[j].NomChantier,pIChantier[j+1].NomChantier);
                strcpy(pIChantier[j+1].NomChantier,chaine);

                MontantTmp=pIChantier[j].Montant;
                pIChantier[j].Montant=pIChantier[j+1].Montant;
                pIChantier[j+1].Montant=MontantTmp;

                temporaire=pIChantier[j].position;
                pIChantier[j].position=pIChantier[j+1].position;
                pIChantier[j+1].position=temporaire;
            }
        }
    }
}

/*
INPUT : Pointeur de l'index des chantiers + taille max de celui-ci
PROCESS : Initialisation de l'index des chantiers en mettant leur identifiant à -1, leur nom de chantier à VIDE
et leur position dans le fichier
OUTPUT : /
*/
void InitIndexChantier(IndexChantier *pIChantier,short limite)
{
    short compteur=0;

    while (compteur<limite)
    {
        pIChantier->NumChantier=-1;
        strcpy(pIChantier->NomChantier, "VIDE");
        pIChantier->position=compteur;
        compteur++;
        pIChantier++;
    }
}

/*
INPUT : /
PROCESS : Initialisation du fichier contenant les chantiers en mettant les champs à -1
OUTPUT : /
*/
void BidonnageFichierChantier()
{
    FILE *fChantier;
    Chantier meschantiers;
    short compteur = 0;

    fChantier=fopen(NOMFICHIERCHANTIER,"ab");

    if(fChantier==NULL)
    {
        printf("\nImpossible d'ouvrir le fichier chantiers.\n");
    }
    else
    {
        memset(&meschantiers,-1,sizeof(Chantier));

        while(compteur<TAILLEFICHIERCHANTIERS)
        {
            fwrite(&meschantiers,sizeof(Chantier),1,fChantier);
            compteur++;
        }
        fclose(fChantier);
    }
}

/*
INPUT: Pointeur vers l'index des chantiers + taille max de celui-ci
PROCESS: Met à jour l'index des chantiers avec les différentes valeurs du fichier chantiers
OUTPUT:/
*/
void MiseAJourIndexChantier(IndexChantier *pIChantier,short limite)
{
    short i=0;
    FILE *fChantier;
    Chantier meschantiers;

    fChantier=fopen(NOMFICHIERCHANTIER,"rb");

    if (fChantier==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier chantiers.\n");
    }
    else
    {
        fread(&meschantiers,sizeof(Chantier),1,fChantier);

        for (i=0;i<limite;i++,pIChantier++)
        {
            if (meschantiers.NumChantier!=-1)
            {
                strcpy(pIChantier->NomChantier,meschantiers.NomChantier);
                pIChantier->NumChantier=meschantiers.NumChantier;
                pIChantier->Montant=meschantiers.Montant;
                pIChantier->position=i;
            }

            fread(&meschantiers,sizeof(Chantier),1,fChantier);
        }

        fclose(fChantier);
    }
}

/*
INPUT : Pointeur du numéro de chantier entré par l'utilisateur, pointeur vers l'index chantier + taille max de celui-ci
PROCESS : Cherche les numéros des chantiers pour voir si celui entré par l'utilisateur n'existe pas déjà
OUTPUT : Position à laquelle le numéro de chantier a été trouvé sinon -1
*/
short VerifNumChantier(int NumChantier,IndexChantier *pIChantier,short limite)
{
    int offset=-1,compteur=0;

    while(compteur<limite && offset==-1)
    {
        if(pIChantier->NumChantier==NumChantier)
        {
            offset=pIChantier->position;
        }
        else
        {
            compteur++;
            pIChantier++;
        }
    }

    return(offset);
}

/*
INPUT : Pointeurs vers les indexs chantier et ouvrier
PROCESS : Ajout d'un horaire pour un chantier et un ouvrier donnés
OUTPUT : /
*/
void AjoutEstOccupe(IndexChantier *pIChantier,IndexOuvriers *pIOuvrier)
{
    FILE *fEstOccupe;
    EstOccupe enregistrement;
    int numChantier=-1,numReg=-1,numEstOccupe=-1;
    char chaine[TAILLEHEURE];

    fEstOccupe=fopen(NOMFICHIERESTOCCUPE,"ab");

    if(fEstOccupe==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier est occupe.\n");
    }
    else
    {
        printf("\nEncodage d'un horaire :\n");

        while(numEstOccupe==-1)
        {
            numReg=-1;
            numChantier=-1;

            while(numReg==-1)
            {
                printf("\nEntrez le numero de registre national:\n");
                fflush(stdin);
                scanf("%d",&enregistrement.NumReg);

                numReg=VerifNumReg(enregistrement.NumReg,pIOuvrier,TAILLEFICHIEROUVRIERS);

                if(numReg==-1)
                {
                    printf("\nLe numero n'existe pas!\n");
                }
            }

            while(numChantier==-1)
            {
                printf("\nEntrez le numero de chantier:\n");
                fflush(stdin);
                scanf("%ld",&enregistrement.NumChantier);

                numChantier=VerifNumChantier(enregistrement.NumChantier,pIChantier,TAILLEFICHIERCHANTIERS);

                if(numChantier==-1)
                {
                    printf("\nLe numero n'existe pas!\n");
                }
            }

            printf("\nEntrez votre date:\n");
            SaisieDate(&enregistrement.Date);

            numEstOccupe=VerifEstOccupe(enregistrement.NumReg,enregistrement.NumChantier,enregistrement.Date);

            if(numEstOccupe!=-1)
            {
                printf("\nCombinaison existante.\n");
                numEstOccupe=-1;
            }
            else
            {
                numEstOccupe=0;
            }
        }

        printf("\nEntrez les heures (HH:MM:SS):\n");
        SaisieHeure(chaine,TAILLEHEURE);
        strcpy(enregistrement.Heure,chaine);

        fwrite(&enregistrement,sizeof(EstOccupe),1,fEstOccupe);
    }

    fclose(fEstOccupe);
}

/*
INPUT : /
PROCESS : Affichage du fichier contenant les horaires par ouvrier et par chantier
OUTPUT : /
*/
void AfficheEstOccupe()
{
    FILE *fp;
    EstOccupe enregistrements;
    short compteur=1;

    fp=fopen(NOMFICHIERESTOCCUPE,"rb");

    if(fp==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier est occupe.\n");
    }
    else
    {
        fread(&enregistrements,sizeof(EstOccupe),1,fp);

        while(!feof(fp))
        {
            printf("\nVoici votre enregistrement %hd :",compteur);
            printf("\nSon numero de registre national: %d",enregistrements.NumReg);
            printf("\nSon numero de chantier: %ld",enregistrements.NumChantier);
            printf("\nSon heure: %s",enregistrements.Heure);
            printf("\nSa date: %hd/%hd/%hd\n",enregistrements.Date.jour,enregistrements.Date.mois,enregistrements.Date.annee);
            fread(&enregistrements,sizeof(EstOccupe),1,fp);
            compteur++;
        }

        fclose(fp);
    }
}

/*
INPUT : Numéros de registre national, de chantier et date encodés par l'utilisateur
PROCESS: Vérifie si la combinaison existe ou non
OUTPUT: Position à laquelle la combinaison est trouvée sinon -1
*/
short VerifEstOccupe(long NumRegNat,long NumChantier,Date pdate)
{
    FILE *fEstOccupe;
    EstOccupe enregistrement;
    int offset=-1;

    fEstOccupe=fopen(NOMFICHIERESTOCCUPE,"rb");

    if(fEstOccupe==(FILE *)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier est occupe.\n");
    }
    else
    {
        fread(&enregistrement,sizeof(EstOccupe),1,fEstOccupe);

        while(!feof(fEstOccupe) && offset==-1)
        {
            if(enregistrement.NumReg==NumRegNat && enregistrement.NumChantier==NumChantier && enregistrement.Date.jour==pdate.jour && enregistrement.Date.annee==pdate.annee && enregistrement.Date.annee==pdate.annee)
            {
                offset=1;
            }
            else
            {
                fread(&enregistrement,sizeof(EstOccupe),1,fEstOccupe);
            }
        }

        fclose(fEstOccupe);
    }

    return(offset);
}

/*
INPUT: Numéro de registre national encodé par l'utilisateur
PROCESS: Vérifie que le numéro de registre national existe dans le fichier EstOccupe
OUTPUT: Position à laquelle l'enregistrement est trouve sinon -1
*/
short RechercheEstOccupe(int pNumReg)
{
    FILE *fEstOccupe;
    EstOccupe meshoraires;
    short offset=-1;

    fEstOccupe=fopen(NOMFICHIERESTOCCUPE, "rb");

    if (fEstOccupe==(FILE*)NULL)
    {
        printf("\nImpossible d'ouvrir le fichier est occupe.\n");
    }
    else
    {
        fread(&meshoraires, sizeof(EstOccupe), 1, fEstOccupe);

        while (!feof(fEstOccupe) && offset==-1)
        {
            if (meshoraires.NumReg==pNumReg)
            {
                offset = 1;
            }
            else
            {
                fread(&meshoraires, sizeof(EstOccupe), 1, fEstOccupe);
            }
        }

        fclose(fEstOccupe);
    }

    return(offset);
}

/*
INPUT : Pointeur de la chaîne de caractères + taille max de celle-ci
PROCESS : Saisi d'une chaîne de caractères par l'utilisateur + mises en majuscules des bonnes lettres
OUTPUT : /
*/
void LireChaine(char *pSaisie,short limite)
{
    short i=0;
    short chainevalide=0;
    char *pTmp=pSaisie;

    while(chainevalide==0)
    {
        pSaisie=pTmp;

        fflush(stdin);
        (*pSaisie)=getchar();

        while(i<(limite-1) && (*pSaisie)!='\n')
        {
            pSaisie++;
            i++;
            (*pSaisie)=getchar();
        }

        (*pSaisie)='\0';
        pSaisie=pTmp;
        chainevalide=1;

        while((*pSaisie)!='\0' && chainevalide==1)
        {
            if(((*pSaisie)<'A' || (*pSaisie)>'Z') && ((*pSaisie)<'a' || (*pSaisie)>'z') && (*pSaisie)!=' ' && (*pSaisie)!='-')
            {
                chainevalide=0;
                printf("\nNous avons trouve un caractere non accepte!");
                printf("\nRecommencez la saisie :\n");
            }
            else
            {
                pSaisie++;
            }
        }
    }

    if(chainevalide!=0)
    {
        pSaisie=pTmp;

        (*pSaisie)=toupper(*pSaisie);

        pSaisie++;

        while((*pSaisie)!='\0')
        {
            if((*pSaisie)==' ' || (*pSaisie)=='-')
            {
                (*(pSaisie+1))=toupper((*(pSaisie+1)));
                pSaisie++;
            }
            else
            {
                (*pSaisie)=tolower(*pSaisie);
            }

            pSaisie++;
        }
    }
}

/*
INPUT : Pointeur de la rue + taille maximale de celle-ci
PROCESS : Initialisation de la rue et du numéro de rue de l'utilisateur
OUTPUT :/
*/
void LireRue(char *pSaisie,short limite)
{
    short i=0;
    short chainevalide=0;
    char *pTmp=pSaisie;

    while(chainevalide==0)
    {
        pSaisie=pTmp;

        fflush(stdin);
        (*pSaisie)=getchar();

        while(i<(limite-1) && (*pSaisie)!='\n')
        {
            pSaisie++;
            i++;
            (*pSaisie)=getchar();
        }

        (*pSaisie)='\0';

        pSaisie=pTmp;
        chainevalide=1;

        while((*pSaisie)!='\0' && chainevalide==1)
        {
            if(isdigit(*pSaisie)==0 && ((*pSaisie)<'A' || (*pSaisie)>'Z') && ((*pSaisie)<'a' || (*pSaisie)>'z') && (*pSaisie)!=' ' && (*pSaisie)!='-')
            {
                chainevalide=0;
                printf("\nNous avons trouve un caractere non accepte!");
                printf("\nVeuillez recommencer la saisie :\n");
            }
            else
            {
                pSaisie++;
            }
        }
    }

    if(chainevalide!=0)
    {
        pSaisie=pTmp;
        (*pSaisie)=toupper(*pSaisie);
        pSaisie++;

        while((*pSaisie)!='\0')
        {
            if((*pSaisie)==' ' || (*pSaisie)=='-')
            {
                (*(pSaisie+1))=toupper((*(pSaisie+1)));
                pSaisie++;
            }
            else
            {
                (*pSaisie)=tolower(*pSaisie);
            }

            pSaisie++;
        }
    }
}

/*
INPUT : Pointeur de la date
PROCESS : Saisi de la date au format JJ/MM/AAAA par l'utilisateur + vérification de la validité de celle-ci
OUTPUT : /
*/
void SaisieDate(Date *pD)
{
    char Saisie[TAILLEDATE];
    char *pSaisie=&Saisie[0];
    char *token;
    short i;
    short day,month,year;
    time_t(now);
    time(&now);
    struct tm *local = localtime(&now);
    short datevalide=0;

    while(datevalide==0)
    {
        pSaisie=&Saisie[0];
        i=0;

        fflush(stdin);
        (*pSaisie)=getchar();

        while(i<(TAILLEDATE-1) && (*pSaisie)!='\n')
        {
            pSaisie++;
            i++;
            (*pSaisie)=getchar();
        }

        (*pSaisie)='\0';

        pSaisie=&Saisie[0];

        if(strlen(pSaisie)==10)
        {
            if(*(pSaisie+2)=='/' && *(pSaisie+5)=='/')
            {
                pSaisie=&Saisie[0];
                token = strtok(pSaisie,"/");
                i = 0;

                while(token!=NULL)
                {
                    if(i==0)
                    {
                        pD->jour = atoi(token);
                    }

                    if(i==1)
                    {
                       pD->mois = atoi(token);
                    }
                    if(i==2)
                    {
                       pD->annee = atoi(token);
                    }

                    token=strtok(NULL,"/");
                    i++;
                }
            }
            else
            {
                if(*(pSaisie+2) != '/')
                {
                    printf("\nFormat du champ incorrect...Le caractere '%c' doit etre un '/'", *(pSaisie+2));
                    printf("\nRecommencez la saisi :\n");
                    datevalide=0;
                }
                else
                {
                    printf("\nFormat du champ incorrect...Le caractere '%c' doit etre un '/'", *(pSaisie+5));
                    printf("\nRecommencez la saisi :\n");
                    datevalide=0;
                }
            }
        }
        else
        {
            printf("\nLa taille de la date est trop petite (taille=10).");
            printf("\nRecommencez la saisi :\n");
            datevalide=0;
        }

        day = local->tm_mday;
        month = local->tm_mon + 1;
        year = local->tm_year + 1900;

        if (pD->annee>=1957 && pD->annee<=year)
        {
            switch (pD->mois)
            {
                case 4: case 6: case 9: case 11:
                    {
                        if ((pD->jour>=1)&&(pD->jour<=30))
                        {
                            datevalide=1;
                        }
                        else
                        {
                            printf("\nLe jour que vous avez entre est invalide (compris entre 1 et 31).\n");
                            printf("\nRecommencez la saisi :\n");
                            datevalide=0;
                        }
                    }
                    break;

                case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                    {
                        if ((pD->jour>=1)&&(pD->jour<=31))
                        {
                           datevalide=1;
                        }
                        else
                        {
                           printf("\nLe jour que vous avez entre est invalide (compris entre 1 et 31).\n");
                           printf("\nRecommencez la saisi :\n");
                           datevalide=0;
                        }
                    }
                    break;

                case 2:
                    {
                        if (pD->annee%4==0)
                        {
                            if(pD->annee%400==0)
                            {
                                if((pD->jour>=1)&&(pD->jour<=29))
                                {
                                  datevalide=1;
                                }
                                else
                                {
                                    printf("\nLe jour que vous avez entre est invalide (compris entre 1 et 29).\n");
                                    printf("\nRecommencez la saisi :\n");
                                    datevalide=0;
                                }
                            }
                            else
                            {
                                if((pD->jour>=1)&&(pD->jour<=28))
                                {
                                    datevalide=1;
                                }
                                else
                                {
                                    printf("\nLe jour que vous avez entre est invalide (compris entre 1 et 28).\n");
                                    printf("\nRecommencez la saisi :\n");
                                    datevalide=0;
                                }
                            }
                        }
                        else
                        {
                            if((pD->jour>=1)&&(pD->jour<=28))
                            {
                               datevalide=1;
                            }
                            else
                            {
                                printf("\nLe jour que vous avez entre est invalide (compris entre 1 et 28).\n");
                                printf("\nRecommencez la saisi :\n");
                                datevalide=0;
                            }
                        }
                    }
                    break;

                    default:
                        {
                            printf("\nLe mois que vous avez entre est invalide (compris entre 1 et 12).\n");
                            printf("\nRecommencez la saisi :\n");
                            datevalide=0;
                        }
                        break;
                }
            }
            else
            {
               printf("\nL'annee que vous avez entree est invalide (comprise entre 1957 et 2023).");
               printf("\nRecommencez la saisi :\n");
               datevalide=0;
            }

           if(datevalide!=0)
           {
                if(pD->annee==year)
                {
                    if(pD->mois>month)
                    {
                        printf("\nDate entree superieure a celle du jour : %hd/%hd/%hd.",day,month,year);
                        printf("\nRecommencez la saisi :\n");
                        datevalide=0;
                    }
                    else
                    {
                        if(pD->mois==month)
                        {
                            if(pD->jour>day)
                            {
                                printf("\nDate entree superieur a celle du jour : %hd/%hd/%hd.",day,month,year);
                                printf("\nRecommencez la saisi :\n");
                                datevalide=0;
                            }
                            else
                            {
                                datevalide=1;
                            }
                        }
                        else
                        {
                            datevalide=1;
                        }
                    }
                }
           }

    }
}

/*
INPUT : Pointeur pour la spécialité de l'ouvrier
PROCESS : Initialisation de la spécialité par l'utilisateur
OUTPUT : /
*/
void SaisieSpecialite(char *pSaisie)
{
    short choix=0;

    printf("\n1. Coffreur.");
    printf("\n2. Couvreur.");
    printf("\n3. Ferrailleur.");
    printf("\n4. Grutier.");
    printf("\n5. Macon.");
    printf("\n6. Manoeuvres.");
    printf("\n7. Menusier.");
    printf("\nVotre choix :\n");
    fflush(stdin);
    scanf("%hd",&choix);

    switch(choix)
    {
        case 1:
            {
                strcpy(pSaisie,"Coffreur");
            }
            break;

        case 2:
            {
                strcpy(pSaisie,"Couvreur");
            }
            break;

        case 3:
            {
                strcpy(pSaisie,"Ferrailleur");
            }
            break;

        case 4:
            {
                strcpy(pSaisie,"Grutier");
            }
            break;

        case 5:
            {
                strcpy(pSaisie,"Macon");
            }
            break;

        case 6:
            {
                strcpy(pSaisie,"Manoeuvre");
            }
            break;

        case 7:
            {
                strcpy(pSaisie,"Menusier");
            }
            break;

        default:
            {
                printf("\nChoix pas valide, recommencer!\n");
            }
            break;
    }
}

/*
INPUT : Pointeur de la chaîne de caractères du gérant + taille max de celle-ci
PROCESS : Saisi d'une chaîne des initiales du gérant par l'utilisateur + mises en majuscules de celles-ci
OUTPUT : /
*/
void LireGerant(char *pSaisie,short limite)
{
    short i=0;
    short chainevalide=0;
    char *pTmp=pSaisie;

    while(chainevalide==0)
    {
        pSaisie=pTmp;
        fflush(stdin);
        (*pSaisie)=getchar();

        while(i<(limite-1) && (*pSaisie)!='\n')
        {
            pSaisie++;
            i++;
            (*pSaisie)=getchar();
        }

        (*pSaisie)='\0';
        pSaisie=pTmp;
        chainevalide=1;

        while((*pSaisie)!='\0' && chainevalide==1)
        {
            if(((*pSaisie)<'A' || (*pSaisie)>'Z') && ((*pSaisie)<'a' || (*pSaisie)>'z') && (*pSaisie)!=' ' && (*pSaisie)!='-')
            {
                chainevalide=0;
                printf("\nNous avons trouve un caractere non accepte!");
                printf("\nVeuillez recommencer la saisie :\n");
            }
            else
            {
                pSaisie++;
            }
        }
    }

    if(chainevalide!=0)
    {
        pSaisie=pTmp;

        while((*pSaisie)!='\0')
        {
            (*pSaisie)=toupper(*pSaisie);
            pSaisie++;
        }
    }
}

/*
INPUT:Pointeur de l'heure saisie par l'utilisateur + taille max de celle-ci
PROCESS:Initialisation de l'heure par l'utilisateur + vérification de sa validité
OUTPUT:/
*/
void SaisieHeure(char *pHeure, short limite)
{
    char *token;
    short i;
    short heure, minutes, secondes;
    short heurevalide = 0;
    char *pTemporaire = pHeure;

    while (heurevalide == 0)
    {
        pHeure = pTemporaire;
        i = 0;

        fflush(stdin);
        (*pHeure) = getchar();

        while (i < (limite - 1) && (*pHeure) != '\n')
        {
            pHeure++;
            i++;
            (*pHeure) = getchar();
        }

        (*pHeure) = '\0';

        pHeure = pTemporaire;

        if(strlen(pHeure)==(limite - 1))
        {
            if (*(pHeure+2)==':' && *(pHeure+5)==':')
            {
                while((*pHeure)!='\0')
                {
                    if(isdigit(*pHeure)==0 && isdigit(*(pHeure + 1))==0 && isdigit(*(pHeure + 3))==0 &&
                       isdigit(*(pHeure + 4))==0 && isdigit(*(pHeure + 6))==0 && isdigit(*(pHeure + 7))==0)
                    {
                        printf("\nFormat de champ incorrect.\n");
                        printf("\nRecommencez la saisie:\n");
                        heurevalide=0;
                    }
                    else
                    {
                        token = strtok(pHeure,":");
                        i = 0;

                        while(token!=NULL)
                        {
                            if(i==0)
                            {
                                heure=atoi(token);
                            }

                            if(i==1)
                            {
                               minutes=atoi(token);
                            }
                            if(i==2)
                            {
                               secondes=atoi(token);
                            }

                            token=strtok(NULL,":");
                            i++;
                        }
                    }

                    pHeure++;
                }
            }
            else
            {
                if (*(pHeure+2)!=':')
                {
                    printf("\nFormat du champ incorrect...Le caractere '%c' doit etre un ':'", *(pHeure+2));
                    printf("\nRecommencez la saisie:\n");
                    heurevalide = 0;
                }
                else
                {
                    printf("\nFormat du champ incorrect...Le caractere '%c' doit etre un ':'", *(pHeure + 5));
                    printf("\nRecommencez la saisie:\n");
                    heurevalide = 0;
                }
            }
        }
        else
        {
            printf("\nLa taille de la date est trop petite (taille = 8).");
            printf("\nRecommencez la saisi :\n");
            heurevalide = 0;
        }

        if(heure==8)
        {
            if(minutes>0)
            {
                printf("\nLimite depassee (maximum : 08:00:00).\n");
                printf("\nRecommencez la saisie:\n");
                heurevalide=0;
            }
            else
            {
                if(secondes>0)
                {
                    printf("\nLimite depassee (maximum : 08:00:00).\n");
                    printf("\nRecommencez la saisie:\n");
                    heurevalide=0;
                }
                else
                {
                    heurevalide=1;
                }
            }
        }

        if(heure>=0 && heure<=8)
        {
            if(minutes>=0 && minutes<=59)
            {
                if(secondes>=0 && secondes<=59)
                {
                    heurevalide=1;
                }
                else
                {
                    printf("\nNombre de secondes invalide (compris entre 0 et 59).\n");
                    printf("\nRecommencez la saisie:\n");
                    heurevalide=0;
                }
            }
            else
            {
                printf("\nNombre de minutes invalide (compris entre 0 et 59).\n");
                printf("\nRecommencez la saisie:\n");
                heurevalide=0;
            }
        }
        else
        {
            printf("\nNombre d'heures invalide.\n");
            printf("\nRecommencez la saisie:\n");
            heurevalide=0;
        }

        if(heurevalide!=0)
        {
            if(heure==8)
            {
                if(minutes>0)
                {
                    printf("\nLimite depassee (maximum : 08:00:00).\n");
                    printf("\nRecommencez la saisie:\n");
                    heurevalide=0;
                }
                else
                {
                    if(secondes>0)
                    {
                        printf("\nLimite depassee (maximum : 08:00:00).\n");
                        printf("\nRecommencez la saisie:\n");
                        heurevalide=0;
                    }
                    else
                    {
                        heurevalide=1;
                    }
                }
            }
        }
    }

    pHeure=pTemporaire;
    sprintf(pHeure,"%.2d:%.2d:%.2d",heure,minutes,secondes);
}
