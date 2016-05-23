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

### ---------- RM (Ross-McDonald) ----------------------------------------------
def RM_differentiate(syst, t, a, b1, b2, mu, gamma,):
	""" Differenciate syst according to the SIR model
	Keyword arguments:
	syst -- current system
	t -- time
	a -- Number of infection tries per unit time per carrier (mosquito bites)
	b1 -- Ratio of bites from infected carriers resulting in an infection for the target
	b2 -- Ration of bites to infected targets resulting in an infection for the carrier
	mu -- Natural carrier mortality rate
	gamma -- Cure rate for targets
	"""

	Sh = syst[0]
	Ih = syst[1]
	Sv = syst[2]
	Iv = syst[3]
	H = Sh + Ih
	V = Sv + Iv
	Ihp = b1*a*Iv*((H-Ih)/float(H)) - gamma*Ih
	Ivp = b2*a*Ih*((V-Iv)/float(H)) - mu*Iv
	Shp =  - Ihp
	Svp =  - Ivp
	return [Shp, Ihp, Svp, Ivp]

def RM(Sh, Ih, Sv, Iv, a, b1, b2, mu, gamma, ti, tf, n):
	""" Applies RM model, returns a graph of the solution.
	Keyword arguments:
	Sh -- Initial number of healthy targets (humans H)
	Ih -- Initial number of infected targets (humans H)
	Sv -- Initial number of non-infected carriers (mosquitos V)
	Iv -- Initial number of infected carriers (mosquitos V)
	a -- Number of infection tries per unit time per carrier (mosquito bites)
	b1 -- Ratio of bites from infected carriers resulting in an infection for the target
	b2 -- Ration of bites to infected targets resulting in an infection for the carrier
	mu -- Natural carrier mortality rate
	gamma -- Cure rate for targets
	ti -- initial time
	tf -- final time
	n -- division of the time interval
	"""
	syst_CI = array([Sh, Ih, Sv, Iv])
	step = (tf - ti)/float(n)

	t = array([step * i for i in range(n)])

	solution = odeint(RM_differentiate, syst_CI, t, args=(a, b1, b2, mu, gamma))

	Sht = solution[:, 0]
	Iht = solution[:, 1]
	Svt = solution[:, 2]
	Ivt = solution[:, 3]

	plot(t, Sht, label='Healthy targets')
	plot(t, Iht, label='Infected targets')
	plot(t, Svt, label='Non-infectious carriers')
	plot(t, Ivt, label='Infectious carriers')
	xlabel('Time')
	ylabel('Population')
	legend()
	savefig("results_RM.png")
	show()
	clf()
