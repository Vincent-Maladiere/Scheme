

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
    char str1[256] = {'n','e','w','l','i','n','e'};
    char str2[256] = {'s','p','a','c','e'};
    char str3[256] = {'+','i','n','f'};
    char str4[256] = {'-','i','n','f'};
    
    restart :
    
    if((expr->type==SFS_NUMBER || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type==SFS_CHARACTER || (strcmp(expr->this.symbol,str3) == 0) || (strcmp(expr->this.symbol,str4) == 0))){ /* SFS_PAIR aussi ??????? */
        return expr;  /* pas d'eval donc autoevaluant */
    }
    if(expr->type == SFS_SYMBOL){
        object cherchemaggle = make_object(SFS_PAIR);
        cherchemaggle = env->this.pair.car;
        if(cherchemaggle == NULL){
            ERROR_MSG("\n Undefined parameter\n");
        }
        while(strcmp(cherchemaggle->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) != 0){ /* PB MAGGLE */
            cherchemaggle = cherchemaggle->this.pair.cdr;
            if(cherchemaggle == NULL){
                ERROR_MSG("\n Undefined parameter\n");
            }

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
            
            if((strcmp(cherchemaggle->this.pair.car->this.pair.cdr->this.symbol,str1))||(strcmp(cherchemaggle->this.pair.car->this.pair.cdr->this.symbol,str2))){
                strcpy(result->this.symbol,cherchemaggle->this.pair.car->this.pair.cdr->this.symbol);
            }
            else{
                result->this.character = cherchemaggle->this.pair.car->this.pair.cdr->this.character;
            }
            return result;
        }
        if(SFS_BOOLEAN == cherchemaggle->this.pair.car->this.pair.cdr->type){
            result->this.number.this.integer = cherchemaggle->this.pair.car->this.pair.cdr->this.number.this.integer;
            return result;
        }
    }
    if(is_form("quote",expr) == 1) {
        return expr->this.pair.cdr->this.pair.car;
    }
    if(is_form("if",expr) == 1) {
        if(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 1){
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
        else{
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    if(is_form("define", expr) == 1){
        if(expr->this.pair.cdr->this.pair.car->type == SFS_SYMBOL){
            object safe_env = make_object(SFS_PAIR);
            safe_env->this.pair.car = cons(expr->this.pair.cdr->this.pair.car, sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car));
            safe_env->this.pair.cdr = env->this.pair.car;
            env->this.pair.car = safe_env;
            expr = expr->this.pair.cdr->this.pair.car; /* Permet d'afficher la variable définie avec sfs_print */
        }
        else{
            ERROR_MSG("\n Define impossible\n");
        }
    }
    if(is_form("set!", expr) == 1){
        object safe_env = make_object(SFS_PAIR);
        safe_env = env->this.pair.car; /* On ne perd pas la tête de liste ! On envoit une copie */
        if(safe_env == NULL){
            ERROR_MSG("\n You can't set an undefined parameter\n");
        }
        while(strcmp(safe_env->this.pair.car->this.pair.car->this.symbol, expr->this.pair.cdr->this.pair.car->this.symbol) != 0){
            safe_env = safe_env->this.pair.cdr;
            if(safe_env == NULL){
                ERROR_MSG("\n You can't set an undefined parameter\n");
            }
        }

        safe_env->this.pair.car->this.pair.cdr = sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car);
        expr = expr->this.pair.cdr->this.pair.car;
        return expr;
    }
    
    if(is_form("or", expr) == 1){
        if((sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0)&&(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')){
            if((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')) {
                expr->type = SFS_BOOLEAN;
                expr->this.number.this.integer = 0;
            }
            else{
                expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
                goto restart;
            }
        }
        else{
            expr = expr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    
    if(is_form("and", expr) == 1){
        if(((sfs_eval(expr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) &&(sfs_eval(expr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01')) || ((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car)->this.string[0] == '\x01'))) {
            expr->type = SFS_BOOLEAN;
            expr->this.number.this.integer = 0;
        }
        else {
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
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


else if (isform('+'))
    object(*plus)(object)
    exec(plus, eval(args))


