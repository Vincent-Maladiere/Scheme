
/**
 * @file read.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 15 18:31:05 2012
 * @brief Read routine for SFS.
 *
 * Read routine for SFS.
 */

#include <stdio.h>
#include <ctype.h>

#include "read.h"



void flip( uint *i ) {

    if ( *i == FALSE ) {
        *i = TRUE;
    }
    else {
        *i = FALSE;
    }
}

/*
 * @fn char* first_usefull_char(char* line)
 *
 * @brief retourne un pointeur sur le premier caractere utile dans line
 * ou NULL si line ne contient que des espaces et des commentaires
 */
char* first_usefull_char(char* line) {

    int i=0;
    if (line == NULL) {
        return NULL;
    }
    i = 0;
    /* on saute les espaces */
    while(line[i] != '\0' && isspace(line[i])) {
        i++;
    }
    /* si fin de ligne => ligne inutile */
    if(line[i] == '\0') {
        return NULL;
    }
    /* si premier caractere non espace est ';' => ligne inutile */
    if(line[i] == ';') {
        return NULL;
    }
    return line + i; /* ligne utile */
}

/**
 * @fn uint  sfs_get_sexpr( char *input, FILE *fp )
 *
 * @brief extrait la prochaine S-Expression dans le flux fp et la stocke dans input
 * (meme si elle est repartie sur plusieurs lignes)
 * @param fp (FILE *) flux d'entree (ouvert en ecriture, mode texte)
 * @param input (char *) chaine allouee de taille BIGSTRING, dans laquelle la S-Expression sera stockée
 *
 * @return S_OK si une S-Expression apparemment valide a ete trouvee
 * @return S_KO si on n'a pas trouve de S-Expression valide
 * @return S_END si fin de fichier atteinte sans avoir lu de caractere utile.
 *
 * sfs_get_sexpr commence par lire une ligne dans fp,
 * puis compte le nombre de parentheses ouvrantes et fermantes sur la ligne.
 * Les parentheses dans des chaines et les caracteres Scheme #\( et #\)
 * ne sont pas comptes.
 *
 * Si le compte devient zéro et que 
 *        - la ligne est fini, la fonction retourne S_OK
 * 				- la ligne n'est pas fini la fonction retourne S_KO
 *
 * S'il y a plus de parentheses fermantes qu'ouvrantes,
 * la fonction retourne S_KO.
 * Les commentaires et espaces qui figurent a la fin de chaque ligne
 * sont remplacés par un espace.
 * Les espaces qui figurent a la fin de la S-Expression (y compris '\n')
 * sont supprimés.
 *
 * Attention : cette fonction refuse les S-Expression multiple sur une seule ligne. Ainsi :
 *    a b c
 *    (qqchose) (autrechose)
 *    (qqchose) 78
 * seront considereees comme des erreurs
 * et la fonction retournera S_KO
 *
 * @pre fp doit etre prealablement ouvert en lecture
 * @pre input doit etre prealablement alloue en memoire, de taille BIGSTRING
 */

typedef enum {
    NOTHING,        /* rien n'a ete trouve encore.. */
    STRING_ATOME,   /* la premiere trouvee dans la ligne semble etre un atome */
    BASIC_ATOME,    /* la premiere trouvee dans la ligne semble etre d'une chaine */
    S_EXPR_PARENTHESIS, /* la premiere trouvee dans la ligne semble etre une expression parenthesee */
    FINISHED        /* on a trouve une S-Expr bien formee */
} EXPRESSION_TYPE_T;

uint  sfs_get_sexpr( char *input, FILE *fp ) {
    int       parlevel = 0;
    uint      in_string = FALSE;
    uint      s = 0;
    char      k[BIGSTRING];
    char      *ret = NULL;
    char      *chunk = NULL;
    uint      i = 0;
    string    sfs_prompt;

    EXPRESSION_TYPE_T typeOfExpressionFound = NOTHING;

    parlevel = 0;
    memset( input, '\0', BIGSTRING );

    do {
        ret = NULL;
        chunk=k;
        memset( chunk, '\0', BIGSTRING );

        /* si en mode interactif*/
        if ( stdin == fp ) {
            uint nspaces = 2*parlevel;

            init_string( sfs_prompt );

            /* le prompt indique le niveau de parenthese
               et decale la prochaine entrée en fonction
               de ce niveau (un peu à la python)*/
            sprintf( sfs_prompt, "SFS:%u > ", parlevel );

            for ( i= 0; i< nspaces; i++ ) {
                sfs_prompt[strlen(sfs_prompt)] = ' ';
            }

            /* si sur plusieurs lignes, le \n équivaut à un espace*/
            if (nspaces>0) {
                input[strlen(input)+1] = '\0';
                input[strlen(input)] = ' ';
            }

            /*saisie de la prochaine ligne à ajouter dans l'input*/
            printf("%s",sfs_prompt);
            ret = fgets( chunk, BIGSTRING, fp );
            if (ret && chunk[strlen(chunk)-1] == '\n') chunk[strlen(chunk)-1] = '\0';

        }
        /*si en mode fichier*/
        else {
            ret = fgets( chunk, BIGSTRING, fp );

            if ( NULL == ret ) {
                /* fin de fichier...*/
                if ( parlevel != 0 ) {
                    WARNING_MSG( "Parse error: missing ')'" );
                    return S_KO;
                }
                return S_END;
            }

            if (strlen(chunk) == BIGSTRING-1
                    && chunk[BIGSTRING-1] != '\n'
                    && !feof(fp)) {
                WARNING_MSG( "Too long line for this interpreter!" );
                return S_KO;
            }
        }

        /* si la ligne est inutile 
        	=> on va directement à la prochaine iteration */
        if (first_usefull_char(chunk) == NULL) {
            continue;
        }


        s = strlen( chunk );

        if ( s > 0 ) {
            if (strlen(input) + s > BIGSTRING-1 ) {
                WARNING_MSG( "Too long a S-expression for this interpreter!" );
                return S_KO;
            }

            for ( i = 0; i< strlen(chunk); i++ ) {
                /* si la fin de la ligne chunk est inutile,
                   on ajoute un espace dans input et on sort de la boucle*/
                if ( in_string == FALSE && first_usefull_char(chunk + i) == NULL ) {
                    chunk[i]='\0';
                    input[strlen(input)] = ' ';
                    break;
                }


                switch(chunk[i]) {
                case '(':
                    if (in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel++;
                        typeOfExpressionFound = S_EXPR_PARENTHESIS;
                    }
                    break;
                case ')':
                    if ( in_string == FALSE
                            && ! ( i>1 && chunk[i-1] == '\\' && chunk[i-2] == '#' ) ) {
                        parlevel--;
                        if (parlevel == 0 ) {
                            typeOfExpressionFound = FINISHED;
                        }
                        if ( parlevel < 0 ) {
                            WARNING_MSG( "Parse error : cannot start with ')'" );
                            return S_KO;
                        }
                    }
                    break;
                case '"':
                    if ( i<2 || chunk[i-1] != '\\' ) {
                        if ( in_string == FALSE ) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                WARNING_MSG("Parse error: invalid string after atom : '%s'", chunk+i);
                                return S_KO;
                            }
                            in_string = TRUE;
                            if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                                typeOfExpressionFound = STRING_ATOME;
                            }
                        }
                        else {
                            in_string = FALSE;
                            if(typeOfExpressionFound == STRING_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        }
                    }
                    break;
                default:
                    if(in_string == FALSE) {
                        if(isspace(chunk[i])) {
                            if(typeOfExpressionFound == BASIC_ATOME) {
                                typeOfExpressionFound = FINISHED;
                            }
                        } else if(typeOfExpressionFound != S_EXPR_PARENTHESIS) {
                            typeOfExpressionFound = BASIC_ATOME;
                        }
                    }
                    break;
                }


                if(typeOfExpressionFound == FINISHED) {
                    char *first_useful = first_usefull_char(chunk + i + 1);
                    if( first_useful != NULL) {
                        if(*first_useful == ')' ) {
                            WARNING_MSG( "Parse error: too many closing parenthesis')'" );
                        }
                        else {
                            WARNING_MSG("Parse error: invalid trailing chars after S-Expr : '%s'", chunk+i);
                        }
                        return S_KO;
                    }
                }

                /* recopie char par char*/
                input[strlen(input)] = chunk[i];
            }
            if(in_string == TRUE) {
                WARNING_MSG( "Parse error: non terminated string on line %s", chunk );
                return S_KO;
            }
        }


        if ( parlevel > 0 && fp != stdin ) {
            if ( feof( fp ) ) {
                WARNING_MSG( "Parse error: missing ')'" );
                return S_KO;
            }

            if (input[strlen(input)-1] == '\n') input[strlen(input)-1] = ' ';
        }
    } while ( parlevel > 0 );

    /* Suppression des espaces restant a la fin de l'expression, notamment le dernier '\n' */
    while (isspace(input[strlen(input)-1])) input[strlen(input)-1] = '\0';

    return S_OK;
}

object sfs_read( char *input, uint *here ) {
    while(isspace(input[*here])){
        (*here)++;
    }
    if ( input[*here] == '(' ) {
        if ( input[(*here)+1] == ')' ) {
            *here += 2;
            return nil;
        }
        else {
            (*here)++;
            return sfs_read_pair( input, here );
        }
    }
    else {
        return sfs_read_atom( input, here );
    }
}


object sfs_read_atom( char *input, uint *here ) {
    
    object atom = nil;
    char caractere[256] = "";
    int i = 0;
    
    if((isdigit(input[*here]))||(input[*here] == '+')||(input[*here] == '-')){ /*boucle digit*/
        caractere[i] = input[*here];
        i++;
        (*here)++;
        if((((input[*here-1]=='+')&&(isblank(input[*here])))||((input[*here-1])&&(isblank(input[*here]))))){
            atom = make_object(SFS_SYMBOL);
            strcpy(atom->this.symbol,caractere);
        }
        
        else{
            while(isdigit(input[*here])){ /*tant que des digits sont détectés, on les intègre dans le char*/
                caractere[i] = input[*here];
                i++;
                (*here)++;
            }
            if((isblank(input[*here]))||(input[*here]==')')){ /*si la fin du while est causée par un espace, c'est un nombre !*/
                atom = make_object(SFS_NUMBER);
                atom->this.number.numtype = NUM_INTEGER;
                atom->this.number.this.integer = atoi(caractere);
            }
            else{
                ERROR_MSG("Entier Invalide\n");
            }
    
        }
    }
    if((input[*here]) == '"'){ /*boucle string*/
        (*here)++;
        while(isalpha(input[*here])){
            caractere[i] = input[*here];
            i++;
            (*here)++;
        }
        if(((input[*here] == '"')&&(isblank(input[(*here)+1])))||((input[*here] == '"')&&((input[*here]==')')))){
            atom = make_object(SFS_STRING);
            strcpy(atom->this.string,caractere);
            atom->this.string[i+1] = '\0'; /*toujours placé à la fin du string*/
            (*here)++;
        }
        else{
            ERROR_MSG("String Invalide\n");
        }
    }
    if(input[*here] == '#'){ /*boucle caractere*/
        (*here)++;
        if(input[*here] == '\''){
            if ((input[*here]=='n') && (input[*here+1]=='e') && (input[*here+2]=='w') && (input[*here+3]=='l') && (input[*here+4]=='i') && (input[*here+5]=='n') && (input[*here+6]=='e') && (isblank(input[*here]))) {
                atom = make_object(SFS_SYMBOL); /*Est-ce vraiment un symbol ? un string maybe ?*/
                char str1[256] = {'\n'};
                strcpy(atom->this.symbol,str1);
            }
            else if ((input[*here]=='s') && (input[*here+1]=='p') && (input[*here+2]=='a') && (input[*here+3]=='c') && (input[*here+4]=='e')&&(isblank(input[*here]))) {
                atom = make_object(SFS_SYMBOL);
                char str1[256] = {' '};
                strcpy(atom->this.symbol,str1);
            }
            else if((isalpha(input[*here]))&&((isblank(input[(*here)+1]))||(input[*here]==')'))){
                atom = make_object(SFS_CHARACTER);
                atom->this.character = input[*here];
            }
            else{
                ERROR_MSG("Caractère invalide\n");
            }
        }
        if((input[*here] == 't')||(input[*here] == 'f')){
            (*here)++;
            if(isblank(input[*here])||(input[*here]==')')){
                atom = make_object(SFS_BOOLEAN); /*True = 1 , False = 0*/
                atom->this.number.numtype = NUM_INTEGER;
                atom->this.number.this.integer = (input[*here-1] == 't') ? 1 : 0;
            }
            else{
                ERROR_MSG("Booléen Invalide\n");
            }
        }
    }
    if(isalpha(input[*here])){ /*boucle symbol*/
        caractere[i] = input[*here];
        (*here)++;
        i++;
        while(isalpha(input[*here])){
            caractere[i] = input[*here];
            (*here)++;
            i++;
        }
        if(isblank(input[*here])||(input[*here]==')')){
            atom = make_object(SFS_SYMBOL);
            strcpy(atom->this.symbol,caractere);
        }
        else{
            ERROR_MSG("Symbol Invalide\n");
        }
    }
   
    return atom;
}
        
        

        
        
object sfs_read_pair_save( char *stream, uint *i ) {

    object pair = make_object(SFS_PAIR);
    
    pair->this.pair.car = sfs_read(stream,i);
    
    if(stream[*i] == ')'){
        (*i)++;

        pair->this.pair.cdr = sfs_read(stream,i);
    }
    else{
    pair->this.pair.cdr = sfs_read_pair(stream,i);
    }
    return pair;
}

object sfs_read_pair_old( char *stream, uint *i ) {
    
    object pair = make_object(SFS_PAIR);
    
    pair->this.pair.car = sfs_read(stream,i);
    
    if(stream[*i] == ')'){
        (*i)++;
        
        pair->this.pair.cdr = nil;
    }
    else{
        pair->this.pair.cdr = sfs_read(stream,i);
    }
    return pair;
}

object sfs_read_pair( char *stream, uint *i ) {
    
    if(stream[*i] == ')'){
        (*i)++;
        
        return nil;
    }
    else {
        object car = sfs_read(stream,i);
        
       return cons( car, sfs_read_pair(stream,i) );
    }
}
