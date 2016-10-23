

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
    if(expr->type == SFS_SYMBOL){
        object cherchemaggle = make_object(SFS_PAIR);
        cherchemaggle = env->this.pair.car;
        while(strcmp(cherchemaggle->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) != 0){ /* PB MAGGLE */
            if(cherchemaggle == nil){
                ERROR_MSG("Undefined parameter");
            }
            cherchemaggle = cherchemaggle->this.pair.cdr;
        }
        object result = make_object(cherchemaggle->this.pair.car->this.pair.cdr->type);
        if(SFS_NUMBER == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.number.this.integer = cherchemaggle->this.pair.car->this.pair.cdr->this.number.this.integer;
            return result;
        }
        if(SFS_STRING == cherchemaggle->this.pair.car->this.pair.cdr->type){
            strcpy(result->this.string, cherchemaggle->this.pair.car->this.pair.cdr->this.string);
            return result;
        }
        if(SFS_CHARACTER == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.character = cherchemaggle->this.character;
            return result;
        }
        if(SFS_BOOLEAN == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.number.this.integer = cherchemaggle->this.number.this.integer;
            return result;
        }
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
            safe_env->this.pair.car = cons(expr->this.pair.cdr->this.pair.car, expr->this.pair.cdr->this.pair.cdr->this.pair.car);
            safe_env->this.pair.cdr = env->this.pair.car;
            env->this.pair.car = safe_env;
            expr = expr->this.pair.cdr->this.pair.car; /* Permet d'afficher la variable définie avec sfs_print */
        }
        else{
            ERROR_MSG("Define impossible");
        }
    }
    if(is_form("set!", expr) == 1){
        object safe_env = make_object(SFS_PAIR);
        safe_env = env->this.pair.car; /* On ne perd pas la tête de liste ! On envoit une copie */
        while(strcmp(safe_env->this.pair.car->this.pair.car->this.symbol, expr->this.pair.cdr->this.pair.car->this.symbol) != 0){
            if(safe_env == nil){
                ERROR_MSG("You can't set an undefined parameter");
            }
            safe_env = safe_env->this.pair.cdr;
        }
        safe_env->this.pair.car->this.pair.cdr->type = expr->this.pair.cdr->this.pair.cdr->this.pair.car->type;
        
        if(SFS_NUMBER == safe_env->this.pair.car->this.pair.cdr->type){
            safe_env->this.pair.car->this.pair.cdr->this.number.this.integer = expr->this.pair.cdr->this.pair.cdr->this.pair.car->this.number.this.integer;
            expr = expr->this.pair.cdr->this.pair.car;
            return expr;
        }
        if(SFS_STRING == safe_env->this.pair.car->this.pair.cdr->type){
            strcpy(safe_env->this.pair.car->this.pair.cdr->this.string, expr->this.pair.cdr->this.pair.cdr->this.pair.car->this.string);
            expr = expr->this.pair.cdr->this.pair.car;
            return expr;
        }
        if(SFS_CHARACTER == safe_env->this.pair.car->this.pair.cdr->type){
            safe_env->this.pair.car->this.pair.cdr->this.character = expr->this.pair.cdr->this.pair.cdr->this.character;
            expr = expr->this.pair.cdr->this.pair.car;
            return expr;
        }
        if(SFS_BOOLEAN == safe_env->this.pair.car->this.pair.cdr->type){
            safe_env->this.pair.car->this.pair.cdr->this.number.this.integer = expr->this.pair.cdr->this.pair.cdr->this.pair.car->this.number.this.integer;
            expr = expr->this.pair.cdr->this.pair.car;
            return expr;
        }

    }
    if(is_form("or", expr) == 1){
        
    }
    if(is_form("and", expr) == 1){
        
    }

    return expr;
}



 int is_form (char *name, object expr) {  /* detecter si c'est une forme oui==1, 0 sinon */
     if ((expr->type == SFS_PAIR) && (expr->this.pair.car->type == SFS_SYMBOL) && (0 == strcmp(name, expr->this.pair.car->this.string))){
        return 1;
    }
    else{
        return 0;
    }
}
