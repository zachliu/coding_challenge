Insight Data Engineering - Coding Challenge  
======

README
------

    1. wordCount  
       It is to count all the words in the given text files.  
    2. runningMedian  
       It is to keep track of the median for the number of  
       words in each line of the given text files.  
       
General Information
-------------------
    Language:	C++11  
    OS:	        Ubuntu 15.04 64-bit  
    Compiler:	g++ version 4.9.2 (Ubuntu 4.9.2-10ubuntu13)  
    IDE:        NetBeans IDE 8.0.2 (Build 201411181905)  
    Platform:   Intel® Core™ i5-4200U CPU with 7.5 GiB memory  
    
Author
------

    by Zexi Liu  
    on Jun 11th, 2015
    
Manifest
--------
    .
    ├── README.md
    ├── run.sh
    ├── src
    │   ├── runningMedian.cpp
    │   └── wordCount.cpp
    ├── wc_input
    │   └── test.txt
    └── wc_output
        ├── med_result.txt
        └── wc_result.txt



Compile/run
-----------	

    run.sh contains the default rules of compiling and running the two programs.  
    Note: change the access permissions of run.sh before using it:  
    $ sudo chmod 755 run.sh  
    $ ./run.sh  

Features
--------

    * They can work on multiple files in alphabetic order.  
    * Capable of processing large text files.  
      Time consumption for processing "War and Peace" (65,008 lines, 576,613 words):  
      real time: 240ms; user: 40ms; system: 180ms (NetBeans timer)  
    * Punctuation are removed ("shout" and "shout." are counted together).  
    * Capitalization are ignored.  

Known issues 
-------------

    * The apostrophe (') is also removed so that "don't" is counted as "dont".
