# Build instructions

---

First create a folder called "build" and invoke cmake to generate the required files:

```sh
mkdir build
cd build
cmake ..
```

Then build the executables with make:

```sh
make all
```

At the end you will have two executables:

- zotti_asd_project
- zotti_asd_project_timings



### zotti_asd_project

---

This executable takes a string of comma separated floats in input from stdin that terminates with a "." and outputs the weighted lower median of them

Usage:

```
./zotti_asd_project
0.01, 0.1, 2.42, 3.14, 2.4 .
```

or piping a file containing the input string

```sh
echo "0.01, 0.1, 2.42, 3.14, 2.4 ." > input.txt
./zotti_asd_project < input.txt
```



### zotti_asd_project_timings

---

This executable takes an input size as argument and outputs a csv string with the following format:

> size, average_execution_time, error

Usage:

```
./zotti_asd_project <size>
```

or piping the results to a file

```
./zotti_asd_project <size> > timings.csv
```



### get_timings.py

---

This simple python script automates the collection of data for different sizes, outputting a csv file called "timings.csv"