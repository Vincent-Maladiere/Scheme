//
//  primitive.h
//  Scheme
//
//  Created by Vincent Maladiere on 16/11/16.
//  Copyright © 2016 Vincent Maladiere. All rights reserved.
//

#ifndef primitive_h
#define primitive_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "object.h"
#include "read.h"
#include "eval.h"
#include "print.h"

object make_primitive(void);

object plus_p (object arbreAAditionner, object environnement);
object moins_p (object arbreASoustraire, object environnement);
object diviser_p (object arbreADiviser, object environnement);
object multiplier_p (object arbreAMultiplier, object environnement);
object rest_p (object arbreADivisionEntiere, object environnement);
object egal_p (object arbreATester, object environnement);
object inf_p (object arbreATester, object environnement);
object sup_p (object arbreATester, object environnement);

/* Renvoie vrai ou faux si tous les arguments sont de la nature testée */
object boolean_p (object arbreATester, object environnement);
object string_p (object arbreATester, object environnement);
object symbol_p (object arbreATester, object environnement);
object char_p (object arbreATester, object environnement);
object integer_p (object arbreATester, object environnement);
object pair_p (object arbreATester, object environnement);
object null_p (object arbreATester, object environnement);

/* Convertit un seul parametre, erreur si plusieurs arguments */
object char_number_p (object argAConvertir, object environnement);
object number_char_p (object argAConvertir, object environnement);
object number_string_p (object argAConvertir, object environnement);
object string_number_p (object argAConvertir, object environnement);
object symbol_string_p (object argAConvertir, object environnement);
object string_symbol_p (object argAConvertir, object environnement);

object cons_p (object arbreAUtiliser, object environnement);
object car_p (object arbreAUtiliser, object environnement);
object cdr_p (object arbreAUtiliser, object environnement);
object set_car_p (object arbreAUtiliser, object environnement);
object set_cdr_p (object arbreAUtiliser, object environnement);
object list_p (object arbreAUtiliser, object environnement); /* Renvoie la liste de tous les arguments */
object eq_p (object arbreAUtiliser, object environnement); /* Renvoie vrai si tous les arguments appartiennent a la meme entite */

#endif /* primitive_h */
