# ProduceConsume-OpSys341

Brad Taniguchi  
Matt Levan  
CSC341 Operating Systems  
Dr. Bin Tang  

---

#### Instructions
1. compile with `gcc buffer.c -pthread -o buffer.o`  
2. run with `./buffer.o <sleep time> <producer threads> <consumer threads>`  
    EX './buffer.o 20 5 5'  

#### Contribution
Matt Levan  
    - Primary and final draft of insert\_item() and remove\_item()  
    - README prompt  
Bradley Taniguchi   
    - First draft of insert\_item() and remove\_item()  
    - git repo  

#### Observations
    Outputs are still dont in tandume, thus each printout may occur differently  
    in different order, with definantly different numbers. As the execution of the threads  
    is still done depending on the OS. But the logic will stay the same, with producers
    creating randomly generated numbers and consumers only consuming the correct filled
    places on the buffer. The mutex and semaphore locks will prevent race conditions,
    with all functions of the program working in tandem.
 
---

#### Prompt
Producer Consumer Problem, page 253.

An incomplete program, called `buffer_incomplete.c` is given. Your job is 
to fill the `insert_item()` and `remove_item()`, which should use semaphores as 
well as mutex lock to synchronize producers and consumers to access the buffer 
(NOTE: The book asks to only use semaphores). An output file called 
`output.txt` , after command line input './a.out 20 5 5 > output.txt', is also 
given. Please study both files carefully. The output of your program should 
look similar.

Extra points: 20 points.

1. 10pts. There are 5 producer threads and 5 consumer threads using above 
command line input, please print out the ID of each specific producer/consumer.

2. 10pts. Due to race condition, the time a produder tries to insert into the 
buffer is not necessarily the time it succeeds in insertion; similarly, the 
time a consumer tries to remove from the buffer could be different from the 
time it actually removes. Please printout the time of each if it occurs.

***Deadline 3/15, 11:59pm, Sunday, group of two students.***

Please submit a zip file titled 
`LastNameOfFirstStudent_LastNameOfSecondStudent_341_proj3.zip`,  which includes:

1. the completed source program called 'buffer.c' and

2. README file, including
  * How to compile and run your programs, 
  * Two member members' name and each's specific contribution to the project.

3. Any other observations/findings that you want to mention in your experiment.
Please note that all submissions are final, that is, it allows only one attempt.

