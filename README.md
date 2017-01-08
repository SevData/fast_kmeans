# fast_kmeans
This is an enhanced Python 3 K-Mean clustering algo calling C Code with Cython interface. 
The code was developed and tested on Ubuntu / Amazon EC2 on Python 3.4 and 3.5.
It also run successfully on MacOS X on Python 3.4 and 3.5.

Installation Notice (Ubuntu 16.04.1)
------------------------------------

1. Download all files :<br />
fast_km_example.py  # Python example<br />
fast_km.c           # C code<br />
fast_km.h           # C Header<br />
setup.py            # Cython builder (to be executed)<br />
fast_km.pyx         # Cython link<br />

2. Install/Upgrade python libraries<br />
sudo apt-get --yes --force-yes update<br />
sudo apt-get --yes --force-yes upgrade<br />
sudo apt-get --yes --force-yes install python3-pip<br />
sudo apt-get --yes --force-yes install packaging-dev<br />
sudo pip3 install numpy<br />
sudo pip3 install cython<br />

3. Call Cython builder with setup.py<br />
python3 setup.py build_ext --inplace<br />

4. Run the example from Python 3<br />
python3 fast_km_example.py<br />
