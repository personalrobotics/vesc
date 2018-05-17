from matplotlib import pyplot as plt
import numpy
import IPython

if __name__ == '__main__':
	# Read the .txt file
	fileName = 'torque3sec.txt'
	seconds = []
	speed = []
	with open(fileName) as file:
		for line in file:
			if 'secs:' in line:
				data = line.rstrip().split('secs: ')
				seconds.append(float(data[1]))
			if 'speed:' in line:
				data = line.rstrip().split('speed: ')
				speed.append(float(data[1]))

	time = []
	baseTime = seconds[0]
	i = 0
	while i < len(seconds):
		time.append(seconds[i] - baseTime + seconds[i+1]/1000000000)
		i += 2
	time = numpy.array(time)
	time = time - time[0]
	speed = numpy.array(speed)

	plt.plot(time, speed)
	plt.show()
