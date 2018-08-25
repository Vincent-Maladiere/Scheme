; TEST_RETURN_CODE=PASS
; TEST_COMMENT=Arithmétique

(+ 1 2)
(+ 300 "koa")
(- 1 2 3 4 5)
(* (+ 18 2) (- 15 5) (* 2 5))
(/ 1 9 8)
(% 236 13 3)

(* 999999999999 34)
(* 123456789123456789 0)
(* 7878787878787878 -inf)

(/ 0 0)
(/ -inf 0)
(/ 0 +inf)
(/ +inf -inf)

(= (* 5 4) (- 30 10))
(= 12 13)

(< 1 2 3 5 4)
(< 18 34 400000)

(> 1 2 3 4 5)
(> 23 12 2)

;;; Make sure you put a return at
;;; the end of the input file