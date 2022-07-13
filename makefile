test:
	g++ main.cpp add_user.cpp login.cpp print_user.cpp get_hash.cpp change_user.cpp delete_user.cpp Task_Management.cpp Task_process.cpp Periodic_Scanning.cpp input_from_cmd.cpp user.h -pthread -o test
clean:
	rm test 
