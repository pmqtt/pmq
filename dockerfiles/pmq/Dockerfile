FROM pmqtt/dev
ENV LD_LIBRARY_PATH /usr/local/lib64
EXPOSE 1883
RUN apk update \
        && apk add bash \
        && apk add openssl-dev && apk add libc6-compat \
        && apk add git \
        && apk add gcc \
        && apk add g++ \
        && apk add gdb \
        && apk add valgrind \
        && apk add cmake  \
        && apk add make \
        && apk add zlib-dev \
        && apk add boost-dev \
        && apk add py-pip \
        && mkdir /third_party && cd /third_party \
        && git clone https://github.com/microsoft/cpprestsdk.git \
        && cd /third_party/cpprestsdk \
        && git submodule update --init \
        && cmake . \
        && make -j4 \
        && make install \
        && cd /third_party \
        && git clone https://github.com/jbeder/yaml-cpp.git \
        && cd /third_party/yaml-cpp \
        && cmake . \
        && make -j4 \
        && make install \
        &&git clone https://github.com/pmqtt/pmq.git \
        && cd pmq \
        && cmake . \
        && make -j4 \
        && make install \
        && cd .. \
        && apk del bash \
        && apk del git \
        && apk del gcc \
        && apk del g++ \
        && apk del gdb \
        && apk del valgrind \
        && apk del cmake  \
        && apk del make \
        && apk del zlib-dev \
        && apk del py-pip \
        && apk del vim \
        && rm -rf third_party \
        && rm -rf pmq \
        && rm -rf /usr/include/* \
        && rm -rf /usr/local/include/* \
        && rm -rf /usr/lib/python2.7 \
        && rm -rf /usr/lib/python3.6 \
        && rm -rf /usr/lib/*.a \
        && rm -rf /usr/local/lib/*.a \
        && rm -rf /usr/local/lib64/*.a \
        && rm -rf /usr/local/lib64/cpprestsdk \
        && rm -rf /usr/local/share/*

CMD ["PMQ"]