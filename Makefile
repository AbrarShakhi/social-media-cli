

run: compile
	./bin.out

compile:
	g++ src/getkey.cpp src/authentication.cpp src/avl_tree_set.cpp src/binary_tree_frequency_map.cpp src/choice.cpp src/dashboard.cpp src/main.cpp src/merge_sort.cpp src/user.cpp src/utils.cpp src/validatetor.cpp -o bin.out
