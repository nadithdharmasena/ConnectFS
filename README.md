# ConnectFS
File organization system for efficient project initiation.

## Purpose
ConnectFS aims to make the process of gathering resources for 
new projects and assignments easier and quicker. 

### What problem is ConnectFS trying to solve?

Consider the following situation.

Suppose you would like to build a high-frequency trading system. Note that HFT
requires expertise in computer science, math, and finance. Because of your
previous experiences with these subjects, you have stockpiles of educational
resources and previously written code that would be helpful as you begin your work
on the project.

Unfortunately, these files are scattered all over your computer. Since CS, math, and finance
are generally unrelated, the files are probably stored in completely different places, 
making your search for them quite difficult and time-consuming. This problem is a common
one because many projects lie at the intersection of typically 
disconnected topics. 

This example highlights that the file-folder system on present-day operating systems
is too rigid for the demands of inter-domain project management.

### How does ConnectFS solve this issue?

ConnectFS offers a file system that is represented internally by a directed graph. Each node in the graph
represents either a Topic or a File. Topics can point to other Topics or Files. Files cannot have 
children. 

* Topic - Node with label that describes all of its children
    * Machine Learning could have
        * Children Topics that pertain to Support Vector Machine's or Random Forest Classifiers
        * Files that contain implementations of various ML models
* File - Node that contains pointer to locations on the OS' existing file system that house the "real" file
    * File "RandomNumberGenerator" could point to a file at "~/Documents/ProjectRandom/random_generator.py"

Topics are similar to traditional folders. However, there is an important difference. Any topic or file can be the 
child of any number of topics. This capability accounts for the possibility that one resource could fall under
the umbrella of several classifications.

The fact that Files are simply pointers to locations on the OS' file system means that ConnectFS does not deal with
"real" data. This design ensures that Files can be deleted without erasing any underlying data, which makes
for a dynamic file system that can remain clutter-free even after extensive use.

## How can I use ConnectFS?

Begin by cloning this repository, navigating into your local repo folder, and running the following command.

`cmake CMakeLists.txt`

If you do not have cmake installed on your computer, follow the download and install instructions at https://cmake.org/ or install cmake through Homebrew.

After running the cmake command, compile the source code using the following. 

`make`

If all goes well, you should have an executable file named ConnectFS in your local repo folder now. Before starting the application, create a folder named `data` in the same folder as your executable. 
This folder will hold the application's permanent graph database storage files.

## Shell Documentation

[See DOCUMENTATION.md](DOCUMENTATION.md)