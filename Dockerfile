FROM node:alpine

COPY ./yarn.lock /app/yarn.lock

WORKDIR /app

RUN apk upgrade --update \
  && apk add --virtual \
  build-dependencies \
  build-base \
  perl \
  git \
  make \
  gcc \
  python

RUN yarn

ADD . /app

CMD [ "node", "./src/server.bs.js" ]
