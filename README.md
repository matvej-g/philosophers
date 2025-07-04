# philosophers

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

A Norm-compliant C implementation of the Dining Philosophers problem, simulating philosopher behavior (thinking, eating, sleeping) with threads and synchronization primitives.

## Table of Contents

- [About](#about)  
- [Features](#features)  
- [Installation](#installation)  
- [Usage](#usage)  
- [Example](#example)  

## About

The **Dining Philosophers** problem is a classic concurrency exercise: N philosophers sit around a table with one fork between each pair. Each philosopher must alternately think and eat. To eat, a philosopher must hold both adjacent forks (mutexes), introducing potential deadlock or starvation if not managed correctly.

## Features

  - Monitors each philosopher’s state in a dedicated watcher  
  - Each philosopher runs in its own process
  - Detects philosopher death and cleans up threads/processes  
  - Prevents resource leaks   
- **Configurable parameters**:  
  - Number of philosophers  (don't run < 200 philos, this may overwhel your CPU)
  - Time to die (ms)  (use > 60)
  - Time to eat (ms)  (use > 60)
  - Time to sleep (ms)  (use > 60)
  - [Optional] Number of times each must eat  
  
- **Norm-compliant**:  
  - Only allowed functions
  - Max 25 lines per function  
  - 80-column width limit  
  - Max 4 functions per file  
  - Max 4 parameters per function  

## Installation

**Clone the repo**  
   ```bash
   git clone https://github.com/YourUsername/philosophers.git
   cd philosophers
   make
   ```

## Usage

```bash
  ./philo number_of_philosophers <time_to_die> <time_to_eat> <<time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

## Example

```bash
  ./philo 5 800 200 200 2
```
![Philosophers example](image/example.png)
