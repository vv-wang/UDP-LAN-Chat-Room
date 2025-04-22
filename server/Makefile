OBJS = main.o ulcrs.o linklist.o


server : $(OBJS)
	gcc $^ -o $@ -lpthread
	@echo "Done."

%.o : %.c
	gcc -c $^ -o $@

clean :
	rm *.o server
	@echo "Cleaned."
