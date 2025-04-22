OBJS = main.o ulcrc.o


client : $(OBJS)
	gcc $^ -o $@ -lpthread
	@echo "Done."

%.o : %.c
	gcc -c $^ -o $@

clean :
	rm *.o client
	@echo "Cleaned."
