import fileinput

lines =[]

for line in fileinput.input():
	lines.append(line)



a = sum([i for i in lines if isinstance(i,int) or isinstance(i,float)])

print a 