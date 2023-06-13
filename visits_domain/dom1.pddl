(define (domain localization)

(:requirements :typing :durative-actions :numeric-fluents :negative-preconditions :action-costs :conditional-effects :equality :fluents )


(:types 	robot region assignment )


(:predicates
		(robot_in ?v - robot ?r - region)
		(at-assignment ?a - assignment ?r - region)
		(carry ?a - assignment) 
		(free ?v - robot)
	      
)

(:functions 
		(act-cost) (triggered ?from ?to - region) (dummy)
)

(:durative-action goto_region
		:parameters (?v - robot ?from ?to - region)
		:duration (= ?duration 100)
		:condition (and (at start (robot_in ?v ?from)))
	        :effect (and 
	        		(at start (not (robot_in ?v ?from))) 
	        		(at start (increase (triggered ?from ?to) 1))
				(at end (robot_in ?v ?to)) 
				(at end (assign (triggered ?from ?to) 0))  	
                		(at end (increase (act-cost) (dummy))))
)


(:action pick_up
		:parameters (?v - robot ?a - assignment ?r - region)
		:precondition (and 
				(at-assignment ?a ?r) 
				(free ?v))
		:effect (and 
				(carry ?a) 
				(not(at-assignment ?a ?r)) 
				(not(free ?v)))


)


(:action drop
		:parameters (?v - robot ?a - assignment ?r - region)
		:precondition (and 
				(robot_in ?v ?r) 
				(carry ?a))
		:effect (and 
				(at-assignment ?a ?r) 
				(free ?v) 
				(not(carry ?a)))


)



)
