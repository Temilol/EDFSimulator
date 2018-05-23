#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
ofstream outputFile;

struct pros
{
	string name;
	int arrival, execution, deadline, time;
};

struct tpros
{
	string temp_name;
	int temp_arrival, temp_execution, temp_deadline, temp_time;
};

bool compareByArrivalTime(const pros &a, const pros &b) {
	return a.arrival < b.arrival;
}

bool compareByDeadline(const pros &a, const pros &b) {
	return (a.arrival == b.arrival) && (a.deadline < b.deadline);
}

int total(vector<pros> &a) {
	int ttotal_burst = 0;
	for (int i = 0; i < a.size(); i++) {
		ttotal_burst += a[i].execution;
	}
	return ttotal_burst;
}

int reOrder(vector<pros> &process, const int &total_burst) {
	ofstream outputFile;
	bool found;
	int turnaround, total_turnaround = 0;

	outputFile.open("Temilola_EDF_Simulation.txt");
	outputFile << "\t\t\t\tREPORT" << endl;
	outputFile << "\t\t-----------------------------------------" << endl;
	for (int i = 0; i < total_burst + 1; i++) {
		vector<tpros>tprocess; //create a temporary process
		outputFile << endl;
		outputFile << "At Time " << i << endl;
		found = false;
		for (int j = 0; j < process.size(); j++) {
			if ((process[j].arrival <= i) && (process[j].execution > 0)) { //The job is within range of the arrival time
				if (process[j].time >= 0) {
					process[j].time -= 1; //decreament the time before deadline if its not yet zero
				}
				//store the values in a temporary vector
				tpros temp = { process[j].name, process[j].arrival, process[j].execution, process[j].deadline, process[j].time };
				tprocess.push_back(temp);
				found = true;
			}
		}
		if (found) {
			//Jobs in the memory
			outputFile << endl;
			outputFile << "The Jobs currently in memory " << "at time " << i << endl;
			for (int i = 0; i < tprocess.size(); i++)
			{
				outputFile << "Job " + tprocess[i].temp_name + " has an execution time of " << tprocess[i].temp_execution << " and time before its deadline is " << tprocess[i].temp_time + 1 << endl;
			}

			//Find the job with the smallest time before deadline
			int smallest = tprocess[0].temp_time, index = 0;
			for (int k = 1; k < tprocess.size(); k++) {
				if (tprocess[k].temp_time < smallest) {
					smallest = tprocess[k].temp_time;
					index = k;
				}
			}

			//Search the whole process for the already found smallest job
			string search = tprocess[index].temp_name;
			for (int j = 0; j < process.size(); j++) {
				if (process[j].name == search) {
					process[j].execution -= 1; //decrease the execution time
					if (process[j].execution == 0) { //Then the job has ended
						outputFile << endl;
						outputFile << "Job " + process[j].name << " has ended its process at time " << i+1 << endl;
						//If the job has ended then you can calculate the turnaround of the job
						turnaround = (i + 1) - process[j].arrival;
						total_turnaround += turnaround;
					}
					if ((process[j].time == 0) && process[j].execution != 0) {//The deadline has been execeeded
						outputFile << endl;
						outputFile << "Job " + process[j].name << " has gotten to its deadline but it has not finished executing" << endl;
					}
					break;
				}
			}
		}
		tprocess.clear(); //reset the temporay process
	}
	return total_turnaround;
}

int main() {
	int amount, tarrival, texecution, tdeadline, ttime, total_burst, total_turn_around;
	double average_turnaround;
	string tname;
	vector<pros>process;
	cout << "How many process would you like to schedule (The jobs should be greater than 0): ";
	cin >> amount;

	//Get the job details
	if (amount > 0)
	{
		for (int i = 0; i < amount; i++)
		{
			cout << "What is the job name ";
			cin >> tname;
			cout << "What is the job arrival time ";
			cin >> tarrival;
			cout << "What is the execution time ";
			cin >> texecution;
			cout << "When is the job Deadline ";
			cin >> tdeadline;
			/* cout << "How long does the job have before deadline ";
			cin >> ttime; */
			ttime = tdeadline - tarrival;
			pros temp = { tname, tarrival, texecution, tdeadline, ttime };

			process.push_back(temp);

			cout << endl;
		}

		//sort the job according to the arrival time
		sort(process.begin(), process.end(), compareByArrivalTime);
		//sort the jobs that arrive at the same time according to their deadline
		sort(process.begin(), process.end(), compareByDeadline);
		//calculate total execution time of all the jobs
		total_burst = total(process);

		total_turn_around = reOrder(process, total_burst);
		average_turnaround = total_turn_around / static_cast<float>(amount);
		//cout << endl;
		outputFile << "The average turn around time is " << average_turnaround << endl;
		cout << "The average turn around time is " << average_turnaround << endl;
		cout << "The timeline of your job has been saved into a file named Temilola_EDF_Simulation.txt" << endl;
		outputFile.close();
	}
	else
	{
		cout << "You entered an invalid amount of job " << endl;
	}
	outputFile.close();
	system("pause");
	return 0;
}