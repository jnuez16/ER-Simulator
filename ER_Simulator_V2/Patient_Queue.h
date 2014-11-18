//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef PATIENTQUEUE_H_
#define PATIENTQUEUE_H_

#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include "Random.h"
#include "Residents.h"


class Patient_Queue
{
private:
	Random rnd;
	double arrival_rate;
	//int num_served;
	//int total_wait;
	//int clock;
	std::vector<Residents> residents;
	//std::string queue_name;
	std::priority_queue<Residents> patients_high_priority;
	std::priority_queue<Residents> patients_low_priority;

public:
	Patient_Queue()
	{
		std::ifstream ss;
		ss.open("Resident_Names.txt");
		std::string sdata;
		while (!ss.eof())
		{
			ss >> sdata;
			residents.push_back(sdata);
		}
	}

	void set_arrival_rate(double arrival_rate)
	{
		this->arrival_rate = arrival_rate;
	}

	/*
	Residents front()
	{
	return patients.top();
	}

	bool empty()
	{
	return patients.empty();
	}

	void pop()
	{
	patients.pop();
	}
	*/
	
	std::priority_queue<Residents> &priority_high()
	{
		return patients_high_priority;
	}

	std::priority_queue<Residents> &priority_low()
	{
		return patients_low_priority;
	}

	void high_priority_pop()
	{
		patients_high_priority.pop();
	}
	
	void low_priority_pop()
	{
		patients_low_priority.pop();
	}

	bool empty()
	{
		return (patients_high_priority.empty() && patients_low_priority.empty());
	}
	
	void update(int clock)
	{
		int i = rand() % 2000;
		double x = rnd.next_double();
		residents[i].set_pri_num();
		if (x < arrival_rate && residents[i].get_pri_num() > 10)
		{
			
			patients_high_priority.push(Residents(residents[i], clock));
		}
		else if (x < arrival_rate && residents[i].get_pri_num() <= 10)
		{
			patients_low_priority.push(Residents(residents[i], clock));
		}

		/*std::cout << patients_q10up.size() << std::endl;
		std::cout << patients_q10down.size() << std::endl;
		if (!patients_q10up.empty())
		{
			std::string name = patients_q10up.top().get_name();
			int x = patients_q10up.top().get_pri_num();
			std::cout << clock << std::endl;
			std::cout << name << std::endl;
			std::cout << x << std::endl;
			patients_q10up.pop();
		}

		if (!patients_q10down.empty())
		{
			std::string name = patients_q10down.top().get_name();
			int x = patients_q10down.top().get_pri_num();
			std::cout << clock << std::endl;
			std::cout << name << std::endl;
			std::cout << x << std::endl;
			patients_q10down.pop();
		}*/
	}
};


#endif