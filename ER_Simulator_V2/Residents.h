//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef RESIDENTS_H_
#define RESIDENTS_H_


#include <string>
#include "Random.h"

class Residents
{
private:
	std::string name;
	int pri_num;
	int arrival_time;
	bool alive;
	int start_treatment_time;

	int end_treatment_time;
	int visit_time;
	int visit_count = 0;
public:
	Residents(std::string name) //initializing a vector
	{
		this->name = name;
		alive = true;
		set_pri_num();
	}

	Residents(Residents &resident, int clock) //initializing priority queues
	{
		this->arrival_time = clock;
		name = resident.get_name();
		alive = resident.is_alive();
		pri_num = resident.get_pri_num();
	}
	void set_pri_num()
	{
		pri_num = 1 + rand() % 20;
	}

	int rand_num()
	{
		
		int x = 1 + rand() % 20;
		return x;
	}

	std::string get_name()
	{
		return name;
	}

	void set_alive(bool alive)
	{
		this->alive = alive;
	}

	bool is_alive()
	{
		return alive;
	}

	int get_pri_num()
	{
		return pri_num;
	}

	void set_start_treatment_time(int clock)
	{
		start_treatment_time = clock;
	}

	int get_start_treatment()
	{
		return start_treatment_time;
	}

	void set_end_treatment_time(int start_treatment_time, int treatment_time)
	{
		end_treatment_time = start_treatment_time + treatment_time;
	}

	int get_end_treatment_time()
	{
		return end_treatment_time;
	}

	void set_visit_time(int arrival_time, int end_treatment_time)
	{
		visit_time = end_treatment_time - arrival_time;
	}

	int get_visit_time()
	{
		return visit_time;
	}

	void set_visit_count(int visit_count)
	{
		this->visit_count = visit_count;
	}

	int get_visit_count()
	{
		return visit_count;
	}

	bool operator<(const Residents &op) const
	{
 		return pri_num < op.pri_num;
	}

	int get_arrival_time()
	{
		return arrival_time;
	}
};

#endif