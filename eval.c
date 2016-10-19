

/**
 * @file eval.c
 * @author François Cayre <cayre@yiking.(null)>
 * @date Fri Jun 22 20:11:30 2012
 * @brief Evaluation stuff for SFS.
 *
 * Evaluation stuff for SFS.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

object sfs_eval( object expr ) {
    
   uint *ici = 0;
   restart :
    
    if((expr->type==SFS_NUMBER || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type==SFS_CHARACTER)){ /* SFS_PAIR aussi ??????? */
        return expr;  /* pas d'eval donc autoevaluant */
    }
    if(is_form("quote",expr) == 1) {
        return expr->this.pair.cdr->this.pair.car;
    }
    if(is_form("if",expr) == 1) {
        if(sfs_eval(cdr(car(expr))) == TRUE){
            expr = cdr(cdr(car(expr)));
            goto restart;
        }
        else{
            expr = cdr(cdr(cdr(car(expr))));
            goto restart;
        }
    }
    if(is_form("define", expr) == 1){
        if(expr->this.pair.cdr->this.pair.car->type == SFS_SYMBOL){
        object safe_env = make_object(SFS_PAIR);
        safe_env = env->this.pair.car; /* env non def comme paire dans repl WHY? */
        env->this.pair.car->this.pair.car = cons(expr->this.pair.cdr->this.pair.car, expr->this.pair.cdr->this.pair.cdr->this.pair.car);
        env->this.pair.car->this.pair.cdr = safe_env; /* la save_env nouveau est decalé apres l'introduction precedente */
        expr = expr->this.pair.cdr->this.pair.car; /* Permet d'afficher la variable définie avec sfs_print */
        }
        else{
            ERROR_MSG("Define impossible");
        }
    }
    if(is_form("set!", expr) == 1){
        if(expr->this.pair.cdr->this.pair.car->type == SFS_SYMBOL){ condition obligée
        cas (define a b):
        
        aller chercher si le cdr(cdr(expr))==>(le b du coup) existe deja dans lenvironnement avec la meme technique que define en simple (voir plus bas)
        Si b nexiste pas, le créer avec define, sinon cest bon
        if(expr->this.pair.cdr->this.pair.cdr->type == SFS_NUMBER){  cas simple nombre   
        while (is_form ((car(car(car(env))), car(cdr(expr))) != 0 ){
       
            /*env->this.pair.car->this.pair.car->this.pair.car = 
           
            ...
            car(cdr(expr))= cdr(cdr(expr))  affecter valeur
            expr = expr->this.pair.cdr->this.pair.car;  expr = expr->this.pair.cdr->this.pair.car;
        
            else{
            ERROR_MSG("Define impossible");

        while(car(car(car(env))) != car(cdr(expr))){ /*On s'en tient à l'env courant pour l'instant : Tant que le nom de la variable n'est pas trouvé on */
        /* pas possible de comparer des pointeurs, mettre eval avant ? sauf que eval marche que pour une expr */ 
            /* que faire pour les cas (set a b) */
        }
    }
    if(is_form("or", expr) == 1){
        
    }
    if(is_form("and", expr) == 1){
        
    }
    else{
        return expr;
    }
    return nil;
}


 int is_form (char *name, object expr) {  /* detecter si c'est une forme oui==1, 0 sinon */
     if ((expr->type == SFS_PAIR) && (expr->this.pair.car->type == SFS_SYMBOL) && (0 == strcmp(name, expr->this.pair.car->this.string))){
        return 1;
    }
    else{
        return 0;
    }
}







void change_env (){
    env = cdr(env);
}

void back_to_head_env (object saved_env){
    env = saved_env ;
}
