; TEST_RETURN_CODE=PASS
; TEST_COMMENT=type_primitive

(boolean? #t #f #"hello")
(boolean? (or #f #t))

(string? "bonsoir" "strings of life")
(string? "guttentag" 718)

(define a 3)
(symbol? a)
(symbol? "a")

(char? #\h #\y #\p #\e)
(char? "hype")

(integer? 2 (* 23 4) 10)
(integer? a 34)

(pair? (quote "hola como esta en la casa") (+ 1 2))
(pair? 1)

(nill? () () ())
(nill? () "NULL" ())


;;; Make sure you put a return at
;;; the end of the input file