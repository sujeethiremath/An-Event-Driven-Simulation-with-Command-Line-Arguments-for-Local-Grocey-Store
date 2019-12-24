1. The program accommodates anywhere from 1 to 10 registers.

2. The program reads the parameters of the simulation as command–line arguments.

3. Just as in a grocery store, grocery store customers ready to check out have to wait in line first–come, first served if no
registers are available. It is Assumed that customers ready to check out either

   (a) go the the first available register; or

   (b) if no register is available, they go to the first shortest line available.

It is assumed that customers ready to check out are routed to the grocery store’s registers bay and that registers are numbered
starting with the one closest to the registers bay entrance.

For each register, the program keeps track of the total number of transactions processed, the average transaction time,
the maximum wait line length, the average wait line length, and the average wait time. The overall values for each of these
statistic are also reported. The simulation statistics is displayed in tabular form.



Input


The program reads the parameters of the simulation as command–line arguments. The first command–line argument is
the filename of an input text file containing arrival times and transaction times. Each line of the file contains the arrival time
and required transaction time for a customer.
The second command–line argument is the number of registers R to use in the simulation, 1 ≤ R ≤ 10.
The program generates appropriate correct–use information if an incorrect number of command–line arguments are
provided.


Sample Input


The following is sample input file. The text file named simdata.txt contain the following:

        1 5
        2 5
        4 5
        20 5
        22 5
        24 5
        26 5
        28 5
        30 5
        88 3

Then typing the command “eventSim simdata.txt 1” runs the simulation on the provided data using a single register.
Likewise, the command “eventSim simdata.txt 2” runs the simulation on the provided data using a two registers.


Output


The program displays a trace of the events executed and a summary of the computed statistics for each teller and for
the single wait line. All output is sent to standard output.


Sample Output


The command “eventSim simdata.txt 1” generates the following output: 

        <<< BEGIN SIMULATION (1 registers) >>>
        Register 1 processing arrival event at time:    1   5
        Register 1 processing arrival event at time:    2   5
        Register 1 processing arrival event at time:    4   5
        Register 1 processing departure event at time:  6
        Register 1 processing departure event at time:  11
        Register 1 processing departure event at time:  16
        Register 1 processing arrival event at time:    20  5
        Register 1 processing arrival event at time:    22  5
        Register 1 processing arrival event at time:    24  5
        Register 1 processing departure event at time:  25
        Register 1 processing arrival event at time:    26  5
        Register 1 processing arrival event at time:    28  5
        Register 1 processing departure event at time:  30
        Register 1 processing arrival event at time:    30  5
        Register 1 processing departure event at time:  35
        Register 1 processing departure event at time:  40
        Register 1 processing departure event at time:  45
        Register 1 processing departure event at time:  50
        Register 1 processing arrival event at time:    88  3
        Register 1 processing departure event at time:  91
        <<< END SIMULATION >>>
        
        >>> SIMULATION STATISTICS
        
                Register number:    1   OVERALL
         Transactions processed:    10      10
       Average transaction time:    4.80    4.80
       Maximum wait line length:    2       2
       Average wait line length:    0.70    0.70
              Average wait time:    5.60    5.60
    
    
Meanwhile, the command “eventSim simdata.txt 2” generates the following output:

<<< BEGIN SIMULATION (2 registers) >>>

Register 1 processing arrival event at time: 1 5

Register 2 processing arrival event at time: 2 5

Register 1 processing arrival event at time: 4 5

Register 1 processing departure event at time: 6

Register 2 processing departure event at time: 7

Register 1 processing departure event at time: 11

Register 1 processing arrival event at time: 20 5

Register 2 processing arrival event at time: 22 5

Register 1 processing arrival event at time: 24 5

Register 1 processing departure event at time: 25

Register 1 processing arrival event at time: 26 5

Register 2 processing departure event at time: 27

Register 2 processing arrival event at time: 28 5

Register 1 processing departure event at time: 30

Register 1 processing arrival event at time: 30 5

Register 2 processing departure event at time: 33

Register 1 processing departure event at time: 35

Register 1 processing departure event at time: 40

Register 1 processing arrival event at time: 88 3

Register 1 processing departure event at time: 91

<<< END SIMULATION >>>

>>> SIMULATION STATISTICS

    Register number:            1   2   OVERALL
    
    Transactions processed:     7   3   10
    
    Average transaction time: 4.71 5.00 4.80
    
    Maximum wait line length:   0   0   0
    
    Average wait line length:   0   0   0
    
    Average wait time:         1.71 0   1.20
    
Notice the improvement in wait times by simply opening up a second register.
