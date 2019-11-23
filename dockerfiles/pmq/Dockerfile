FROM pmqtt/dev
ENV LD_LIBRARY_PATH /usr/local/lib64
EXPOSE 1883
RUN git clone https://github.com/pmqtt/pmq.git \
    &&  cd pmq \
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
    && rm -rf third_party \
    && rm -rf pmq

CMD ["PMQ"]