	#include "Register.h"

	//constructor to initialize the data items
	Register :: Register()
	{
		RegisterAvailability = true;
		transactionsProcessed = 0;
		totalTransactionTime = 0;
		totalDepartureTime = 0;
		totalArrivalTime = 0;
	}

	//sets the status of the Register availability
	void Register :: setRegisterAvailability( bool availability)
	{
		RegisterAvailability = availability;
	}

//function returns total departure time
	double Register:: getTotalDepartTime()
	{
		return totalDepartureTime;
	}

//function to return total arrival time
	double Register :: getTotalArrivalTime()
	{
		return totalArrivalTime;
	}

//function to set departure times
 	void Register :: addTotalDepartureTime(double ATD)
	{
		totalDepartureTime = totalDepartureTime + ATD; 
	}

//function to set arrival times 
	void Register :: addTotalArrivalTime(double ATAT)
	{
		totalArrivalTime = totalArrivalTime + ATAT;
	}

	//function to insert value into the wait line vector 
	void Register :: addToWaitLine(double sizenumber)
	{
		if(sizenumber > 0)
		{
			waitLine.push_back((sizenumber-1));
		}
		else
		{
			waitLine.push_back(sizenumber);
		}
	}

	//function to return maximum value of queue size
	unsigned Register ::  getMaxWaitLine()
	{
		return unsigned(*max_element(waitLine.begin(), waitLine.end()));
	}

	//function returns the average wait line length 
	double Register :: getAvgWaitLine()
	{
		double temp = 0;
		for(unsigned i=0; i<waitLine.size();i++)
		{
			temp = temp + waitLine[i];
		}

		return (temp/getTransactionsProcessed());

	}

	//adds the transaction to the total transactions
	void Register :: addTransactionProcessed()
	{
		transactionsProcessed = transactionsProcessed + 1;
	}

	double Register :: getTotalWaitLineLength()
	{
		double result = 0;
		for(unsigned i=0; i<waitLine.size();i++)
		{
			result = result + waitLine[i];
		}

		return result;
	}

	//adds the time of the transactions to the total transaction time
	void Register :: addToTotalTransactionTime( double Time)
	{
		totalTransactionTime = totalTransactionTime + Time;
	}

	//returns the bool value of the Register availability
	bool Register :: getRegisterAvailability() const 
	{
		return RegisterAvailability;
	}

	//returns number of transactions processed by the Register
	unsigned Register :: getTransactionsProcessed() const
	{
		return transactionsProcessed;
	}

	//returns the total transaction time
	int Register :: gettotalTransactionTime() const
	{
		return totalTransactionTime;
	}

	//returns the average of the transaction time 
	double Register :: getAvgTransactionTime() const
	{
		return (totalTransactionTime/transactionsProcessed);
	}
