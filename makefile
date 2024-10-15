hashtable: main.cpp
	g++ -Wall -o main.out main.cpp
	   # write command to test your files (you do not need it for your submissions)

run: main.out 
	./main.out 


clean:
	rm *.out
