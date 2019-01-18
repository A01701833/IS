import fileinput

lines =[]

for line in fileinput.input():
	lines.append(line)

if any("." in s for s in lines):
	lines[0:]= [float(x) for x in lines[0:]]
else:
	lines[0:]= [int(x) for x in lines[0:]]


suma = 0

for i in lines[0:]:
	suma += i 

print(suma)
