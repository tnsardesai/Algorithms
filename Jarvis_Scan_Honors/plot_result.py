import matplotlib.pyplot as plt

f = open('result.txt','r')

# Stores the first number in N.
N = int(f.readline().strip('\n'))

# These two arrays are for storing N numbers with coressponding x and y.
x = []
y = []

# These two arrays are for storing h numbers which form the convex hull.
x_h = []
y_h = []

i = 0;
j = 0;

"""
  i keeps track of the line number. 
  If the line number is less than N then the points should be appended to x, y
  If the line number is equal to N then that value is number of points in the hull.
  If the line number is greater to N then store the points in x_h, x_h.
  j is keeping track of the number of lines after N and breaks when it is equal to h.
"""
for line in f:
	if i < N:
		x.append(int(line.split(None, 1)[0]))	
		y.append(int(line.split(None, 1)[1].strip('\n')))
	if i == N:
		h = int(line.strip('\n')) 
	if i > N:
		j = j+1
		x_h.append(int(line.split(None, 1)[0]))
		y_h.append(int(line.split(None, 1)[1].strip('\n')))	
		if j == h:
			break
	i = i + 1

# We append this so that the convex hull looks complete.
x_h.append(x_h[0])
y_h.append(y_h[0])


plt.plot(x, y, 'b.')  # plot the points in x, y with blue "."
plt.plot(x_h,y_h,'ro-') # plot the points in x_h, y_h with red "0" and - to join them
plt.axis([-1100,1100,-1100,1100]) #axis
plt.grid(True)
plt.show()

