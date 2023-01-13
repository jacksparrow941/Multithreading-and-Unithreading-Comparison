build:
	gcc  src/main.c lib/Modules.c -Iinclude -lpthread -lm -o obj/swl2

run:  
	obj/swl2 $(t) $(n)
plot:   
	gnuplot  Euler.p Wallies.p

clean:
	rm -rf o obj/swl2
