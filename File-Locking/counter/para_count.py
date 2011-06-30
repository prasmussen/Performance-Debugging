#!/usr/bin/python
import os, re

total = 0

for file in os.listdir("./"):
	if not re.match("^para\d+\.count$", file):
		continue
	f = open(file)
	counter = f.read()
	if not re.match("^\d+$", counter):
		print "Invalid input from file %s" % file
	print "%s: %s" % (file, counter)
	total += int(counter)


print "Total: %d" % total
