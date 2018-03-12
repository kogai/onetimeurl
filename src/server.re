[@bs.module "body-parser"]
external bodyParserJson : unit => Express.Middleware.t = "json";

[@bs.module]
external serveStatic :
  (string, {. "index": array(string)}) => Express.Middleware.t =
  "serve-static";

let use = (a, m) => {
  Express.App.use(a, m);
  a;
};

let useOnPath = (a, m, ~path) => {
  Express.App.useOnPath(a, m, ~path);
  a;
};

let schema =
  GraphQL.Utilities.buildSchema(
    Node.Fs.readFileSync("./src/schema.graphql", `utf8),
  );

let rootValue = {"hello": () => "world!!!"};

Express.App.make()
|> use(_, bodyParserJson())
|> use(_, serveStatic("./public", {"index": [|"index.html"|]}))
|> useOnPath(
     _,
     ~path="/graphql",
     ApolloServerExpress.createGraphQLExpressMiddleware(schema, ~rootValue),
   )
|> useOnPath(
     _,
     ~path="/graphiql",
     ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql"),
   )
|> Express.App.listen(
     ~port=3000,
     ~onListen=(_) => Js.log2("Server start at", 3000),
     _,
     (),
   );
