type t('a) = Js.Promise.t('a);

let return: 'a => Js.Promise.t('a);

let bind: (Js.Promise.t('a), 'a => Js.Promise.t('b)) => Js.Promise.t('b);

let (>>=): (Js.Promise.t('a), 'a => Js.Promise.t('b)) => Js.Promise.t('b);
