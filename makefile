#makefile
#Emilio Sillart
#proj1 - Data Structures 

CC = g++ -std=c++11


proj.x: proj1.cpp
	$(CC) -o proj.x proj1.cpp


clean: 
	rm -rf *.o *~ *.x
