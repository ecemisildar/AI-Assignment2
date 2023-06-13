(define (problem prob1)
(:domain localization)
(:objects
     r0 r1 r2 r3 r4 r5 - region
     R2D2 - robot
)
(:init
    (robot_in R2D2 r0)
    
    ;(at-assignment r1)
    ;(at-assignment r2)
    ;(at-assignment r3)
    ;(at-assignment r4)
   
   
    (= (act-cost) 0)
    (= (dummy) 0)
    (= (collected) 0)

 
)

(:goal 
     (and ;(<= (collected) 2) 
     	(robot_in R2D2 r5)
     )
)

(:metric minimize (act-cost) )
)


