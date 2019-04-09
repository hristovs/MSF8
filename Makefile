make:

compile:
	g++ estimate.cpp Select.cpp queries.cpp -lpqxx -lpq -o simulator
