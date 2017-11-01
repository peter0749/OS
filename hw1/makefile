all: hw1 server
hw1: hw1.c
	gcc hw1.c ${ARGS} -o hw1
server: create_shm.c
	gcc create_shm.c -o server
clean:
	rm -f hw1 server
clear_all_ipcs: hw1
	./clean_ipcs
