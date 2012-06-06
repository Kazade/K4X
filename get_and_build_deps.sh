git clone --recursive git://github.com/Kazade/KGLT.git /tmp/kglt
mkdir /tmp/kglt/build
cd /tmp/kglt/build
cmake .. && make -j4
sudo make install

