import numpy
import scipy
from scipy import misc

my_data = numpy.genfromtxt("BAIXA11.csv", delimiter=',')

scipy.misc.imsave("ALTAS20.jpg", my_data)