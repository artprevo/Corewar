.name "zork"
.comment "just a basic living prog"

sti r1,r1,r1

l2:	sti	r2,%66,r1
	sti r1,r1,r1
	sti r1,r3,r1
fork0: live %1
live:	live	%1
	st r1,%:l2
	zjmp	%:live
	sti r1,%:fork0,%1
