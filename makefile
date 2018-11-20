# target: dependencies
# <tab> rule

# make (without arguments) executes first rule in file
# Ideally, one target for every object file and a target for final binary.

BST: driver.o
	g++ -oBST  driver.o
driver.o: driver.cpp BST312.h
	g++ -c driver.cpp