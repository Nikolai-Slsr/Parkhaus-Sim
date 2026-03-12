
test_objs = obj/queue.o obj/parkhaus.o obj/statistics.o obj/sim_parameters.o obj/functions_test_file.o

main_objs = obj/main.o obj/queue.o obj/parkhaus.o obj/statistics.o obj/sim_parameters.o	

all: main

main: $(main_objs)
	gcc -Wall -Wextra -Iinclude -o main $(main_objs)

main.o: src/main.c
	gcc -Wall -Wextra -Iinclude -c src/main.c -o obj/main.o

queue.o: src/queue.c
	gcc -Wall -Wextra -Iinclude -c src/queue.c -o obj/queue.o

parkhaus.o: src/parkhaus.c
	gcc -Wall -Wextra -Iinclude -c src/parkhaus.c -o obj/parkhaus.o

statistics.o: src/statistics.c
	gcc -Wall -Wextra -Iinclude -c src/statistics.c -o obj/statistics.o

sim_parameters.o: src/sim_parameters.c
	gcc -Wall -Wextra -Iinclude -c src/sim_parameters.c -o obj/sim_parameters.o

obj/functions_test_file.o: test/functions_test_file.c
    gcc -Wall -Wextra -Iinclude -c test/functions_test_file.c -o obj/functions_test_file.o

test: $(test_objs)
	gcc -Wall -Wextra -o tests/functions_test $(test_objs)

clean:
	rm -rf obj main tests/functions_test

deepclean: clean
	rm -rf outputs/