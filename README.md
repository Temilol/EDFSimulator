### About the Application
This application is a stimulator that schedules job based on the Earliest Deadline First Scheduling Approach.

You can read more about the [EDF Scheduling Algorithm](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)

The Application is a Terminal-based User Interface and it is an Interactive Program.

If **TWO Jobs** are tied, the FIFO Algorithm will be used to decide which to choose.

### Input Template Structure
```
Two Jobs were Inputed
Job A has an Arrival Time of 2, Execution time of 3 and a Deadline time of 4
Job B has an Arrival Time of 1, Execution time of 2 and a Deadline time of 5
```

### Output Template Structure
After the Jobs have been scheduled, The application produce a timeline report as an output explaining what happens at each step. A Template is shown below:

```						
				REPORT TEMPLATE
-------------------------------------------------

At Time 0
At Time 1
The Jobs currently in memory at time 1
Job B has an execution time of 2 and time before its deadline is 5

At Time 2
The Jobs currently in memory at time 2
Job B has an execution time of 1 and time before its deadline is 4
Job A has an execution time of 3 and time before its deadline is 4
Job B has ended its process at time 3

At Time 3
The Jobs currently in memory at time 3
Job A has an execution time of 3 and time before its deadline is 3

At Time 4
The Jobs currently in memory at time 4
Job A has an execution time of 2 and time before its deadline is 2

At Time 5
The Jobs currently in memory at time 5
Job A has an execution time of 1 and time before its deadline is 1
Job A has ended its process at time 6
```

### Language Used
The Application was developed in **C++**

The tool used in developing the application was **Visual Studio**

### Setup/Run the application
Follow the following steps to setup the application on your local system
- **Setup Visual Studio or Any C++ Compiler on your local system**
- **Load the Temilola EDF simulator.cpp file**
- **The Report file generated will be in the Programs' root directory.**