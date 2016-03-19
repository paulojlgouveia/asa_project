
import random;

# Numero de Vertices
v = 10
# Numero de Arcos (para alem dos necessarios para ser um grafo ligado)
a = 5


######################################################################

ma = []

for i in range(v):
	l = []
	for x in range(v):
		l.append(False)
	ma.append(l)

b = range(v)
for i in range(v):
	x = random.randint(0, len(b)-1)
	while x == i:
		x = random.randint(0, len(b)-1)
	ind = b.pop(x)
	ma[ind][i] = True
	ma[i][ind] = True

for i in range(a):
	while True:
		x = random.randint(0, v-1)
		poss = []
		for b, el in enumerate(ma[x]):
			if (not el) and (b != x):
				poss.append(b)
		if len(poss) > 0:
			c = poss[random.randint(0, len(poss)-1)]
			ma[x][c] = True
			ma[c][x] = True
			break

with open(str(v)+"v"+str(a)+"a.graph", 'w') as out:
	out.write(str(v) + " " + str(v+a)+"\n")
	for x, i in enumerate(ma):
		for y, h in enumerate(ma[x]):
			if y > x and ma[x][y]:
				out.write(str(x+1) + " " + str(y+1)+"\n")
                