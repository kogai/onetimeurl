FROM node:alpine

RUN apk upgrade --update \
  && apk add --virtual \
  build-dependencies \
  build-base \
  perl \
  git \
  make \
  gcc \
  python

WORKDIR /app

COPY ./yarn.lock /app/yarn.lock

ADD . /app

RUN yarn
RUN yarn build

CMD [ "node", "./src/simple.bs.js" ]
