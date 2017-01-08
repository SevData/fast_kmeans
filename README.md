# fast_kmeans
This is an enhanced Python 3 K-Mean clustering algo calling C Code with Cython interface. 
The code was developed and tested on Ubuntu / Amazon EC2 on Python 3.4 and 3.5.
It also run successfully on MacOS X on Python 3.4 and 3.5.

Installation Notice (Ubuntu 16.04.1)
------------------------------------

1. Download all files :
fast_km_example.py  # Python example__
fast_km.c           # C code
fast_km.h           # C Header
setup.py            # Cython builder (to be executed)
fast_km.pyx         # Cython link

2. Install/Upgrade python libraries
sudo apt-get --yes --force-yes update
sudo apt-get --yes --force-yes upgrade
sudo apt-get --yes --force-yes install python3-pip
sudo apt-get --yes --force-yes install packaging-dev
sudo pip3 install numpy
sudo pip3 install cython

3. Call Cython builder with setup.py
python3 setup.py build_ext --inplace

4. Run the example from Python 3
python3 fast_km_example.py
