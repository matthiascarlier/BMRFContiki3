# BMRF

This version of Contiki implements Biderectional Multicast RPL Forwarding (BMRF) in Contiki 3.x

# simulations

All simulations can be found in examples/ipv6/multicast. To run a series a simulations, look at "startsimualtions.sh" (or variants). To process the data, look at the files "processdatahops.py" and "calculateInterval.py" (or variants).

examples/ipv6/multicast/bmrf provides a general example on how to use BMRF to forward multicast packets when using RPL.

examples/ipv6/multicast/simulations-bmrf contains all simulations for the SKY motes.

examples/ipv6/multicast/simulations-bmrf-z1 contains all simulations for the Z1 motes.

the folders examples/ipv6/multicast/simulations-bmrf-simple* contains all simulation for comparing BMRF on contikiMAC and TSCH
