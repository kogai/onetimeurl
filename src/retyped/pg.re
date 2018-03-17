type t;
[@bs.module "pg"] [@bs.new] external client : unit => t = "Client";
 [@bs.send]  external connect: t => Js.Promise.t('a) = "connect";
 [@bs.send]  external query: t => string => array(string) => Js.Promise.t('a) = "query";
 [@bs.send]  external end_: t => Js.Promise.t(unit) = "end";
