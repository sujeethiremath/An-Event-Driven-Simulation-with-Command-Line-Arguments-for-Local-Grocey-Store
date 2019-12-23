    #include "Event.h"
    #include "Register.h"
    #include<algorithm>
    using namespace std;

    typedef priority_queue<Event,vector<Event>,greater<vector<Event>::value_type>> eventList;
    typedef queue<Event> registerQueue;

    vector<string> split( const string& s , char delimiter )
    {
        vector<string> tokens;          // vector of tokens
        string token;                   // a single token
          istringstream tokenStream(s);   // an input string stream
                // Tokenize s by grabbing individual tokens
        while( getline( tokenStream , token , delimiter ) )
        tokens.push_back(token);    // add found token

        return tokens;
    }

    //function to processing arrival events
    void processArrival(eventList &eventListPQueue ,  vector<Register>  &vRegister,  double &totalDepartTime, double &totalTransactTime, double &arrivalTime, vector<registerQueue> &vRegisterQueue)
    {
        Event currentEvent(eventListPQueue.top());
        eventListPQueue.pop();
        int RegisterIndex = -1;
        unsigned currentTime = currentEvent.getTime();
        unsigned currentDuration =  currentEvent.getDuration();
        arrivalTime += currentTime;

        for(unsigned i=0; i<vRegister.size();i++)
        {
            if(vRegister[i].getRegisterAvailability()==true)  //finding the next available Register in the vector
            {
                RegisterIndex = i;
                break;
            }
        }
        if( RegisterIndex != -1  &&  vRegisterQueue[RegisterIndex].empty() == true )
        {
            cout<<"Register";
            cout<<setw(3)<< RegisterIndex+1<<" ";
            cout<<"processing";
            cout<<setw(10);
            cout<<"arrival";
            cout<<" event at time:";
            cout<<setw(5);
            cout<<currentEvent.getTime();
            cout<<setw(5)<<currentEvent.getDuration()<<endl;

            unsigned departureTime = currentTime + currentDuration; //calculating departure event time
            totalDepartTime += departureTime; //keeping record of total departure time
            totalTransactTime += currentDuration; //keeping track of total transaction time
            Event newDepartureEvent(Event::departure, departureTime, 0, RegisterIndex);  //creating new departure event object with previously calculated departure time
            eventListPQueue.push(newDepartureEvent); //inserting departure event back into eventList priority queue
            vRegister[RegisterIndex].setRegisterAvailability(false); //setting register availability to false
            vRegister[RegisterIndex].addTransactionProcessed(); //keeping track of transactions processed by one particular register
            vRegister[RegisterIndex].addTotalDepartureTime(departureTime);
            vRegister[RegisterIndex].addToTotalTransactionTime(currentDuration);
            vRegister[RegisterIndex].addTotalArrivalTime(currentTime);
        }
        else if( RegisterIndex == -1)
        {
            vector<unsigned> sizes;
            for(unsigned i=0; i<vRegisterQueue.size();i++)
            {
                sizes.push_back(vRegisterQueue[i].size());
            }

            unsigned x=sizes[0], indexR=0;

            for(unsigned j=1; j<sizes.size();j++)  //loop to find register with minimum queue length
            {
                if(x>sizes[j])
                {
                    x = sizes[j];
                    indexR = j;
                }
            }

                      cout<<"Register";
                       cout<<setw(3)<< indexR+1<<" ";
                       cout<<"processing";
                       cout<<setw(10);
                       cout<<"arrival";
                       cout<<" event at time:";
                       cout<<setw(5);
                       cout<<currentEvent.getTime();
                       cout<<setw(5)<<currentEvent.getDuration()<<endl;

            registerQueue &rQ = (vRegisterQueue[indexR]); //adding to the queue of particular register
            rQ.push(currentEvent);
            vRegister[indexR].addTotalArrivalTime(currentTime);

        }


    }

    //Processes departure events
    void processDeparture(eventList &eventListPQueue ,  vector<Register>  &vRegister, double &totalDepartTime, double &totalTransactTime,vector<registerQueue> &vRegisterQueue)
    {
        Event currentEvent(eventListPQueue.top());
        eventListPQueue.pop();
        int servedByRegisterIndex = currentEvent.getServedByRegisterIndex();

        cout<<"Register";
        cout<<setw(3)<< servedByRegisterIndex+1<<" ";  //printing the number of the Register
        cout<<"processing departure event at time:";
        cout<<setw(5);
        cout<<currentEvent.getTime()<<endl;

        vRegister[servedByRegisterIndex].setRegisterAvailability(true);
        double sizeOfQueue = vRegisterQueue[servedByRegisterIndex].size();
        vRegister[servedByRegisterIndex].addToWaitLine(sizeOfQueue);

        if(vRegisterQueue[servedByRegisterIndex].empty() == false)  //if queue is not empty processing the event in the queue
        {
            Event customer(vRegisterQueue[servedByRegisterIndex].front());
            vRegisterQueue[servedByRegisterIndex].pop();
            unsigned departureTime = currentEvent.getTime() + customer.getDuration();
            totalDepartTime += departureTime;
            totalTransactTime += customer.getDuration();
            Event newDepartureEvent(Event::departure, departureTime, 0, servedByRegisterIndex);  //creating departure event
            eventListPQueue.push(newDepartureEvent);
            vRegister[servedByRegisterIndex].setRegisterAvailability(false); //setting the availability for particular Register to false
            vRegister[servedByRegisterIndex].addTransactionProcessed();
            vRegister[servedByRegisterIndex].addToTotalTransactionTime(customer.getDuration());
             vRegister[servedByRegisterIndex].addTotalDepartureTime(departureTime);
        }


    }


    int main(int argc, char* argv[])
    {


        string fileName,input;
        unsigned noOfRegisters;
        char delimiter = ' ';
        vector<string> inputFileNames,listOfTokens;
        ifstream eventFile;
        double totalDepartTime = 0, totalTransactTime = 0, arrivalTime=0;
        int eTime,eDuration;
        eventList eventListPQueue;
        vector<registerQueue> vRegisterQueue;
        vector<Register>  vRegister;  //vector of Register objects

        //cin>>fileName;
        //cin>>noOfRegisters;

        if(argc>1) //if multiple arguments passed then only initialize the variables
        {
            fileName = argv[1];
            noOfRegisters = stoi(argv[2]);

        }
        else  //printing message if just one argument is passed
        {
            cout<<"Correct usage: eventSim filename count"<<endl;
            cout<<setw(20)<<"where";
            cout<<" filename is the simulation data filename; and"<<endl;
            cout<<setw(26);
            cout<<"count";
            cout<<" is the number of registers (1..10) to use."<<endl<<endl;
            return 1;
        }
        if(noOfRegisters>10)  //printing the message if number of Registers crosses the limit 10
        {
            cout<<"Correct usage: bankSim filename count"<<endl;
            cout<<setw(20)<<"where";
            cout<<" filename is the simulation data filename; and"<<endl;
            cout<<setw(26);
            cout<<"count";
            cout<<" is the number of Registers (1..10) to use."<<endl<<endl;
            return 1;

        }
        for(unsigned i=0;i<noOfRegisters;i++)  //inserting Register objects into the vector
        {
            Register T;
            vRegister.push_back(T);
            registerQueue rQ;
            vRegisterQueue.push_back(rQ);
        }

        eventFile.open(fileName);

        if(eventFile.is_open())
        {
            while(getline(eventFile, input))
            {
                listOfTokens = split( input , delimiter );

                for(unsigned j=0;j<listOfTokens.size();j++)
                {
                    if(j%2==0)
                    eTime = stoi(listOfTokens[j]);
                    else
                    {
                        eDuration = stoi(listOfTokens[j]);
                        Event E(Event::arrival,eTime,eDuration); //creating event object
                        eventListPQueue.push(E); //inserting event object into priority queue which sorted according to eTime
                    }
                }
            }

            eventFile.close();
        }
        else
        {
            cout<<"Error opening File"<<endl;
        }

        cout<<"<<< BEGIN SIMULATION ("<<noOfRegisters<<" registers) >>>"<<endl;
        while(eventListPQueue.empty()==false)
        {
            if(eventListPQueue.top().getType() == Event::arrival)
            processArrival( eventListPQueue  , vRegister,  totalDepartTime, totalTransactTime, arrivalTime, vRegisterQueue);  //function to process arrival events
            else
            processDeparture( eventListPQueue  , vRegister,  totalDepartTime, totalTransactTime, vRegisterQueue );  //function to process departure events
        }
        cout<<"<<< END SIMULATION >>>"<<endl<<endl;
        cout<<">>> SIMULATION STATISTICS"<<endl<<endl;

        cout<<setw(17)<<"Register"<<right;
        cout<<" number:";

        for(unsigned i=1; i<=noOfRegisters; i++)
        {
            cout<<setw(8)<<i;  //printing numbers of the Registers
        }

        cout<<setw(4)<<"O";
        cout<<"VERALL";
        cout<<endl;
        cout<<setw(14)<<"Transactions";
        cout<<" processed:";

        unsigned num=0;
        for(unsigned j=0;j<vRegister.size();j++)
        {
            cout<<setw(8)<<right<<vRegister[j].getTransactionsProcessed();  //printing the number of transactions done by single Register
            num = num + vRegister[j].getTransactionsProcessed();
        }

        cout<<setw(10)<<num<<endl;
        cout<<setw(7)<<"Average";
        cout<<" transaction time:";

        double addition=0;
        for(unsigned k=0;k<vRegister.size();k++)
        {
            cout << fixed << showpoint;
            cout<<setw(8)<<setprecision(2)<<right<<vRegister[k].getAvgTransactionTime();  //printing the average transaction time
            addition = addition + vRegister[k].gettotalTransactionTime();
        }

        double averageofTrans = addition/num;
        cout << fixed << showpoint;
        cout<<setw(6)<<"    "<<setprecision(2)<<averageofTrans<<endl;

        cout<<setw(7)<<"Maximum";
        cout<<" wait line length:";

        vector<unsigned> overallMaxWait; //vector to store wait line lengths of all queues front of registers
        for(unsigned i=0; i<vRegister.size();i++)
        {
             cout<<setw(8)<<vRegister[i].getMaxWaitLine();
            overallMaxWait.push_back(vRegister[i].getMaxWaitLine());
        }

        cout<<setw(10)<<unsigned(*max_element(overallMaxWait.begin(), overallMaxWait.end())); //finding the maximum among the wait line

        cout<<endl;
        cout<<setw(7)<<"Average";
        cout<<" wait line length:";

        for(unsigned j=0; j<vRegister.size();j++)
         {
              cout<<setw(8)<<setprecision(2)<<vRegister[j].getAvgWaitLine();
          }

          double totalAWL=0;
          for(unsigned g=0; g<vRegister.size();g++)
          {
              totalAWL = totalAWL + vRegister[g].getTotalWaitLineLength();
          }

          cout<<setw(10)<<setprecision(2)<<(totalAWL/num);


        cout<<endl;
        cout<<setw(14)<<"Average";
        cout<<" wait time:";

        for(unsigned r=0; r<vRegister.size();r++)
        {
            cout<<setw(8)<<setprecision(2)<<(vRegister[r].getTotalDepartTime() - vRegister[r].gettotalTransactionTime() - vRegister[r].getTotalArrivalTime())/(vRegister[r].getTransactionsProcessed());
        }

        cout << fixed << showpoint;
        cout<<setw(10)<<setprecision(2)<<(totalDepartTime - totalTransactTime - arrivalTime)/num;
        cout<<endl<<endl;
        return 0;
    }
