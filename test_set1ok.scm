; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Test_set1, on fait appel a define au prealable


(define a 3)
(set a 5)
a
(set a 7)
a
(set a riri)
a
(define b hola)
(set a b)
a
