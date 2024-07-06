# Scala Computing Programming Assignment


## Quick Start

```
$ cd scalacomputingassignment
$ g++ main.cpp -std=c++11
$ ./a.out
```

## Introduction
This is a classical puzzle about crossing the river by several people over a narrow bridge.

A group of people walking together in a forest at night encounters a bridge that they have to cross. The bridge can hold only two people at a time. The group has one torch, which must be used to cross the bridge. People can walk with different speed, so each person needs different time to cross the bridge. When crossing the bridge, a pair of people walks at the slowest person's pace. What is the minimum time the group can cross the bridge?

A minor modification from the scenario explained above is that there can be a number of bridges instead of just one that need to be traversed and new people can join the existing pool of people along the way.

The goals for this assignment are:
* Determine the fastest time that the hikers can cross each bridge
* the total time to complete all crossings

-----

## TestCase:

Demonstrate the operation of your program using the following inputs: the hikers cross 3 bridges, at the first bridge (100 ft long) 4 hikers cross (hiker A can cross at 100 ft/minute, B at 50 ft/minute, C at 20 ft/minute, and D at 10 ft/minute), at the second bridge (250 ft long) an additional hiker crosses with the team (E at 2.5 ft/minute), and finally at the last bridge (150 ft long) two hikers are encountered (F at 25 ft/minute and G at 15 ft/minute).

## Custom Input
Configure the number of bridges that need to be traversed.
```
numBridges: 
    - 3
```
Provide the length of individual bridges.
```
bridgeLengths: 
    - 100
    - 250
    - 150
```
Provide the individual moving speeds of new arriving hikers at every bridge.
```
hikersSpeedsAtEachBridge: 
    - 100,50,20,10
    - 2.5
    - 25,15
```

## Test case files

`test1.yaml`, `test2.yaml`, `test3.yaml` present different test cases. You can modify any of these input files to update your test case.

-----

## Comments & concerns

The original problem stated that program inputs need to be read from yaml file but since i did not have a sample input, I have a simple yaml input file format in this submission. I can port to different yaml input format if needed.


