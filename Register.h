	#ifndef REGISTER_H_
		#define REGISTER_H_
		#include<algorithm>
		using namespace std;

		class Register{
			private:
			//varable to hold the availability status of Register
			bool RegisterAvailability;

			//variable to hold the number of transactions processed by Register
			unsigned transactionsProcessed;

			//variable to hold the total transaction time for the Register
			double totalTransactionTime;

			//vector of double to hold the values of sizes of queues to calculate average wait line length
			vector<double> waitLine;

			//variable to keep track of total departure event time for the performed transactions
			double totalDepartureTime;

			//variable to hold total arrival time of all the events performed by register
			double totalArrivalTime;


			public:
			//constructor to initialize the data items
			Register();

			//function to set departure times
			void addTotalDepartureTime(double ATD);

			//function returns total departure time
			double getTotalDepartTime();

			//function to insert value into the wait line vector 
			void addToWaitLine(double sizenumber);

			//function to set arrival times 
			void addTotalArrivalTime(double ATAT);

			//function to return total arrival time
			double getTotalArrivalTime();

			//function to return maximum value of queue size
			unsigned getMaxWaitLine();
			
			//function returns the average wait line length 
			double getAvgWaitLine();

			//function to return total wait line length
			double getTotalWaitLineLength();

			//returns the bool value of the Register availability
			bool getRegisterAvailability() const;

			//returns number of transactions processed by the Register
			unsigned getTransactionsProcessed() const;

			//returns the total transaction time 
			int gettotalTransactionTime() const;

			//returns the average of the transaction time 
			double getAvgTransactionTime() const;

			//sets the status of the Register availability
			void setRegisterAvailability( bool availability);

			//adds the transaction to the total transactions
			void addTransactionProcessed();

			//adds the time of the transactions to the total transaction time
			void addToTotalTransactionTime( double Time);

		};

		//#include "Register.cpp"
	#endif
