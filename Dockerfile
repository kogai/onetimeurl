FROM node:alpine

ADD . /app
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

CMD [ "yarn", "start" ]
