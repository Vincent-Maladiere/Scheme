; TEST_RETURN_CODE=PASS
; TEST_COMMENT=fonctions_structures

(cons 'a ())
(cons 'a '(1 2 3))

(car cons('a '(1 2 3)))
(car (cdr '(#t #\c +inf))

(cdr cons('a '(1 2 3)))
(cdr (cdr cdr (1 2 3 4 5)))

(list #t "amour" 123 #\p #\e)
(list (list 1 2) 3 4)


(eq? (or #t #t) (and #t #t))
(eq? 1 1 1)
(eq? (+ 1 2) (- 4 1))
(eq? (< 1 2) (= 2 2))

