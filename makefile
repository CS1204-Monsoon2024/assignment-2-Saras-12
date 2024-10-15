hash_table: main.cpp HashTable.cpp
	g++ -Wall -o hash_table.out main.cpp HashTable.cpp
	# write command to test your files (you do not need it for your submissions)

clean:
	rm *.out
