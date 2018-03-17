let use = (a, m) => {
  Express.App.use(a, m);
  a;
};

let useOnPath = (a, m, ~path) => {
  Express.App.useOnPath(a, m, ~path);
  a;
};
