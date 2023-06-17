(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents )


(:types 	robot region)


(:predicates
		(robot_in ?v - robot ?r - region)
		(visited ?r - region)
		(at-assignment ?r - region)
	      
)

(:functions 
		(act-cost) (triggered ?from ?to - region) (dummy) (collected)
)

;(:action take-assignment
 ;       :parameters (?v - robot
  ;      	     ?r - region)
   ;     :precondition (and (at-assignment ?r)
    ;    		(robot_in ?v ?r)
     ;   		(< (collected) 2))
      ;  :effect (and (not (at-assignment ?r))
       ;              (increase (collected) 1))
    ;)
    

(:durative-action goto_region
		:parameters (?v - robot ?from ?to - region)
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)))
	        :effect (and 
	        		(at start (not (robot_in ?v ?from))) 
	        		(at start (increase (triggered ?from ?to) 1))
				(at end (robot_in ?v ?to)) 
				(at end (assign (triggered ?from ?to) 0))  
				(at end (visited ?to)) 		
                		(at end (increase (act-cost) (dummy))))
)



)
