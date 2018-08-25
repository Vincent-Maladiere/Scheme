//
//  primitive.c
//  Scheme
//
//  Created by Vincent Maladiere on 16/11/16.
//  Copyright © 2016 Vincent Maladiere. All rights reserved.
//

#include "primitive.h"

char str1[256] = {'n','e','w','l','i','n','e'};
char str2[256] = {'s','p','a','c','e'};
char str3[256] = {'+','i','n','f'};
char str4[256] = {'-','i','n','f'};
char str000[256] = {'u','n','d','e','f'};

object make_primitive(void){
    list_prim = make_object(SFS_PAIR);
    list_prim->this.pair.car = NULL;
    list_prim->this.pair.cdr = make_object(SFS_PAIR);
    
    object o = make_object(SFS_PAIR);
    o = list_prim->this.pair.cdr;
    
    /* arithmétique */
    
    /* + */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str5[256] = {'+'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str5);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = plus_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* - */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str6[256] = {'-'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str6);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = moins_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* * */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str7[256] = {'*'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str7);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = multiplier_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* / */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str8[256] = {'/'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str8);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = diviser_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* % */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str9[256] = {'%'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str9);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = rest_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* = */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str10[256] = {'='};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str10);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = egal_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* < */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str11[256] = {'<'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str11);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = inf_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* > */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str12[256] = {'>'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str12);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = sup_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* boolean? */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str101[256] = {'b','o','o','l','e','a','n','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str101);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = boolean_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* string */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str102[256] = {'s','t','r','i','n','g','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str102);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = string_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* symbol */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str103[256] = {'s','y','m','b','o','l','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str103);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = symbol_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* integer */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str104[256] = {'i','n','t','e','g','e','r','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str104);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = integer_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* pair */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str105[256] = {'p','a','i','r','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str105);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = pair_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* nil */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str106[256] = {'n','u','l','l','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str106);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = null_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* char -> integer */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str301[256] = {'c','h','a','r','-','>','n','u','m','b','e','r'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str301);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = char_number_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* integer -> char */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str302[256] = {'n','u','m','b','e','r','-','>','c','h','a','r'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str302);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = number_char_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* number -> string */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str303[256] = {'n','u','m','b','e','r','-','>','s','t','r','i','n','g'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str303);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = number_string_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* string -> number */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str304[256] = {'s','t','r','i','n','g','-','>','n','u','m','b','e','r'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str304);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = string_number_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* symbol -> string */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str305[256] = {'s','y','m','b','o','l','-','>','s','t','r','i','n','g'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str305);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = symbol_string_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* string -> symbol */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str306[256] = {'s','t','r','i','n','g','-','>','s','y','m','b','o','l'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str306);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = string_symbol_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* car */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str401[256] = {'c','a','r'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str401);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = car_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* cdr */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str402[256] = {'c','d','r'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str402);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = cdr_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* list */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str403[256] = {'l','i','s','t'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str403);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = list_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* eq */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str404[256] = {'e','q','?'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str404);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = eq_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* cons */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str405[256] = {'c','o','n','s'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str405);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = cons_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    return list_prim;
}




object plus_p (object arbreAAditionner){
    int res = 0;
    int bit_infini = 1;
    while(arbreAAditionner->this.pair.car != NULL){
        int bit_erreur = 0;
        if(arbreAAditionner->this.pair.car->type == SFS_NUMBER){
            res += arbreAAditionner->this.pair.car->this.number.this.integer;
            bit_erreur = 1;
        }
        if(strcmp(str3,arbreAAditionner->this.pair.car->this.symbol) == 0){
            bit_infini = 2;
            bit_erreur = 1;
        }
        if(strcmp(str4,arbreAAditionner->this.pair.car->this.symbol) == 0){
            bit_infini *= -1;
            bit_erreur = 1;
        }
        if(bit_erreur == 0){
            ERROR_MSG("\n Il y a un non entier dans l'arbre argument");
        }
        arbreAAditionner = arbreAAditionner->this.pair.cdr;
    }
    if(bit_infini == 1){
        object resObject = make_object(SFS_NUMBER);
        resObject->this.number.this.integer = res;
        return resObject;
    }
    object resObject = make_object(SFS_INFINI);
    if(bit_infini == -2){
        char str000[256] = {'u','n','d','e','f'};
        strcpy(resObject->this.symbol,str000);
        return resObject;
    }
    if(bit_infini == 2){
        strcpy(resObject->this.symbol,str3);
    }
    if(bit_infini == -1){
        strcpy(resObject->this.symbol,str4);
    }
    return resObject;
}

object moins_p (object arbreASoustraire){
    int res = (arbreASoustraire->this.pair.car->type == SFS_INFINI) ? 0 : arbreASoustraire->this.pair.car->this.number.this.integer;
    if(arbreASoustraire->this.pair.car->type == SFS_NUMBER){
        arbreASoustraire = arbreASoustraire->this.pair.cdr;
    }
    int bit_infini = 1;
    while(arbreASoustraire->this.pair.car != NULL){
        int bit_erreur = 0;
        if(arbreASoustraire->this.pair.car->type == SFS_NUMBER){
            res -= arbreASoustraire->this.pair.car->this.number.this.integer;
            bit_erreur = 1;
        }
        if(strcmp(str3,arbreASoustraire->this.pair.car->this.symbol) == 0){
            bit_infini = 2;
            bit_erreur = 1;
        }
        if(strcmp(str4,arbreASoustraire->this.pair.car->this.symbol) == 0){
            bit_infini *= -1;
            bit_erreur = 1;
        }
        if(bit_erreur == 0){
            ERROR_MSG("\n Il y a un non entier dans l'arbre argument");
        }
        arbreASoustraire = arbreASoustraire->this.pair.cdr;
    }
    if(bit_infini == 1){
        object resObject = make_object(SFS_NUMBER);
        resObject->this.number.this.integer = res;
        return resObject;
    }
    object resObject = make_object(SFS_INFINI);
    if(bit_infini == -2){
        char str000[256] = {'u','n','d','e','f'};
        strcpy(resObject->this.symbol,str000);
        return resObject;
    }
    if(bit_infini == 2){
        strcpy(resObject->this.symbol,str3);
    }
    if(bit_infini == -1){
        strcpy(resObject->this.symbol,str4);
    }
    return resObject;
}


object multiplier_p (object arbreAMultiplier){
    int res = 1;
    int bit_infini = 1;
    /* arbreAMultiplier = arbreAMultiplier->this.pair.cdr; */
    while(arbreAMultiplier->this.pair.car != NULL){
        int bit_erreur = 0; /* Permet de corriger une erreur sur le error_msg qui revient systematiquement*/
        if(arbreAMultiplier->this.pair.car->type == SFS_NUMBER){
            res *= arbreAMultiplier->this.pair.car->this.number.this.integer;
            bit_erreur = 1;
        }
        if((strcmp(str3,arbreAMultiplier->this.pair.car->this.symbol) == 0)&&(bit_infini > 0)){
            bit_infini = 2;
            bit_erreur = 1;
            if(res == 0){
                goto undef;
            }
        }
        if(strcmp(str4,arbreAMultiplier->this.pair.car->this.symbol) == 0){
            bit_infini *= -1;
            bit_erreur = 1;
            if(res == 0){
                goto undef;
            }
        }
        if((arbreAMultiplier->this.pair.car->this.number.this.integer == 0)&&(arbreAMultiplier->this.pair.car->type == SFS_NUMBER)&&(bit_infini != 1)){
            undef : ;
            object resObject = make_object(SFS_INFINI);
            strcpy(resObject->this.symbol,str000);
            return resObject;
        }
        if(bit_erreur == 0){
            ERROR_MSG("\n\nIl y a un non entier dans l'arbre argument\n");
        }
        arbreAMultiplier = arbreAMultiplier->this.pair.cdr;
    }
    if(bit_infini == 1){
        object resObject = make_object(SFS_NUMBER);
        resObject->this.number.this.integer = res;
        return resObject;
    }
    object resObject = make_object(SFS_INFINI);
    if(bit_infini == 2){
        strcpy(resObject->this.symbol,str3);
    }
    if(bit_infini < 0){
        strcpy(resObject->this.symbol,str4);
    }
    return resObject;
}

object diviser_p (object arbreADiviser){
    int bit_infini_num = 1;
    int numerateur = (arbreADiviser->this.pair.car->type == SFS_INFINI) ? 1 : arbreADiviser->this.pair.car->this.number.this.integer;
    if(strcmp(arbreADiviser->this.pair.car->this.symbol,str3)== 0){
        bit_infini_num = 2;
    }
    if(strcmp(arbreADiviser->this.pair.car->this.symbol,str4)== 0){
        bit_infini_num = -1;
    }
    
    object denominateur = multiplier_p(arbreADiviser->this.pair.cdr);
    
    if((denominateur->type == SFS_NUMBER)&&(bit_infini_num == 1)&&(numerateur != 0)){
        if(denominateur->this.number.this.integer == 0){
            object resObject = make_object(SFS_INFINI);
            if(numerateur>=0){
                strcpy(resObject->this.symbol,str3);
            }
            else{
                strcpy(resObject->this.symbol,str4);
            }
            return resObject;
        }
        else{
            int denominateur_entier = denominateur->this.number.this.integer;
            object resObject = make_object(SFS_NUMBER);
            resObject->this.number.this.integer = numerateur / denominateur_entier;
            return resObject;
        }
    }
    if((bit_infini_num == 2)&&(denominateur->type == SFS_NUMBER)){
        object resObject = make_object(SFS_INFINI);
        strcpy(resObject->this.symbol,str3);
        return resObject;
    }
    if((bit_infini_num == -1)&&(denominateur->type == SFS_NUMBER)){
        object resObject = make_object(SFS_INFINI);
        strcpy(resObject->this.symbol,str4);
        return resObject;
    }
    if((bit_infini_num == 1)&&(denominateur->type == SFS_INFINI)){
        object resObject = make_object(SFS_NUMBER);
        resObject->this.number.this.integer = 0;
        return resObject;
    }
    if((numerateur == 0)||(denominateur->this.number.this.integer == 0)||(denominateur->type == SFS_NUMBER)){
        object resObject = make_object(SFS_INFINI);
        strcpy(resObject->this.symbol,str000);
        return resObject;
    }
    if((bit_infini_num != 1)||(denominateur->type == SFS_INFINI)){
        object resObject = make_object(SFS_INFINI);
        strcpy(resObject->this.symbol,str000);
        return resObject;
    }
    ERROR_MSG("\n\nProbleme dans la division\n");
}

object rest_p (object arbreADiviser){
    int bit_infini_num = 1;
    int numerateur = (arbreADiviser->this.pair.car->type == SFS_INFINI) ? 1 : arbreADiviser->this.pair.car->this.number.this.integer;
    if(strcmp(arbreADiviser->this.pair.car->this.symbol,str3)== 0){
        bit_infini_num = 2;
    }
    if(strcmp(arbreADiviser->this.pair.car->this.symbol,str4)== 0){
        bit_infini_num = -1;
    }
    
    object denominateur = multiplier_p(arbreADiviser->this.pair.cdr);
    
    if((denominateur->type == SFS_NUMBER)&&(bit_infini_num == 1)&&(denominateur->this.number.this.integer != 0)){
        int denominateur_entier = denominateur->this.number.this.integer;
        object resObject = make_object(SFS_NUMBER);
        resObject->this.number.this.integer = numerateur % denominateur_entier;
        return resObject;
        
    }
    else{
        object resObject = make_object(SFS_INFINI);
        strcpy(resObject->this.symbol,str000);
        return resObject;
    }
    
    ERROR_MSG("\n\nProbleme dans la division\n");
}

object egal_p (object ArbreATester){
    object resObject = make_object(SFS_BOOLEAN);
    if(ArbreATester->this.pair.car->type != SFS_NUMBER){
        ERROR_MSG("\n\nEntrer des Entiers\n");
    }
    int comparant = ArbreATester->this.pair.car->this.number.this.integer;
    while(ArbreATester->this.pair.car != NULL){
        if(ArbreATester->this.pair.car->type != SFS_NUMBER){
            ERROR_MSG("\n\nEntrer des Entiers\n");
        }
        if(ArbreATester->this.pair.car->this.number.this.integer == comparant){
            ArbreATester = ArbreATester->this.pair.cdr;
        }
        if(ArbreATester->this.pair.car->this.number.this.integer != comparant){
            resObject->this.number.this.integer = 0;
            return resObject;
        }
        ArbreATester = ArbreATester->this.pair.cdr;
    }
    resObject->this.number.this.integer = 1;
    return resObject;
}

object inf_p (object ArbreATester){
    object resObject = make_object(SFS_BOOLEAN);
    int comparant = ArbreATester->this.pair.car->this.number.this.integer;
    ArbreATester = ArbreATester->this.pair.cdr;
    while(ArbreATester->this.pair.car != NULL){
        if(ArbreATester->this.pair.car->type != SFS_NUMBER){
            ERROR_MSG("\n\nEntrer des Entiers\n");
        }
        if(ArbreATester->this.pair.car->this.number.this.integer <= comparant){
            resObject->this.number.this.integer = 0;
            return resObject;
        }
        if(ArbreATester->this.pair.car->this.number.this.integer > comparant){
            comparant = ArbreATester->this.pair.car->this.number.this.integer;
        }
        ArbreATester = ArbreATester->this.pair.cdr;
    }
    resObject->this.number.this.integer = 1;
    return resObject;
}

object sup_p (object ArbreATester){
    object resObject = make_object(SFS_BOOLEAN);
    int comparant = ArbreATester->this.pair.car->this.number.this.integer;
    ArbreATester = ArbreATester->this.pair.cdr;
    while(ArbreATester->this.pair.car != NULL){
        if(ArbreATester->this.pair.car->type != SFS_NUMBER){
            ERROR_MSG("\n\nEntrer des Entiers\n");
        }
        if(ArbreATester->this.pair.car->this.number.this.integer >= comparant){
            resObject->this.number.this.integer = 0;
            return resObject;
        }
        if(ArbreATester->this.pair.car->this.number.this.integer < comparant){
            comparant = ArbreATester->this.pair.car->this.number.this.integer;
        }
        ArbreATester = ArbreATester->this.pair.cdr;
    }
    resObject->this.number.this.integer = 1;
    return resObject;
}


object boolean_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_BOOLEAN){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object string_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_STRING){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object symbol_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_SYMBOL){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object integer_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_NUMBER){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object pair_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_PAIR){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object null_p (object arbreATester){
    while(arbreATester->this.pair.car != NULL){
        if(arbreATester->this.pair.car->type == SFS_NIL){
            arbreATester = arbreATester->this.pair.cdr;
        }
        else{
            object res = make_object(SFS_BOOLEAN);
            res->this.number.this.integer = 0;
            return res;
        }
    }
    object res = make_object(SFS_BOOLEAN);
    res->this.number.this.integer = 1;
    return res;
}

object char_number_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_CHARACTER){
        ERROR_MSG("\n\nErreur\n");
    }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = atoi(argAConvertir->this.pair.car->this.string);
    return resObject;
}

object number_char_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_NUMBER){
        ERROR_MSG("\n\nErreur\n");
    }
    object resObject = make_object(SFS_CHARACTER);
    resObject->this.character = (char) argAConvertir->this.pair.car->this.number.this.integer;
    /*char strosef[256];
     sprintf(strosef, "%d", argAConvertir->this.pair.car->this.number.this.integer);
     strcpy(resObject->this.string,strosef); */
    return resObject;
}

object number_string_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_NUMBER){
        ERROR_MSG("\n\nErreur\n");
    }
    char strnumber[256];
    object resObject = make_object(SFS_STRING);
    sprintf(strnumber, "%d", argAConvertir->this.pair.car->this.number.this.integer);
    strcpy(resObject->this.string,strnumber);
    return resObject;
}

object string_number_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_STRING){
        ERROR_MSG("\n\nErreur\n");
    }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = atoi(argAConvertir->this.pair.car->this.string);
    return resObject;
}

object symbol_string_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_SYMBOL){
        ERROR_MSG("\n\nErreur\n");
    }
    object resObject = argAConvertir->this.pair.car;
    resObject->type = SFS_STRING;
    return resObject;
}

object string_symbol_p (object argAConvertir){
    if(argAConvertir->this.pair.car->type != SFS_STRING){
        ERROR_MSG("\n\nErreur\n");
    }
    object resObject = argAConvertir->this.pair.car;
    resObject->type = SFS_SYMBOL;
    return resObject;
}

object car_p (object arbreAUtiliser){
    return arbreAUtiliser->this.pair.car->this.pair.car;
}

object cdr_p (object arbreAUtiliser){
    return arbreAUtiliser->this.pair.car->this.pair.cdr;
}

object list_p (object arbreAUtiliser){
    return arbreAUtiliser;
}

object eq_p (object arbreAUtiliser){
    object resObject = make_object(SFS_BOOLEAN);
    object test = arbreAUtiliser;
    if(test->this.pair.cdr->this.pair.cdr->this.pair.car != NULL){
        ERROR_MSG("\n\nTrop d'arguments\n");
    }
    object obj1 = arbreAUtiliser->this.pair.car;
    object obj2 = arbreAUtiliser->this.pair.cdr->this.pair.car;
    
    eq :
    
    if(obj1->type != obj2->type){
        ERROR_MSG("\n\nArguments de nature differentes\n");
    }
    if(obj1->type == SFS_NUMBER){
        if(obj1->this.number.this.integer == obj2->this.number.this.integer){
            resObject->this.number.this.integer = 1;
            return resObject;
        }
        resObject->this.number.this.integer = 0;
        return resObject;
    }
    if(obj1->type == SFS_BOOLEAN){
        if(obj1->this.number.this.integer == obj2->this.number.this.integer){
            resObject->this.number.this.integer = 1;
            return resObject;
        }
        resObject->this.number.this.integer = 0;
        return resObject;
    }
    if((obj2->type == SFS_STRING)||(obj2->type == SFS_SYMBOL)){
        if(strcmp(obj1->this.string,obj2->this.string) == 0){
            resObject->this.number.this.integer = 1;
            return resObject;
        }
        resObject->this.number.this.integer = 0;
        return resObject;
    }
    if(obj2->type == SFS_NIL){
        resObject->this.number.this.integer = 1;
        return resObject;
    }
    if(obj1->type == SFS_CHARACTER){
        if(obj1->this.character == obj2->this.character){
            resObject->this.number.this.integer = 1;
            return resObject;
        }
        resObject->this.number.this.integer = 0;
        return resObject;
    }
    if(obj1->type == SFS_PAIR){
        obj1 = sfs_eval(obj1);
        obj2 = sfs_eval(obj2);
        goto eq;
    }
    
    return resObject;
}

object cons_p (object arbreAUtiliser){
    object resObject = cons(arbreAUtiliser->this.pair.car , cons(arbreAUtiliser->this.pair.cdr->this.pair.car,nil));
    return resObject;
}