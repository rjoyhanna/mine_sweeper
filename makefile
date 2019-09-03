mine_sweeper.out: mine_sweeper.o mine_sweeperLogic.o
	gcc -g -Wall -Werror -o mine_sweeper.out mine_sweeper.o mine_sweeperLogic.o

mine_sweeper.o: mine_sweeper.c mine_sweeperLogic.h
	gcc -g -Wall -Werror -c -o mine_sweeper.o mine_sweeper.c

mine_sweeperLogic.o: mine_sweeperLogic.c mine_sweeperLogic.h
	gcc -g -Wall -Werror -c -o mine_sweeperLogic.o mine_sweeperLogic.c   

clear: 
	rm -rf *.o *.out