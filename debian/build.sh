#!/bin/bash

echo "CURRENT "
echo $(pwd)
whoami
CURRENT=$(pwd)
echo $CURRENT
ls
echo "=============================================="
cp ${CURRENT}/../libs/* debian/scopy/opt/scopy/lib/
cp ${CURRENT}/build/scopy debian/scopy/opt/scopy/bin/
ldd debian/scopy/opt/scopy/bin/scopy
ls -la debian/scopy/opt/scopy/bin/
