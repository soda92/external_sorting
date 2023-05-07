TEMPLATE = app
CONFIG -= qt app_bundle
CONFIG += console c++17

SOURCES += ..\hello_world.cc

LIBS += -lfmt -labsl_strings
