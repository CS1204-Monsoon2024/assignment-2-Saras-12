hashtable: main.cpp
	g++ -Wall -o main.out main.cpp
	# write the command for compiling main.cpp to main.out
	
run: main.out
	./main.out
	# run the compiled hashtable program
	
clean:
	rm *.out
	# clean up all .out files
