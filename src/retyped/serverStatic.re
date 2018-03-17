[@bs.module]
external default :
  (string, {. "index": array(string)}) => Express.Middleware.t =
  "serve-static";
