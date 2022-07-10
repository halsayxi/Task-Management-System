test:
	g++ main.cpp Task_Management.cpp Periodic_Scanning.cpp input_from_cmd.cpp user.h -pthread -o test
clean:
	rm test