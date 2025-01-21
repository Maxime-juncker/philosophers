# philosophers

> You never thought philosophy would be so deadly

## goals
this project is about managing a mutithreaded program and mutex.

every philosopher run on an isolated thread, they cannot talk to each other nor can they know if an other philosopher is about to die.
to survive, they need to take turn when eating, this is the cycle of a philosopher: `think` -> `eat` -> `sleep`.

the program stop when a philosopher is dead or when number_of_time_philosopher_must_eat has been reach.

(to go deeper: https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## compile it yourself

clone the repo:
```
git clone https://github.com/Maxime-juncker/philosophers.git
cd philosophers/
```

compile it using make
```
make
```

then run it
```
./bin/philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_time_philosopher_must_eat]
```

`<number_of_philosophers>` the number of philosophers and forks around the table (if equal 1, the philosopher will die because there is only one fork and 2 are needed in order to ear)

`<time_to_die>` time before a philosopher die of starvation (in ms) 

`<time_to_eat>:` the time a philosopher take to eat (in ms)

`<time_to_sleep>` the time a philosopher take to sleep (in ms)

`[number_of_time_philosopher_must_eat]` (optional) the after every philosopher have eaten n time, the program will stop
