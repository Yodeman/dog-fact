# A simple command line program that prints a random dog fact whenever it is executed.

# SETUP
The program utilizes cpp-httplib library to send requests to the server. In order to be
able to use the program:

	*	install libssl-dev using your linux distribution package manager.
 
Follow the step below to properly setup cpp-httplib library:

	*	clone https://github.com/yhirose/cpp-httplib.git into a directory, then execute
		the following within the created directory
  
		```
		mkdir -p build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Release ..
		sudo cmake --build . --target install
		```
  
## Using cmake
Clone this reposiory into a directory then execute the following within the created directory

		```
		mkdir -p dog_fact_build
		cmake -S ./dog-fact -B ./dog_fact_build
		cmake --build ./dog_fact_build
		```
  
and you should be able to execute the *dog_fact* program from the build directory *dog_fact_build*.

## With g++
Clone this reposiory into a directory then execute the following within the created directory

		```
		mkdir -p dog_fact_build
		g++ ./dog-fact/src/gen_dog_fact.cpp -Wall -std=c++11 -pthread -lssl -lcrypto -DCPPHTTPLIB_OPENSSL_SUPPORT -o ./dog_fact_build/dog_fact
		```
		
  and you should be able to execute the *dog_fact* program from the build directory *dog_fact_build*.  
