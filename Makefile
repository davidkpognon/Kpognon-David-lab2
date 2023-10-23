time: ipc.o time.o main.o 
	$(CC) -o $@ $?

ipc.o: ipc.c 
	$(CC) -c $?

time.o: time.c 
	$(CC) -c $?

main.o: main.c 
	$(CC) -c $?

clean:
	-rm -f *.o
	@echo "All clean!"