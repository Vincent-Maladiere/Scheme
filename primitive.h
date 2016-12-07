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

object plus_p (object arbreAAditionner);
object moins_p (object arbreASoustraire);
object diviser_p (object arbreADiviser);
object multiplier_p (object arbreAMultiplier);
object rest_p (object arbreADivisionEntiere);
object egal_p (object arbreATester);
object inf_p (object arbreATester);
object sup_p (object arbreATester);

/* Renvoie vrai ou faux si tous les arguments sont de la nature testée */
object boolean_p (object arbreATester);
object string_p (object arbreATester);
object symbol_p (object arbreATester);
object char_p (object arbreATester);
object integer_p (object arbreATester);
object pair_p (object arbreATester);
object null_p (object arbreATester);

/* Convertit un seul parametre, erreur si plusieurs arguments */
object char_number_p (object argAConvertir);
object number_char_p (object argAConvertir);
object number_string_p (object argAConvertir);
object string_number_p (object argAConvertir);
object symbol_string_p (object argAConvertir);
object string_symbol_p (object argAConvertir);

object cons_p (object arbreAUtiliser);
object car_p (object arbreAUtiliser);
object cdr_p (object arbreAUtiliser);
object set_car_p (object arbreAUtiliser);
object set_cdr_p (object arbreAUtiliser);
object list_p (object arbreAUtiliser); /* Renvoie la liste de tous les arguments */
object eq_p (object arbreAUtiliser); /* Renvoie vrai si tous les arguments appartiennent a la meme entite */

#endif /* primitive_h */
