//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef DOCTOR_H_
#define DOCTOR_H_

#include "Caregiver.h"

class Doctor :public Caregiver
{
private:
	int temp_store;
	int visit = 0;
public:
	Doctor(std::string name, int skill_level) :Caregiver(name, skill_level)
	{
		treatment_time = 1 + rand() % 20;
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
		if (!high_priority.empty() || availability == false)
		{
			if (available())
			{
				it = record.find(high_priority.top().get_name());

				high_priority.top().set_start_treatment_time(clock);
				high_priority.top().set_end_treatment_time(high_priority.top().get_start_treatment(), treatment_time);
				temp_store = high_priority.top().get_end_treatment_time();

				//added this
				high_priority.top().set_visit_count(++visit);
				high_priority.top().set_visit_time(high_priority.top().get_arrival_time(), high_priority.top().get_end_treatment_time());
				total_visit_time += high_priority.top().get_visit_time();
				++num_treated;
				if (it != record.end())
				{
					it->second.update(high_priority.top().get_pri_num(), high_priority.top().get_visit_time(), name);
				}
				else
				{
					record.insert(make_pair(high_priority.top().get_name(), PatientRecord(high_priority.top().get_name(),
						high_priority.top().get_pri_num(), high_priority.top().get_visit_time(), name)));
				}
				

				high_priority.pop();
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
		else
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
	}
};
#endif