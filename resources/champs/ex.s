.name "zork"
.comment "just a basic living prog"

l2:	sti	-4,%:live,%0
	and	r1,%0, r12
live:	live	%1
	zjmp	%:live
