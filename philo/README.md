*This project has been created as part of the 42 curriculum by rchaumei.*

# Philosophers

## Description

The **Philosophers** project is an introduction to multithreading and synchronization using POSIX threads (pthreads).

The goal is to solve the classic Dining Philosophers problem while avoiding:
- Deadlocks
- Data races
- Starvation
- Undefined behavior

Each philosopher is represented by a thread. Forks are protected using mutexes.  
The simulation must respect strict timing constraints and stop when:
- A philosopher dies, or
- Each philosopher has eaten a required number of times (if specified).

This project focuses on:
- Multithreading
- Mutex synchronization
- Precise time handling

---

## Instructions

### Compilation

This will generate the executable:

```bash
make
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
# Arguments

number_of_philosophers : Number of philosophers (and forks)

time_to_die : Time in milliseconds before a philosopher dies if they don't eat

time_to_eat : Time in milliseconds spent eating

time_to_sleep : Time in milliseconds spent sleeping

number_of_times_each_philosopher_must_eat (optional) : Simulation stops when all philosophers have eaten this many times

# Example

```bash
./philo 4 410 200 200
```

## Resources

Classic references used:

IBM : https://www.ibm.com/docs/fr/aix/7.3.0?topic=p-pthread-mutex-init-pthread-mutex-destroy-subroutine;

mans of the functions gettimeofday

Understanding of pthread functions : https://youtu.be/o_GbRujGCnM?si=N5YT_4cu_X-k3fOf

AI Usage:

AI assistance was used for:

Understanding race conditions and deadlock scenarios

Improving sleep precision strategy

Structuring the README

All implementation, debugging, and architectural decisions were personally written and validated.