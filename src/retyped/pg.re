type c;

type config = {
  .
  "user": string,
  "host": string,
  /* "database": string, */
  "password": string,
  "port": int,
};

module Base =
       (Impl: {type t; let make: config => t;})
       : (
           {
             type t;
             let make: config => t;
             let connect: t => Js.Promise.t(t);
             let query: (t, string, array(string)) => Js.Promise.t('a);
             let end_: t => Js.Promise.t(unit);
           } with
             type t = Impl.t
         ) => {
  type t = Impl.t;
  let make = Impl.make;
  [@bs.send] external connect : t => Js.Promise.t('a) = "connect";
  [@bs.send]
  external query : (t, string, array(string)) => Js.Promise.t('a) = "query";
  [@bs.send] external end_ : t => Js.Promise.t(unit) = "end";
};

module Pool =
  Base(
    {
      type t;
      [@bs.module "pg"] [@bs.new] external make : config => t = "Pool";
    },
  );

module Client =
  Base(
    {
      type t;
      [@bs.module "pg"] [@bs.new] external make : config => t = "Client";
    },
  );
