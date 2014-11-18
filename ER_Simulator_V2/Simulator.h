//Group Name: Midnight Company
//Members: Joshua Nuez and Joshua Vinton
//Project: Emergency Room Simulator

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <ios>
#include <limits>
#include <vector>
#include <utility>
#include "Treatment_Queue.h"

class Simulator
{
private:
	Treatment_Queue* treatment_queue;
	int total_time = 7 * 24 * 60; //simulating a week of the ER
	int clock; //Keeps track of time the ER has been running
	std::map<std::string, PatientRecord>::iterator it;
	double average_visit_time;
	int num_doc;
	int num_nurse;
	

	int read_int(const std::string prompt) // function to process user input
	{
		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true)
		{
			try
			{
				std::cout << prompt;
				std::cin >> num;
				std::cout << std::endl;
				return num;
			}
			catch (std::ios_base::failure)
			{
				std::cout << "Bad numberic string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:
	Simulator()
	{
		std::cout << "Welcome to the Midnight Company Emergency Room Simulator. \n\n";
		std::cout << "We are the CS273ville ER, a ghastly home for the almost dying!\n";
		std::cout << "Remember to pick up your dead body on the way out.\n\n";
		
	}

	void enter_data() //function that takes the user input and initializes a queue
	{
		int rate = read_int("Please enter the patients arrival rate (patients/hour): ");
		double arrival_rate = rate / 60.0;
		num_doc = read_int("Please enter the number of doctors on duty: ");
		int doc_skill = read_int("Please enter doctor's skill lvl (1-10): ");
		num_nurse = read_int("Please enter the number of nurses on duty: ");
		int nurse_skill = read_int("Please enter nurse's skill lvl (1=10): ");

		treatment_queue = new Treatment_Queue(arrival_rate, num_doc, doc_skill, num_nurse, nurse_skill);
	}

	void start_treatment()
	{
		
		
			
		for (clock = 0; clock < total_time; clock++)
		{
			treatment_queue->update(clock);
		}

		average_visit_time = treatment_queue->total_visit_time() / treatment_queue->get_num_served();
		std::cout << "Total Number of Patients: " << treatment_queue->get_num_served() << std::endl;
		std::cout << "Total Visit Time: " << treatment_queue->total_visit_time() << std::endl;
		std::cout << "Average Visitation Time: " << average_visit_time << std::endl;

	}

	void menu()
	{
		std::string name;
		int choice;
		do
		{
			std::cout << "Choose from the following actions.\n";
			std::cout << "\t(1) List Treated Residents\n";
			std::cout << "\t(2) Search Resident by Name\n";
			std::cout << "\t(3) List Doctors on duty\n";
			std::cout << "\t(4) List Nurses on duty\n";
			std::cout << "\t(5) Quit\n";

			choice = read_int("Enter choice: ");

			switch (choice)
			{
			case 1:
				std::cout << "Here are the list of treated residents.\n";
				for (std::map<std::string, PatientRecord>::iterator it = treatment_queue->rrecord().begin(); it != treatment_queue->rrecord().end(); ++it)
				{
					std::cout << it->first << std::endl;
				}
				break;
			case 2:
				std::cout << "Input resident name to search: ";
				std::cin >> name;

				it = treatment_queue->rrecord().find(name);
				
				if (it != treatment_queue->rrecord().end())
				{
					std::cout << it->first << std::endl;
					PatientRecord obj = it->second;
					std::cout << "\tInjury Severity: " << std::endl;
					for (int i = 0; i < obj.pri_nums.size(); i++)
					{
						std::cout << obj.pri_nums[i] << std::endl;
					}
					std::cout << "\tVisit Times: " << std::endl;
					for (int i = 0; i < obj.treatment_times.size(); i++)
					{
						std::cout << obj.treatment_times[i] << std::endl;
					}
					std::cout << "\tCaregivers: " << std::endl;
					for (int i = 0; i < obj.caregiver_names.size(); i++)
					{
						std::cout << obj.caregiver_names[i] << std::endl;
					}
					std::cout << "\tNumber of Visits: " << obj.num_visits << std::endl;
				}
					
				//Note to self: create a record class that records the key(name) and values.
				//search through the record for the resident
				break;
			case 3:
				std::cout << "Here are the list of Doctors on duty.\n";
				for (int i = num_nurse; i < num_nurse + num_doc; i++)
				{
					std::cout << "\t" << treatment_queue->getCaregiverName()[i]->getName() << std::endl;
				}
				std::cout << std::endl;
				//Display the names of the doctors and the number of patients they treated.
				break;
			case 4:
				std::cout << "Here are the list of Nurses on duty.\n";
				for (int i = 0; i < num_nurse; i++)
				{
					std::cout << "\t" << treatment_queue->getCaregiverName()[i]->getName() << std::endl;
				}
				std::cout << std::endl;
				//Display the names of the nurses and the number of patients they treated.
				break;
			case 5:
				break;
			default:
				std::cout << "Invalid input\n";
				break;


			}
		} while (choice != 5);
		
	}
};

#endif