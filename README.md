**************************************
 * Abhishek Jhoree
 * 0986820
 * 26/02/2018
 * cis3110 - A2
 **************************************

********************************
Questions
********************************
1)	Yes my program does include switch overhead for the first ready state to running state transition.
			 

2) 	Yes the program will include switch overhead becuase a new thread will have to be moved from the ready state
			to running state. Also the previous thread will have to be unloaded to make space for the new thread.

3) 	No the program will not include switch overhead if a thread moves from ready to blocked and the queue is
			emtpy.

4) 	Yes and No the program may include switch overhead if a thread is interrupted and the queue is either emtpy or
			the thread has the highest priority. This is because once a thread is interrupted due to a time slice
			the thread has recieved its run time and is now moved the back of the queue. 



********************************
Algorithm
********************************
	The two algorithms used are first come first serve and Round Robin.
		For the first come first serve the cpu will run each thread in sequencal order based upon when
		it arrived. The cpu will run the entire thread from start to finish with no interrupts.
		For the Round Robin the cpu will give each thread smaller burst of cpu time of 100u.

********************************
Guide
********************************
	Compile
	type: make
	output: run

	Running
	type ./bin/ [args]

********************************
Assumptions
********************************
	- I'm assuming the cpu can only work on one thread at a time.
	- If no quantum is specified or an invalid number, the quantum is set to 100
	- Only one IO device