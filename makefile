build:
	gcc main.c lists.c supplementary_functions.c 'stack&queque.c' tree.c -o lanParty
	./lanParty date/t13/c.in date/t13/d.in r.out
clean:
	rm -f lanParty