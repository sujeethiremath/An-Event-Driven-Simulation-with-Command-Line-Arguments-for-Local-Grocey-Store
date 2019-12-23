

#ifndef EVENT_H_
#define EVENT_H_

    #include<iomanip>
    #include<iostream>
    #include<queue>
    #include<fstream>
    #include<string>
    #include<sstream>
    #include<vector>

using namespace std;

class Event
{

  public:

    enum eventType { departure, undefined , arrival   };

    // Creates an undefined event
    Event( );
    // Creates an event of a given type, occurance time, and duration
    Event( eventType type , unsigned time , unsigned duration=0, int servedRegisterNo = -1 );
    // Copy constructor
    Event( const Event& otherEvent );

    // Determines the type of the event
    eventType getType() const;

    // Determines the time of the event
    unsigned getTime() const;

    // Determines the duration of the (arrival) event
    unsigned getDuration() const;

    int getServedByRegisterIndex() const;

    // Events are ordered by their event time (occurance)
    friend bool operator<( const Event& lhs , const Event& rhs );
    friend bool operator>( const Event& lhs , const Event& rhs );

  private:

    eventType eType;      // type of event
    unsigned  eTime;      // time of event occurance
    unsigned  eDuration;  // duration, if event is an arrival event
    int servedByRegister; //Served by Register

};
//#include "Event.cpp"
#endif
