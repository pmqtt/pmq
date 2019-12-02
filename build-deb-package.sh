#!/bin/bash

cd ~
mkdir pmq_0.7-0
mkdir pmq_0.7-0/DEBIAN
mkdir pmq_0.7-0/usr/local/bin
cp "~/pmq/PMQ" pmq_1.0-1/usr/local/bin
echo "Package: pmq" >> pmq_0.7-0/DEBIAN/control
echo "Version: 0.7-0" >> pmq_0.7-0/DEBIAN/control
echo "Section: base" >> pmq_0.7-0/DEBIAN/control
echo "Priority: optional" >> pmq_0.7-0/DEBIAN/control
echo "Architecture: i386" >> pmq_0.7-0/DEBIAN/control
echo "Depends: libboost-all (>= 1.65.0)" >> pmq_0.7-0/DEBIAN/control
echo "Maintainer: pmqtt" >> pmq_0.7-0/DEBIAN/control
echo "Description: mqtt message broker" >> pmq_0.7-0/DEBIAN/control

dpkg-deb --build pmq_0.7-0
