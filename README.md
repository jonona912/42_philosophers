<h1 align="center">
	🍝 Philosophers
</h1>

<p align="center">
	<b><i>Dining Philosophers Problem – Multithreading & Synchronization in C</i></b><br>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-What-I-Learned">What I Learned</a>
</h3>

---

## 💡 About the project

> _Philosophers is a classic computer science project that explores the challenges of concurrency, resource sharing, and process synchronization. The task is to implement a simulation of the Dining Philosophers Problem using multithreading in C, managing access to shared resources (forks) and preventing deadlocks and race conditions. The project deepens understanding of thread management, mutexes, and the complexities of concurrent programming._

For more detailed information, look at the [**subject of this project**](https://github.com/jonona912/42_philosophers/blob/main/philosophers_subject.pdf).

## 🛠️ Usage

### Requirements

The project is written in C and requires the **`gcc` compiler** and standard **POSIX threads library (`-lpthread`)** to run.

### Instructions

**1. Compiling the project**

To compile, navigate to the project directory and run:

```shell
$ make
```

**2. Running the program**

To start the simulation, run:

```shell
$ ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
```

**Example:**

```shell
$ ./philosophers 5 800 200 200
```

## 📚 What I Learned

- Multithreading and thread management in C
- Mutexes and synchronization primitives
- Avoiding deadlocks and race conditions
- Simulating concurrent systems
- Debugging concurrent applications

---

## 📝 Draft of what I felt right after completing the project
Philosophers was an interesting project in terms of learning how threads and synchronization work. However, after some time, the project felt like it was holding me back because I was spending more time debugging it. The code design is far from what I wanted it to be but because I was trying to make philosopher sleep in 9 milisecond gaps to give computure more time to process other stuff. 9 milisecond because the project had 10 milisecond tolerance level to detect philosphers death, report and exit it. I implemented my idea and it worked, but the timestamps getting off due to in between function calculations. Then I abondoned the approach to check whether a philosopher has died and whether forks were freed in shorter time intervals (from 9miliseconds to 0.05 miliseconds or 50 microseconds). The code and timestamps depend on other functions. This means that the code is very easy to break by small changes introduced, while if the functions were not interdependent, the code would be more robust to changing and shuffling. The reason I did this is to record times as soon as a function stops, time is recorded before other processes are executed that take time. Also, during evaluations I found that I did not need "forks" mutex and there is a small change needed to be done in thinking loop so that the code exits by destroying all mutexes that were unlocked. However, since I feel I have spent more time than I had to in this project, I will leave the project as they are and will use the lessons learned during this project to my next project :)
