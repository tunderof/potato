FROM ubuntu

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools -y
RUN apt-get install build-essential -y

WORKDIR /chernov_221-353/
RUN mkdir server
WORKDIR /chernov_221-353/server/
COPY *.cpp /chernov_221-353/server/
COPY *.h /chernov_221-353/server/
COPY *.pro /chernov_221-353/server/

RUN qmake echoServer_ex.pro
RUN make

ENTRYPOINT ["./HallServer"] 
