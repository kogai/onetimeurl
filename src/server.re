let connect =
  Async.(
    Pg.client()
    |> return
    >>= Pg.connect
    >>= Pg.query(_, "select * from urls", [||])
    >>= Pg.end_
  );

let schema =
  GraphQL.Utilities.buildSchema(
    Node.Fs.readFileSync("./src/schema.graphql", `utf8),
  );

let rootValue = {"hello": () => "world!!!"};

Express.App.make()
|> Utils.use(_, BodyParser.json())
|> Utils.use(
     _,
     ServerStatic.default("./public", {"index": [|"index.html"|]}),
   )
|> Utils.useOnPath(
     _,
     ~path="/graphql",
     ApolloServerExpress.createGraphQLExpressMiddleware(schema, ~rootValue),
   )
|> Utils.useOnPath(
     _,
     ~path="/graphiql",
     ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql"),
   )
|> Express.App.listen(~port=3000, ~onListen=(_) => Js.log("Start server on port 3000"));
