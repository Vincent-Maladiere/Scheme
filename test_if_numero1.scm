; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test_if_numero 1

(if #t 4) /* renvoi 4 si c'est vrai, sinon renvoi false */
(if #t 4 5) 
(if #f 4)
(if #f 4 5)

