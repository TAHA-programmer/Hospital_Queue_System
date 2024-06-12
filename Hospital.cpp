//MAIN FILE
#include<iostream>
#include<queue>
#include<string>
#include<fstream>

//STRUCTURE FOR INFORMATION OF PATIENTS
struct patients
{
	std::string name;
	double cont_no;
	double cnic;

	//CONSTRUCTOR
	patients()
	{
		name = "";
		cont_no = 0;
		cnic = 0;
	}

};

//FUNCTION HEADER
//DISPLAY MENU
void menu();

//ADD PATIENT 
void add_patient(std::queue<patients>*, int, int&);

//REMOVE PATIENT
void Remove(std::queue<patients>*, int, int&);

//BONUS TASK 

//SAVING/WRITING IN A FILE
void SaveConfig(int&, const std::string*);

//LOADING/READING IN A FILE
void LoadConfig(int&, std::string*&);

//MAIN FUNCTION
int main(int argc,char* argv[])
{
	int queue_size;
	//FOR QUEUE NAMES
	std::string* queue_nam;

	std::ifstream co("config.txt");//BONUS TASK
	if (co.good())
	{
		//LOADING FROM CONFIGURATION FILE
		LoadConfig(queue_size, queue_nam);
	}
	else
	{
		//RUNNING FOR THE FIRST TIME

		if (argc == 2)//FOR TWO ARGUMENTS WHEN COMMAND IS GIVEN
		{
			try
			{
				queue_size = std::stoi(argv[1]);
				if (queue_size <= 0)
					throw"INVALID QUEUE SIZE!";//FOR WRONG INPUT
			}
			catch (const char* msg)
			{
				std::cout << msg << std::endl;
				return 0;
			}
		}
		else
		{
			//WHEN NO ARGUMENT IS PASSED
			std::cout << "ENTER NUMBER OF QUEUES:";
			std::cin >> queue_size;
			while (queue_size <= 0)//FOR WRONG INPUT
			{
				std::cout << "INVALID QUEUE-SIZE\n";
				std::cout << "ENTER AGAIN:";
				std::cin >> queue_size;
			}
		}

		//FOR QUEUE NAMES
		queue_nam = new std::string[queue_size];

		for (int i = 0; i < queue_size; i++)
		{
			std::cout << "ENTER NAME FOR QUEUE " << i + 1 << ":";
			std::cin >> queue_nam[i];
		}

		//SAVE IN THE FILE
		SaveConfig(queue_size, queue_nam);
	}

		std::queue<patients>* q;
		q = new std::queue<patients>[queue_size];

		std::string choice;
		std::string sel_queue_nam;
		int index = -1;
		do
		{
			menu();//DISPLAYING MENU
			std::cout << "ENTER YOUR CHOICE:";
			std::cin >> choice;

			//FOR CALLING ADD FUNCTION
			if (choice == "add")
			{
				//FOR SELECTION FROM WHICH QUEUE YOU WANT DATA
				std::cout << "ENTER SELECETED QUEUE NAME:";
				std::cin >> sel_queue_nam;

				for (int i = 0; i < queue_size; i++)
				{
					if (queue_nam[i] == sel_queue_nam)
					{
						//IF YOU MATCH IT 
						index = i;
						break;
					}
					else
					{
						//IF YOU DID'NT ABLE TO MATCH IT
						index = -1;
					}
				}
				if (index != -1)
				{
					//IF YOU ABLE TO MATCH IT
					add_patient(q, queue_size, index);
					std::cout << "QUEUE WITH THE NAME " << sel_queue_nam << " FOUND" << std::endl;
				}
				else
				{
					//IF YOU DID'NT ABLE TO MATCH IT
					std::cout << "QUEUE WITH THE NAME " << sel_queue_nam << " NOT FOUND" << std::endl;
				}
			}

			//FOR CALLING REMOVE FUNCTION
			else if (choice == "remove")
			{
				//FOR SELECTION FROM WHICH QUEUE YOU WANT DATA 
				std::cout << "ENTER SELECETED QUEUE NAME:";
				std::cin >> sel_queue_nam;

				for (int i = 0; i < queue_size; i++)
				{
					if (queue_nam[i] == sel_queue_nam)
					{
						//IF YOU ABLE TO MATCH IT
						index = i;
						break;
					}
					else
					{
						//IF YOU DID'NT ABLE TO MATCH IT
						index = -1;
					}
				}
				if (index != -1 && !q[index].empty())
				{
					//IF YOU ABLE TO MATCH IT
					Remove(q, queue_size, index);
					std::cout << "REMOVED:" << std::endl;
				}
				else
				{
					//IF YOU DID'NT ABLE TO MATCH IT
					std::cout << "NOT REMOVED BECAUSE OF INVALID NAME OR EMPTINESS OF QUEUE" << std::endl;
				}
			}

			//FOR EXITING FROM THE PROGRAM
			else if (choice == "exit")
			{
				std::cout << "EXIT THE PROGRAM:" << std::endl;
				break;
			}
			else
			{
				std::cout << "INVALID CHOICE , ENTER AGAIN:" << std::endl;
			}

		} while (choice != "exit");

	//DELETING DYNAMIC MEMORY
	delete[]q;
	delete[]queue_nam;

	return 0;
}

//FUNCTION DEFINITION
//DISPLAY MENU
void menu()
{
	std::cout << "HOSPITAL QUEUE SYSTEM:" << std::endl;
	std::cout << "----------------------------" << std::endl;
	std::cout << "ADDING A PATIENT (use add):" << std::endl;
	std::cout << "REMOVING A PATIENT(use remove):" << std::endl;
	std::cout << "EXIT THE SYSTEM (use exit):" << std::endl;
	std::cout << "-----------------------------" << std::endl;
}

//ADD PATIENTS
void add_patient(std::queue<patients>* q, int queue_size, int& ind)
{
	patients p;

	std::cout << "ENTER NAME OF PATIENT:";
	std::cin >> p.name;

	std::cout << "ENTER CONTACT NUMBER:";
	std::cin >> p.cont_no;

	std::cout << "ENTER CNIC NUMBER:";
	std::cin >> p.cnic;

	q[ind].push(p);
}

//REMOVE PATIENT
void Remove(std::queue<patients>* q, int queue_size, int& ind)
{
	std::cout << "REMOVING PATIENT FROM THE QUEUE:" << std::endl;
	
	std::cout << "PATIENT NAME:" << q[ind].front().name << std::endl;
	
	std::cout << "PATIENT CONTACT NUMBER:" << q[ind].front().cont_no << std::endl;
	
	std::cout << "PATIENT CNIC NUMBER:" << q[ind].front().cnic << std::endl;

	q[ind].pop();
}

//BONUS TASK

//SAVING/WRITING IN A FILE
void SaveConfig(int& queue_size, const std::string* queue_nam)
{
	std::ofstream c("config.txt");
	if (c.is_open())
	{
		c << queue_size << std::endl;
		for (int i = 0; i < queue_size; i++)
			c << queue_nam[i] << std::endl;
		c.close();
	}
	else
		std::cout << "CONFIGURATION FILE NOT OPENED:" << std::endl;
}

//LOADING/WRITING FROM A FILE
void LoadConfig(int& queue_size,  std::string*& queue_nam)
{
	std::ifstream co("config.txt");
	if (co.is_open())
	{
		co >> queue_size;
		queue_nam = new std::string[queue_size];
		for (int i = 0; i < queue_size; i++)
			co >> queue_nam[i];
		co.close();
	}
	else
		std::cout << "CONFIGURATION FILE NOT OPENED" << std::endl;
}