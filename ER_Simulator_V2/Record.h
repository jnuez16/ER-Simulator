#ifndef RECORD_H_
#define RECORD_H_

#include <string>
#include <vector>

struct PatientRecord {
	std::string name; 
	std::string caregiver_name;
	std::vector<int> pri_nums;
	std::vector<int> treatment_times;
	std::vector<std::string> caregiver_names;
	int avg_time;
	int pulse;// if we do dead or alive
	int num_visits = 0;
	

	PatientRecord(std::string name, int pri_num, int treatment_time, std::string caregiver_name) 
	{
		this->name = name;
		pri_nums.push_back(pri_num);
		treatment_times.push_back(treatment_time);
		caregiver_names.push_back(caregiver_name);
		num_visits++;
	}

	void update(int pri_num, int treatment_time, std::string caregiver_name)
	{
		pri_nums.push_back(pri_num);
		treatment_times.push_back(treatment_time);
		caregiver_names.push_back(caregiver_name);
		num_visits++;
	}

};

#endif