# philosopher_42

## Project Overview
Philosopher is a project that simulates the famous Dining Philosophers problem, which is a classic synchronization problem in computer science. The goal of the project is to model philosophers who sit around a table, where each philosopher alternates between thinking and eating. The challenge is to avoid situations such as deadlock and resource starvation while ensuring that the philosophers can eat in a fair and synchronized way.

### How It Works:
Each philosopher is a thread: In this simulation, each philosopher is represented by a thread that alternates between thinking, eating, and sleeping.
Each fork is a mutex: The forks used by the philosophers are simulated with mutexes to ensure that only one philosopher can use a fork at any given time.
The project ensures proper synchronization by using mutexes to manage access to the shared resources (the forks) and avoid problems like deadlock or resource starvation.


## 🚀 Use
### 1. Clone the Repository
```
git clone https://github.com/paulovictorarmando/philosopher_42.git
cd philosopher_42
```
### 2.Build
Use the Makefile to compile the source files:
```
make all
```
### 3. Clean Up
To remove object files and the binary, run:
```
make clean
make fclean
```
### 4. Using:
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals]

```

number_of_philosophers: The total number of philosophers (must be a positive integer).
time_to_die: The maximum time (in milliseconds) a philosopher can go without eating before dying.
time_to_eat: The time (in milliseconds) a philosopher spends eating.
time_to_sleep: The time (in milliseconds) a philosopher spends sleeping after eating.
number_of_meals: The number of times each philosopher should eat (optional).
###
