FROM node:alpine

COPY ./package.json /app

WORKDIR /app

RUN apk upgrade --update \
  && apk add --virtual \
  build-dependencies \
  build-base \
  perl \
  git \
  make \
  gcc \
  python \
  && yarn

ADD . /app

CMD [ "yarn", "start" ]
