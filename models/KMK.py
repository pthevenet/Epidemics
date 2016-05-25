# -*- coding: utf-8 -*-

"""
	@file KMK.py
	@brief Mathematical epidemic models implementation - Kermack-McKendrick
	@author Pierre Thévenet
	@date 2016-05-23
"""
import sys
import getopt
from scipy import *
from pylab import *
from scipy.integrate import odeint


### ---------- KMK (Kermack-McKendrick)-----------------------------------------
def KMK_differenciate(syst, t, alpha, beta):
	""" Differenciate syst according to the KMK model
	Keyword arguments:
	syst -- current system
	t -- time
	alpha -- Infection rate (disease constant)
	beta -- Recovering rate (disease constant)
	"""
	s = syst[0]
	i = syst[1]
	r = syst[2]

	sp = -alpha * s * i
	ip = alpha * s * i - beta * i
	rp = beta * i
	return [sp,ip,rp]


def KMK(S, I, R, alpha, beta, t, n):
	""" Applies KMK model, returns a graph of the solution.
    Keyword arguments:
    S -- Initial number of susceptible
    I -- Initial number of infectious
	R -- Initial number of recovered
	alpha -- Infection rate (disease constant)
	beta -- Recovering rate (disease constant)
	t -- time duration
	n -- division of the time interval
	"""
	N = S + I + R # Total population, constant
	syst_CI = array([S,I,R])
	rho = beta/float(alpha)

	step = (t-0)/float(n)
	t = array([step * i for i in range(n)])

	solution = odeint(KMK_differenciate,syst_CI,t, args=(alpha, beta))

	St = solution[:, 0]
	It = solution[:, 1]
	Rt = solution[:, 2]


	plot(t, St, label='Susceptibles')
	plot(t, It, label='Infectious')
	plot(t, Rt, label='Recovered')
	xlabel('Time')
	ylabel('Population')
	legend()
	savefig("results_KMK.png")
	#show()
	clf()


def main(S, I, R, alpha, beta, t, n):
	KMK(int(S), int(I), int(R), alpha, beta, int(t), int(n))
	return 0
