FROM gcc:10.2

WORKDIR /root

RUN apt-get -y update && apt-get -y install libomp-dev
