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

COPY ./package.json ./bsconfig.json ./yarn.lock /app/

RUN yarn

COPY . /app

RUN yarn build

CMD [ "node", "./src/simple.bs.js" ]
