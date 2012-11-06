#!/usr/bin/python
import subprocess
import random

#sizes = [20, 40, 80, 160, 320, 640]
#buffers = [1, 2, 4, 8, 10]
#iterations = 200
x = 7000
y = 8000

results = open("random.txt", "w+")
print "Start"
results.write(str(x)+","+str(y)+"\n")

for i in range(x):
	for j in range(y):
		results.write(str(random.uniform(0.0, 1000.0))+"\n")
print "Done"
