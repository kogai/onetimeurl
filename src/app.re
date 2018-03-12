[@bs.module "body-parser"]
external bodyParserJson : unit => Express.Middleware.t = "json";

let tap2 = (f, x, y) => {
  f(x, y);
  x;
};

let use = (a, m) => {
  Express.App.use(a, m);
  a;
};

let useOnPath = (a, m, ~path) => {
  Express.App.useOnPath(a, m, ~path);
  a;
};

let schema = GraphQL.Utilities.buildSchema("type Query { hello: String }");

let rootValue = {"hello": () => "world"};

Express.App.make()
|> use(_, bodyParserJson())
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
