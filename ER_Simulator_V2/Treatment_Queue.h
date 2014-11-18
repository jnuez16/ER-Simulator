//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef TREATMENTQUEUE_H_
#define TREATMENTQUEUE_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "Patient_Queue.h"
#include "Caregiver.h"
#include "Doctor.h"
#include "Nurse.h"

class Treatment_Queue
{
private:
	Patient_Queue* patient; //creates a priority queue for patients
	std::vector<Caregiver*> caregiver;
	int num_doc;
	int num_nurse;
	int num_served = 0;
	std::map<std::string, PatientRecord> record;
	
public:
	

	Treatment_Queue(double arrival_rate, int num_doc, int doc_skill, int num_nurse, int nurse_skill)
	{
		this->num_doc = num_doc;
		this->num_nurse = num_nurse;
		//Inputs in doctors and nurses names from a text file
		
		

		
		

		patient = new Patient_Queue();
		patient->set_arrival_rate(arrival_rate);
		setNurseName(num_nurse, nurse_skill);
		setDocName(num_doc, doc_skill);
		
	}
	std::map<std::string, PatientRecord> &rrecord()
	{
		return record;
	}
	
	void setNurseName(int num_nurse, int nurse_skill)
	{
		std::ifstream snur;
		snur.open("Nurse_Names.txt");
		std::string sndata;

		for (int i = 0; i < num_nurse; i++) //creates Nurses based on the user input
		{
			std::getline(snur, sndata);
			caregiver.push_back(new Nurse(sndata, nurse_skill));
		}

	}

	std::vector<Caregiver*> getCaregiverName()
	{
		return caregiver;
	}

	void setDocName(int num_doc, int doc_skill)
	{
		std::ifstream sdoc;
		sdoc.open("Doctor_Names.txt");
		std::string sddata;

		for (int i = 0; i < num_doc; i++) //creates Doctors based on the user input
		{
			std::getline(sdoc, sddata);
			caregiver.push_back(new Doctor(sddata, doc_skill));
		}
	}

	int total_visit_time()
	{
		int total_visit_time = 0;
		for (int i = 0; i < num_doc + num_nurse; i++)
		{
			total_visit_time += caregiver[i]->get_total_visit_time();
		}

		return total_visit_time;
	}

	int get_num_served()
	{
		for (int i = 0; i < num_doc + num_nurse; i++)
		{
			num_served += caregiver[i]->get_num_treated();
		}

		return num_served;
	}

	void update(int clock)
	{
		//updates the Patient_Queue
		patient->update(clock);

		if (!patient->empty())
		{
			for (int i = 0; i < num_doc + num_nurse; i++)
			{
				caregiver[i]->update(clock, patient->priority_high(), patient->priority_low(), record);
			}
		}
		
		//
		//
		//if(!patient->empty()) //Note to self: create empty function in the Patient_Queue
		//{
		//	
		//	if(patient priority number is greater than 10) //Note to self: create a front function in the Patient_Queue
		//	{
		//		for(int i = 0; i < num_doc; i++)
		//		{
		//			if doctor is available
		//			{
		//				doctor updates by taking in clock and patient //Note to self: create an update function for doctor class
		//				update patient's start treatment time
		//				update patient's end_treatment time
		//				Insert name and value in the map
		//				if(a random integer = a value)
		//				{
		//					set patient priority number at random //Note to self: create a set priority number in the Patient_Queue
		//				}
		//				else
		//					pop the patient out //Note to self: create a pop function in the Patient_Queue
		//			}
		//		}
		//	}
		//	if(patient priority number is less than or equal to 10)
		//	{
		//		for(int i = 0; i < num_doc; i++)
		//		{
		//			if doctor is available
		//			{
		//				doctor updates by taking in clock and patient //Note to self: create an update function for doctor class
		//				update patient's start treatment time
		//				update patient's end_treatment time
		//				Insert name and value in the map
		//				if(a random integer = a value)
		//				{
		//					set patient priority number at random //Note to self: create a set priority number in the Patient_Queue
		//				}
		//				else
		//					pop the patient out //Note to self: create a pop function in the Patient_Queue
		//			}
		//		}

		//		for(int i = 0; i < num_nurse; i++)
		//		{
		//			if nurse is available
		//			{
		//				nurse updates by taking in clock and patient
		//				update patient's start treatment time
		//				update patient's end_treatment time
		//				Insert name an value in the map
		//				if( a random integer = a value) //take count on how many times the patient have been treated.
		//					set patient priority number at random
		//				else
		//					pop the patient out
		//			}
		//		}
		//	}
		//}
	}
};

#endif