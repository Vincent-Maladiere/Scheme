

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "primitive.h"
#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

object sfs_eval( object expr, object env) {
    char str1[256] = {'n','e','w','l','i','n','e'};
    char str2[256] = {'s','p','a','c','e'};
    char str3[256] = {'+','i','n','f'};
    char str4[256] = {'-','i','n','f'};
    
    restart :
    
    if((expr->type==SFS_NUMBER || expr->type == SFS_INFINI || expr->type == SFS_NIL || expr->type==SFS_STRING || expr->type==SFS_BOOLEAN  || expr->type==SFS_CHARACTER || (strcmp(expr->this.symbol,str3) == 0) || (strcmp(expr->this.symbol,str4) == 0))){
        return expr;  /* pas d'eval puisqu'autoevaluant */
    }
    if(expr->type == SFS_SYMBOL){
        object prim_safe = list_prim->this.pair.cdr; /* attention 'cdr' et pas 'car' pour list_prim, contrairement à env */
        while(prim_safe->this.pair.car != NULL){
            if(strcmp(prim_safe->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) == 0){
                object result = make_object(SFS_SYMBOL);
                strcpy(result->this.symbol,expr->this.symbol);
                return result;
            }
            prim_safe = prim_safe->this.pair.cdr;
        }
        object cherchemaggle = make_object(SFS_PAIR);
        cherchemaggle = env->this.pair.car;
        if(cherchemaggle == NULL){
            WARNING_MSG("\n\nUndefined parameter\n");
            return NULL;
        }
        while(strcmp(cherchemaggle->this.pair.car->this.pair.car->this.symbol, expr->this.symbol) != 0){ /* PB MAGGLE */
            cherchemaggle = cherchemaggle->this.pair.cdr;
            if(cherchemaggle == NULL){
                WARNING_MSG("\n\nUndefined parameter\n");
                return NULL;
            }

        }
        object result = cherchemaggle->this.pair.car->this.pair.cdr;
        return result;
        /*object result = make_object(cherchemaggle->this.pair.car->this.pair.cdr->type);
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
        }*/
    }
    if(is_form("quote",expr) == 1) {
        return expr->this.pair.cdr->this.pair.car;
    }
    if(is_form("if",expr) == 1) {
        if(sfs_eval(expr->this.pair.cdr->this.pair.car,env)->this.number.this.integer == 1){
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
            safe_env->this.pair.car = cons(expr->this.pair.cdr->this.pair.car, sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env));
            safe_env->this.pair.cdr = env->this.pair.car;
            env->this.pair.car = safe_env;
            expr = expr->this.pair.cdr->this.pair.car;
            return NULL;
        }
        else{
            WARNING_MSG("\n\nDefine impossible\n");
            return NULL;
        }
    }
    if(is_form("set!", expr) == 1){
        object safe_env = make_object(SFS_PAIR);
        safe_env = env->this.pair.car; /* On ne perd pas la tête de liste ! On envoit une copie */
        if(safe_env == NULL){
            WARNING_MSG("\n\nYou can't set an undefined parameter\n");
            return NULL;
        }
        while(strcmp(safe_env->this.pair.car->this.pair.car->this.symbol, expr->this.pair.cdr->this.pair.car->this.symbol) != 0){
            safe_env = safe_env->this.pair.cdr;
            if(safe_env == NULL){
                WARNING_MSG("\n\nYou can't set an undefined parameter\n");
                return NULL;
            }
        }

        safe_env->this.pair.car->this.pair.cdr = sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env);
        expr = expr->this.pair.cdr->this.pair.car;
        return expr;
    }
    
    if(is_form("or", expr) == 1){
        if((sfs_eval(expr->this.pair.cdr->this.pair.car,env)->this.number.this.integer == 0)&&(sfs_eval(expr->this.pair.cdr->this.pair.car,env)->this.string[0] == '\x01')){
            if((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env)->this.string[0] == '\x01')) {
                expr->type = SFS_BOOLEAN;
                expr->this.number.this.integer = 0;
                return expr;
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
        if(((sfs_eval(expr->this.pair.cdr->this.pair.car,env)->this.number.this.integer == 0) &&(sfs_eval(expr->this.pair.cdr->this.pair.car,env)->this.string[0] == '\x01')) || ((sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env)->this.number.this.integer == 0) && (sfs_eval(expr->this.pair.cdr->this.pair.cdr->this.pair.car,env)->this.string[0] == '\x01'))) {
            expr->type = SFS_BOOLEAN;
            expr->this.number.this.integer = 0;
            return expr;
        }
        else {
            expr = expr->this.pair.cdr->this.pair.cdr->this.pair.car;
            goto restart;
        }
    }
    
    if(is_form("begin", expr) == 1){
        object resultat = NULL;
        expr = expr->this.pair.cdr;
        while (expr->type != SFS_NIL){
            resultat =  sfs_eval(expr->this.pair.car,env);
            expr = expr->this.pair.cdr;
        }
        return resultat;
    }

    if(is_form("let", expr) == 1){
        object env_let = make_object(SFS_PAIR);
        env_let->this.pair.car = make_object(SFS_PAIR);
        object env_let_safe = env_let->this.pair.car;
        expr = expr->this.pair.cdr;
        if((expr->this.pair.cdr != NULL)&&(expr->this.pair.cdr->this.pair.cdr->type == SFS_NIL)){
            object argument = expr->this.pair.car;
            while(argument->this.pair.cdr != NULL){
                env_let_safe->this.pair.car = cons(argument->this.pair.car->this.pair.car,sfs_eval(argument->this.pair.car->this.pair.cdr->this.pair.car,env_let));
                argument = argument->this.pair.cdr;
                env_let_safe->this.pair.cdr = make_object(SFS_PAIR);
                env_let_safe = env_let_safe->this.pair.cdr;
            }
            object body = expr->this.pair.cdr->this.pair.car;
            return sfs_eval(body,env_let);
            
        }
        else{
            WARNING_MSG("\n\nProblème d'arguments\n");
            return NULL;
        }
    }
    
    if(is_form("lambda", expr) == 1){
        object env_lambda = make_lambda(expr);
        env->this.pair.cdr = env_lambda;
        return env_lambda->this.pair.car->this.pair.car;  /* quesct ce quon retourne ici ? le coupound ? car ca doit mettre <#closure>*/ 
    }
    
    if(is_form("lambda",expr->this.pair.car) == 1){
        if(expr->this.pair.cdr->this.pair.car != NULL){ /* Doute : avec ou sans this.pair.car ??*/
            object env_lambda = make_lambda(expr->this.pair.car);
            return lambda_a_evaluer(expr, env_lambda);
        }
        WARNING_MSG("Argument d'entrée attendu");
        return NULL;
    }
    
    else{
        object prim_safe = list_prim->this.pair.cdr;
        if(env->this.pair.car != NULL){
            object env_safe = env->this.pair.car;
            while(env_safe->this.pair.car != NULL){
                if(is_form(env_safe->this.pair.car->this.pair.car->this.symbol,expr) == 1){
                    if(env_safe->this.pair.car->this.pair.cdr->type == SFS_SYMBOL){
                        strcpy(expr->this.pair.car->this.symbol,env_safe->this.pair.car->this.pair.cdr->this.symbol);
                    }
                    if(env_safe->this.pair.car->this.pair.cdr->type == SFS_COMPOUDS){
                        return lambda_a_evaluer_apres_define(expr, env_safe);
                    }
                }
                env_safe = env_safe->this.pair.cdr;
            }
        }
        while(prim_safe->this.pair.car != NULL){
            if(is_form(prim_safe->this.pair.car->this.pair.car->this.symbol, expr) == 1){
                object ArbreAEvaluer = make_object(SFS_PAIR);
                object ArbreAEvaluer_safe = ArbreAEvaluer;
                object expr_safe = expr->this.pair.cdr;
                while(expr_safe != nil){
                    ArbreAEvaluer_safe->this.pair.car = ((is_form("symbol?",expr))||(is_form("symbol->string",expr))||(is_form("pair?",expr))) ? expr_safe->this.pair.car : sfs_eval(expr_safe->this.pair.car,env);
                    expr_safe = expr_safe->this.pair.cdr;
                    ArbreAEvaluer_safe->this.pair.cdr = make_object(SFS_PAIR);
                    ArbreAEvaluer_safe = ArbreAEvaluer_safe->this.pair.cdr;
                }
                object objetPrimitive = prim_safe->this.pair.car->this.pair.cdr;
                object resultat = objetPrimitive->this.primitive.fonction(ArbreAEvaluer);
                return resultat;
            }
            prim_safe = prim_safe->this.pair.cdr;
        }
        WARNING_MSG("\n\nJe crains que cette fonction n'existe point \n");
        return NULL;
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

object make_lambda(object expr){
    expr = expr->this.pair.cdr;
    object parametres = expr->this.pair.car;
    object parametres_safe = parametres;
    object corps = expr->this.pair.cdr->this.pair.car;  /* cad, pour ((lambda(x) (* 2 x)), c'est donc * ? ou alors (* 2 x) ?n */
    object env_lambda = make_object(SFS_PAIR);
    object env_lambda_safe = env_lambda;
    env_lambda_safe->this.pair.car = make_object(SFS_PAIR);
    env_lambda_safe = env_lambda_safe->this.pair.car;
    env_lambda_safe->this.pair.car = make_object(SFS_COMPOUDS);
    while(parametres_safe->this.pair.cdr != NULL){
        if(parametres_safe->this.pair.car->type == SFS_SYMBOL){
            parametres_safe = parametres_safe->this.pair.cdr;
        }
        else{
            WARNING_MSG("\n\nProblème de paramètres\n");
            return NULL;
        }
    }
    env_lambda_safe->this.pair.car->this.compound.parms = make_object(SFS_PAIR);
    env_lambda_safe->this.pair.car->this.compound.parms = parametres;
    env_lambda_safe->this.pair.car->this.compound.body = make_object(SFS_PAIR);
    env_lambda_safe->this.pair.car->this.compound.body = corps;
    return env_lambda;
}

object lambda_a_evaluer(object expr, object env_lambda){
    object argument = expr->this.pair.cdr;    
    object corps = env_lambda->this.pair.car->this.pair.car->this.compound.body;
    object environnement = make_object(SFS_PAIR);
    environnement->this.pair.cdr = NULL;
    environnement->this.pair.car = make_object(SFS_PAIR);
    object environnement_safe = environnement->this.pair.car;
    object parametres = env_lambda->this.pair.car->this.pair.car->this.compound.parms;
    while(parametres->this.pair.cdr != NULL){
        environnement_safe->this.pair.car = cons(parametres->this.pair.car,sfs_eval(argument->this.pair.car,env));
        environnement_safe->this.pair.cdr = make_object(SFS_PAIR);
        environnement_safe = environnement_safe->this.pair.cdr;
        parametres = parametres->this.pair.cdr;
        argument = argument->this.pair.cdr;
    }
    env_lambda->this.pair.car->this.pair.car->this.compound.envt = environnement;
    return sfs_eval(corps,environnement);
}

object lambda_a_evaluer_apres_define(object expr, object env_lambda){
    object arguments = expr->this.pair.cdr;    
    object corps = env_lambda->this.pair.car->this.pair.cdr->this.compound.body;
    object environnement = make_object(SFS_PAIR);
    environnement->this.pair.cdr = NULL;
    environnement->this.pair.car = make_object(SFS_PAIR);
    object environnement_safe = environnement->this.pair.car;
    object parametres = env_lambda->this.pair.car->this.pair.cdr->this.compound.parms;
    while(parametres->this.pair.cdr != NULL){
        if(arguments == NULL){
            WARNING_MSG("\n\nIl manque des arguments d'entrée\n");
            return NULL;
        }
        environnement_safe->this.pair.car = cons(parametres->this.pair.car,sfs_eval(arguments->this.pair.car,env));
        environnement_safe->this.pair.cdr = make_object(SFS_PAIR);
        environnement_safe = environnement_safe->this.pair.cdr;
        parametres = parametres->this.pair.cdr;
        arguments = arguments->this.pair.cdr;
    }
    env_lambda->this.pair.car->this.pair.cdr->this.compound.envt = environnement;
    return sfs_eval(corps,environnement);
}
