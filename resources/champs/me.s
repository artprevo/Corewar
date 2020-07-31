.name "some name"
.comment "some comments"


	 fork  %:label00          		# 3,0,281
	 ld    %-272,r3           		# 7,3,278
	 live  %0                 		# 5,10,271
	 fork  %:label00         		# 3,15,266
	 ld    %-272,r3           		# 7,18,263
	 fork  %:label00          		# 3,25,256
	 ld    %0,r2              		# 7,28,253
	 ld    %0,r4              		# 7,35,246
	 zjmp  %:label00          		# 3,42,239
label00:

RESTE A TAFFER TOTO.S ET CAR.S