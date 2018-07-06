#########################################
# Welcome!                              #
# This file is intended for Mac OS X,   #
# but can work on any other operating   #
# systems if you change QT_INSTALL_PATH #
#                -Created by @DougBeney #
#########################################

# In the first two lines, I define the source (.cpp) file and the desired output file to be created (./hello)
SOURCE = VersionControll/Main.cpp
OUTPUT = main
DEFINES = -DUNIX

# This variable is used as a quick reference to the QT install path. This is my custom install directory on Mac OS X.
QT_INSTALL_PATH = /usr/dev/Qt/5.11.1/gcc_64

# This is where you would provide the proper includes depending on your project's needs
INCLUDES = -I$(QT_INSTALL_PATH)/include/QtWidgets

#This is the RPATH. To be honest, I am not completely sure of what it does, but it is neccesary.
RPATH = -Wl,-rpath,$(QT_INSTALL_PATH)/lib

#Here is where you link your frameworks
FRAMEWORKS = -F$(QT_INSTALL_PATH)/lib# -framework QtCore -framework QtWidgets

# The main action that happens when you type "make"
all:
	# We run the g++ command and make sure we use c++11 with the second argument. Then after that, we simply plugin in our previous variables.
	g++ -std=c++11 $(SOURCE) $(INCLUDES) $(FRAMEWORKS) $(RPATH) $(DEFINES)  -o $(OUTPUT)

