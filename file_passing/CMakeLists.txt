CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
PROJECT("Non copying file sharing")

ADD_EXECUTABLE(consumer consumer.c)
ADD_EXECUTABLE(producer producer.c)

