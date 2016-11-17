#include "primitive.h"

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

    /* / */
    
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str7[256] = {'/'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str7);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = diviser_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr
    
    /* * */
        
    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str7[256] = {'*'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str7);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = multiplier_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;
    
    /* % */
    
    object rest_p (object arbreADivisionEntiere);

    o->this.pair.car = make_object(SFS_PAIR);
    o->this.pair.car->this.pair.car = make_object(SFS_SYMBOL);
    char str8[256] = {'%'};
    strcpy(o->this.pair.car->this.pair.car->this.symbol,str8);
    
    o->this.pair.car->this.pair.cdr = make_object(SFS_PRIMITIVE);
    o->this.pair.car->this.pair.cdr->this.primitive.fonction = rest_p;
    
    o->this.pair.cdr = make_object(SFS_PAIR);
    o = o->this.pair.cdr;


    
    
    return list_prim;
}



object plus_p (object arbreAAditionner){
    int res = 0;
    while(arbreAAditionner->this.pair.car != NULL){
        if(arbreAAditionner->this.pair.car->type == SFS_NUMBER){
            res += arbreAAditionner->this.pair.car->this.number.this.integer;
        }
        else{
            ERROR_MSG("\n Il y a un non entier dans l'arbre argument");
        }
        arbreAAditionner = arbreAAditionner->this.pair.cdr;
    }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = res;
    return resObject;
}

object moins_p (object arbreASoustraire){
    int res = arbreASoustraire->this.pair.car->this.number.this.integer;
    arbreASoustraire = arbreASoustraire->this.pair.cdr;
    while(arbreASoustraire->this.pair.car != NULL){
        if(arbreASoustraire->this.pair.car->type == SFS_NUMBER){
            res -= arbreASoustraire->this.pair.car->this.number.this.integer;
        }
        else{
            ERROR_MSG("\n Il y a un non entier dans l'arbre argument");
        }
        arbreASoustraire = arbreASoustraire->this.pair.cdr;
    }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = res;
    return resObject;
}


object diviser_p (object arbreAdiviser){

        if(arbreAdiviser->this.pair.car->type == SFS_NUMBER){            
            int res = arbreAdiviser->this.pair.car->this.number.this.integer;
            arbreAdiviser = arbreAdiviser->this.pair.cdr;

                while(arbreAdiviser->this.pair.car != NULL){
                    if((arbreAdiviser->this.pair.car->type == SFS_NUMBER)||(0! = arbreAdiviser->this.pair.car->this.number.this.integer)){            
                        res /= arbreAdiviser->this.pair.car->this.number.this.integer;
                    }
                    else{
                        ERROR_MSG("\n Il y a un non entier dans l'arbre argument");
                    }
                arbreAdiviser = arbreAdiviser->this.pair.cdr;
                }
       else {
       ERROT_MSG ("\n Il faut au moins un entier pour pouvoir faire l'opération: diviser");
       }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = res;
    return resObject;
}
    
    
object multiplier_p (object arbreAmultiplier){

if(arbreAdiviser->this.pair.car->type == SFS_NUMBER){            
  int res = arbreAdiviser->this.pair.car->this.number.this.integer;
  arbreAmultiplier = arbreAmultiplier->this.pair.cdr;
    
    while(arbreAmultiplier->this.pair.car != NULL){
        if(arbreAmultiplier->this.pair.car->type == SFS_NUMBER){
            res *= arbreAmultiplier->this.pair.car->this.number.this.integer;
        }
        else{
            ERROR_MSG("\n multiplication impossible, Il y a un non entier dans l'arbre argument");
        }
        arbreAmultiplier = arbreAmultiplier->this.pair.cdr;
    }
    object resObject = make_object(SFS_NUMBER);
    resObject->this.number.this.integer = res;
    return resObject;
}
    
    
