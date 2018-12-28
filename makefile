exe : *.c
	gcc *.c -o exe -lm
	
clean :
	rm exe