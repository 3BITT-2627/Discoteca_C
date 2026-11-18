/*
 * Esercizio: DISCOTECA
 * Sistema di ingresso: per ogni persona si chiede genere ('M'/'F') ed eta' (> 0).
 * Entrano solo i maggiorenni, fino alla capienza massima.
 * Per chiudere gli ingressi prima del pienone si inserisce 'X' come genere.
 * Alla fine si stampano conteggi e statistiche.
 */
#include <stdio.h>
#include <ctype.h>

#define CAPIENZA_MAX 2
#define MAGGIORE_ETA 18

int main(void)
{
    char genere;
    int eta;

    /* contatori */
    int presenti = 0;          /* persone entrate */
    int tentativi = 0;         /* persone che si sono presentate all'ingresso */
    int respinti = 0;          /* minorenni respinti */
    int maschi = 0, femmine = 0;                 /* entrati per genere */
    int respintiM = 0, respintiF = 0;            /* respinti per genere */

    /* somme per le medie */
    int sommaEtaM = 0, sommaEtaF = 0;

    float mediaM, mediaF, mediaTot;
    float percM, percF, percRespinti;

    printf("=== INGRESSO DISCOTECA (capienza %d) ===\n", CAPIENZA_MAX);
    printf("Inserire 'X' come genere per chiudere gli ingressi.\n\n");

    while (presenti < CAPIENZA_MAX)
    {
        /* --- lettura e controllo del genere --- */
        do
        {
            printf("Genere (M/F, X per chiudere): ");
            scanf(" %c", &genere);
            genere = toupper(genere);
            if (genere != 'M' && genere != 'F' && genere != 'X')
                printf("Valore non valido! Inserire M, F oppure X.\n");
        } while (genere != 'M' && genere != 'F' && genere != 'X');

        if (genere == 'X')
            break;                      /* chiusura anticipata */

        /* --- lettura e controllo dell'eta' --- */
        do
        {
            printf("Eta': ");
            scanf("%d", &eta);
            if (eta <= 0)
                printf("Eta' non valida! Deve essere maggiore di 0.\n");
        } while (eta <= 0);

        tentativi++;

        /* --- controllo maggiore eta' --- */
        if (eta < MAGGIORE_ETA)
        {
            printf(">>> INGRESSO NEGATO: solo maggiorenni.\n\n");
            respinti++;
            if (genere == 'M')
                respintiM++;
            else
                respintiF++;
        }
        else
        {
            presenti++;
            if (genere == 'M')
            {
                maschi++;
                sommaEtaM += eta;
            }
            else
            {
                femmine++;
                sommaEtaF += eta;
            }
            printf(">>> Benvenuto/a! Presenti: %d/%d (posti liberi: %d)\n\n",
                   presenti, CAPIENZA_MAX, CAPIENZA_MAX - presenti);
        }
    } // WHILE CHE CONTROLLA LA CAPIENZA MASSIMA

    if (presenti == CAPIENZA_MAX)
        printf("\n*** CAPIENZA MASSIMA RAGGIUNTA: ingressi chiusi ***\n");

    /* --- STATISTICHE --- */
    printf("\n========== STATISTICHE ==========\n");
    printf("Persone presentate all'ingresso: %d\n", tentativi);
    printf("Entrati: %d  (maschi %d, femmine %d)\n", presenti, maschi, femmine);
    printf("Respinti (minorenni): %d  (maschi %d, femmine %d)\n",
           respinti, respintiM, respintiF);

    /* medie: attenzione alla divisione per zero e al cast a float */
    if (maschi > 0)
    {
        mediaM = (float)sommaEtaM / maschi;
        printf("Eta' media maschi: %.2f\n", mediaM);
    }
    else
        printf("Eta' media maschi: nessun maschio entrato\n");

    if (femmine > 0)
    {
        mediaF = (float)sommaEtaF / femmine;
        printf("Eta' media femmine: %.2f\n", mediaF);
    }
    else
        printf("Eta' media femmine: nessuna femmina entrata\n");

    /* percentuali calcolate sugli entrati */
    if (presenti > 0)
    {
        mediaTot = (float)(sommaEtaM + sommaEtaF) / presenti;
        percM = (float)maschi * 100 / presenti;
        percF = (float)femmine * 100 / presenti;
        printf("Eta' media complessiva: %.2f\n", mediaTot);
        printf("Percentuale maschi: %.1f%%\n", percM);
        printf("Percentuale femmine: %.1f%%\n", percF);
    }

    if (tentativi > 0)
    {
        percRespinti = (float)respinti * 100 / tentativi;
        printf("Percentuale respinti: %.1f%%\n", percRespinti);
    }

    printf("Riempimento locale: %.1f%%\n", (float)presenti * 100 / CAPIENZA_MAX);

    return 0;
}