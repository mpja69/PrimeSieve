Ver.	Comment
====	=================================================================
1	Allt i main()
	Kör endast 1 gång
	Division (modulo) i innerloop

2	Brytit ut Sieve-funktion
	Kör så många pass som möjligt under 5 sekunder = Riktig mätning!
	Bytt division (modulo) i innerloopen mot att stega med primtalet!

3	Använder en struct för vektorn och dess längd 
	Brutit ut koden i funktioner
	Startar ytterloopen med kvadrat-hopp på primtalet

4	Snyggare findPrimes-funktion

5	Ändrat indexingen i vektorn till att den pekar exakt på rätt primtal
	Initierat vektorn med 0 och 1 för att markera alla jämna direkt (då 2 är ett primtal)
	Ignorerat de 2 första, så att indexingen av vektorn börjar på 3.
	Innerloopen stegar dubbla primtalet för att undvika jämna tal
	Ytterloopen stegar med 2 för att undvika jämna tal
		Kompilerat med -O2 och -O3. Gav 10X prestanda

6	Bytt sqrt mot usqrt: (2X snabbare...men ger inte så mycket i sieven),
	Provar bitmap: otpimera minnet...men inte hastighet
	byte   = (index DIV 8) // Heltalsdivision
	bit    = ( 1 << (index MOD 8)) (ex 00000001 med index 0) //
	 ~bit  = (ex 11111110 med index 0) //komplementet
	Clear: buf[byte] = ~bit     (( AND 
	Get: (buf[byte] & bitmask) !=0 // Kolla om biten är satt... (alltså inte 0)
