# Review

## Lecture 1

+ What is an OS:
  + Special layer of software that provide application software access to hardware resources:
    + Convenient abstraction of complex hardware device.
    + Protected access to shared sources.
    + Security and authentication.
    + Communication amongst logical entities

+ An OS include:
  + a Program
    + called **kernel**, which manages all the physical devices
  + some more programs
  + some "optional" **programs**

+ What is a process
  + A process is an **execution instance** of a program
    + More than one process can execute the same program code.

+ **Program** vs **Process**
  + A process has states concerning the execution
    + While line of codes it is running
    + How much time left before returning the CPU to others
  + Linux commands about process
    + `ps`: "Process status", it can report a vast amount of information about every process in system

+ Process hierarchy
  + Process relationship
    + A parent process will have its child process
    + Also, a child process will have it child process
    + This forms a tree hierarchy

+ **System call** vs **Library function call**
  + **System call** always too primitive and is not programer-friendly
  + **Library Function** are usually complied and packed inside an object called **library file**.

+ File System
  + e.g: FAT16 FAT32 NTFS Ext3 Ext4 BtrFS Juliet...
  + How to organize your files in the system

+ FS vs OS
  + An OS may understand different FSs.
  + Each disk can have multiple FSs.

## Lecture 2

+ Storage Device Hierarchy
  + register > cache > main memory > solid-state disk > hard disk > optical disk > magnetic tapes

+ Four Fundamental OS Concepts
  + Thread-(Thread of Control)
    + Certain registers hold the context of thread.
      + **Thread Pointer** hold the address of the top of stack.
    + **Thread: Single unique execution context**
    + A thread is executing on a processor when it is resident in the processor registers.
    + PC register holds the address of executing instruction in the thread.
    + Register hold the root state of thread.
  + Address space(with translation)
    + **The set of accessible address + state associated with them**
  + Process
    + Operating System must pro tect itself from user programs
      + Reliability
      + Security
      + Privacy
      + Fairness
    + Process: execution environment with Restricted Rights
      + Address Space with one or more Threads
      + Owns memory(address space)
      + Owns file descriptors, file system context, ...
      + Encapsulate one or more thread sharing process resources
    + Process:
      + Protected from each other
      + OS Protected from them
      + Process provides memory protection
      + Threads more efficient than process
    + Communication within process **easier**
    + Communication between process **harder**
  + Dual mode operation / Protection

+ Three Type of mode transfer
  + Syscall
  + Interrupt
  + Trap or Exception
  + All 3 are an Unprogrammed control Transfer
