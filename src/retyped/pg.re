type t;

type db = {
  .
  "user": string,
  "host": string,
  /* "database": string, */
  "password": string,
  "port": int,
};

[@bs.module "pg"] [@bs.new] external client : db => t = "Client";

[@bs.send] external connect : t => Js.Promise.t('a) = "connect";

[@bs.send]
external query : (t, string, array(string)) => Js.Promise.t('a) = "query";

[@bs.send] external end_ : t => Js.Promise.t(unit) = "end";
