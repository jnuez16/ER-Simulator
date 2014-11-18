//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef NURSE_H_
#define NURSE_H_

#include "Caregiver.h"

class Nurse : public Caregiver
{
private:
	int temp_store;
	int visit = 0;
public:
	Nurse(std::string name, int skill_level) :Caregiver(name, skill_level)
	{
		treatment_time = 1 + rand() % 10;
		availability = true;
	}

	std::string getName()
	{
		return name;
	}

	bool available()
	{
		return availability;
	}

	

	void update(int clock, std::priority_queue<Residents> &high_priority, std::priority_queue<Residents> &low_priority, std::map<std::string, PatientRecord> &record)
	{
		if (!low_priority.empty() || availability == false)
		{
			if (available())
			{
				it = record.find(low_priority.top().get_name());

				low_priority.top().set_start_treatment_time(clock);
				low_priority.top().set_end_treatment_time(low_priority.top().get_start_treatment(), treatment_time);
				temp_store = low_priority.top().get_end_treatment_time();

				//added this
				low_priority.top().set_visit_count(++visit);
				low_priority.top().set_visit_time(low_priority.top().get_arrival_time(), low_priority.top().get_end_treatment_time());
				total_visit_time += low_priority.top().get_visit_time();
				++num_treated;
				if (it != record.end())
				{
					it->second.update(low_priority.top().get_pri_num(), low_priority.top().get_visit_time(), name);
				}
				else
				{
					record.insert(make_pair(low_priority.top().get_name(), PatientRecord(low_priority.top().get_name(),
						low_priority.top().get_pri_num(), low_priority.top().get_visit_time(), name)));
				}

				low_priority.pop();
				availability = false;
			}
			else
			{
				if (temp_store == clock)
				{
					availability = true;
				}
			}
		}
	}
};


#endif