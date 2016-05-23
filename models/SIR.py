# -*- coding: utf-8 -*-

"""
	@file MME.py
	@brief Mathematical epidemic models implementation
	@author Pierre Thévenet
	@date 2016-05-23
"""

from scipy import *
from pylab import *
from scipy.integrate import odeint


### ---------- SIR (Kermack-McKendrick)-----------------------------------------
def SIR_differenciate(syst, t, alpha, beta):
	""" Differenciate syst according to the SIR model
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


def SIR(S, I, R, alpha, beta, ti, tf, n):
	""" Applies SIR model, returns a graph of the solution.
    Keyword arguments:
    S -- Initial number of infectious
    I -- Initial number of susceptible
	R -- Initial number of recovered
	alpha -- Infection rate (disease constant)
	beta -- Recovering rate (disease constant)
	ti -- initial time
	tf -- final time
	n -- division of the time interval
	"""
	N = S + I + R # Total population, constant
	syst_CI = array([S,I,R])
	rho = beta/float(alpha)

	step = (tf-ti)/float(n)
	t = array([step * i for i in range(n)])

	solution = odeint(SIR_differenciate,syst_CI,t, args=(alpha, beta))

	St = solution[:, 0]
	It = solution[:, 1]
	Rt = solution[:, 2]


	plot(t, St, label='Susceptibles')
	plot(t, It, label='Infectious')
	plot(t, Rt, label='Recovered')
	xlabel('Time')
	ylabel('Population')
	legend()
	savefig("results_SIR.png")
	show()
	clf()
