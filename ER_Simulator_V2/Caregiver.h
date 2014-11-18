//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef CAREGIVER_H_
#define CAREGIVER_H_

#include <string>
#include <fstream>
#include <queue>
#include <map>
#include "Residents.h"
#include "Record.h"

class Caregiver
{
protected:
	std::string name;
	int skill_level;
	int treatment_time;
	bool availability;
	int total_visit_time = 0;
	int num_treated = 0;
	std::map<std::string, PatientRecord>::iterator it;
public:
	std::map<std::string, PatientRecord> record;
	Caregiver(std::string name, int skill_level) : name(name), skill_level(skill_level), availability(true){}
	virtual bool available() = 0;
	virtual void update(int clock, std::priority_queue<Residents> &high_priority, std::priority_queue<Residents> &low_priority,
		std::map<std::string, PatientRecord> &record) = 0;//changed constructor to inlclude map 
	int get_total_visit_time()
	{
		return total_visit_time;
	}
	int get_num_treated()
	{
		return num_treated;
	}
	std::string getName()
	{
		return name;
	}
	
};

#endif