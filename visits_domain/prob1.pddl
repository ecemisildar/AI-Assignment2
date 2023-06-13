(define (problem prob1)
(:domain localization)
(:objects
     r0 r1 r2 r3 r4 r5 - region
     R2D2 - robot
     a1 a2 a3 a4 - assignment
)
(:init
    (robot_in R2D2 r0)
    (free R2D2)
    
    (at-assignment a1 r1) (at-assignment a2 r2) (at-assignment a3 r3) (at-assignment a4 r4)
    
    (= (act-cost) 0)
    (= (dummy) 0)

 
)

(:goal 
     (and (robot_in R2D2 r5)
     	  (at-assignment a1 r5) 
     	  (at-assignment a2 r5) 
     )
)

(:metric minimize (act-cost) )
)


