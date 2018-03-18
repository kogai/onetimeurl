let use = (a, m) => {
  Express.App.use(a, m);
  a;
};

let (|>>) = use;

let useOnPath = (a, (path, m)) => {
  Express.App.useOnPath(a, m, ~path);
  a;
};

let (|>>>) = useOnPath;
