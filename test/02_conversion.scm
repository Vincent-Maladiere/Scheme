; TEST_RETURN_CODE=PASS
; TEST_COMMENT=conversion

(char->number #\a)
(char->number #\11)
(char->number #\233 #\12)
(char->number "yo")

(number->char "ey")
(number->char 999)

(number->string 12)
(number->string 1000)

(string->number "100")
(string->number "un milliard")

(define test 12)
(symbol->string test)
(symbol->string a)

(string->symbol a)
(string->symbol "e")

;;; Make sure you put a return at
;;; the end of the input file