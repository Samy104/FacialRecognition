# FacialRecognition
Facial recognition module for the HAS system

Environment Variables
OpenCL = OpenCL_HOME
OpenCV = OpenCV_Build (For cmake) see below for building OpenCV

#Libraries used: 
wxWidgets v3.0.2
OpenCL 3.0.0



#IMPORTANT MODIFICATIONS
##Install CMAKE (for cmake gui)
https://cmake.org/files/v3.4/cmake-3.4.0-rc3-win32-x86.exe
Change: ->OPENCV_HOME/modules/videoio/src/cap_dshow.cpp and add this line in the file:
\#define STRSAFE_NO_DEPRECATE

##Building OPENCV
##Build with CMAKE_BUILD_TYPE=RELEASE 
##BUILD WITH CMAKE_BUILD_TYPE=DEBUG (if you want to debug)
based off: http://perso.uclouvain.be/allan.barrea/opencv/cmake_config.html
--very important (wont built with it enabled)
###remove both IPP in CMAKE_GUI 
####BUILD
####WITH

Opencv build fix (opencv_videoio prob) ---> http://stackoverflow.com/questions/27828740/opencv-3-0-videoio-error

#Debugging
This is a bug with the new gcc (TDM-GCC-5.x) incorrectly setting the python path so debugging is impossible.
change the gdbinit file for both gdb64to:

python
import sys
sys.path.insert(0, '/../../gcc-5.1.0/python')
from libstdcxx.v6.printers import register_libstdcxx_printers
\#register_libstdcxx_printers (None)
end

OpenKinect
http://openkinect.org/wiki/Getting_Started#Manual_build_from_source (Windows)