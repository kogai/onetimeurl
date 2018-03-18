let connect =
  Async.(
    Pg.Pool.make({
      "user": "postgres",
      "password": "mysecretpassword",
      "host": "db",
      /* "database": "onetimeurl", */
      "port": 5432,
    })
    |> return
    >>= Pg.Pool.connect
    >>= Pg.Pool.query(_, "select * from urls", [||])
  );

Js.log(connect);

let schema =
  GraphQL.Utilities.buildSchema(
    Node.Fs.readFileSync("./src/schema.graphql", `utf8),
  );

let rootValue = {"hello": () => "world!!!"};

let app =
  Utils.(
    Express.App.make()
    |>> BodyParser.json()
    |>> ServerStatic.default("./public", {"index": [|"index.html"|]})
    |>>> (
      "/graphql",
      ApolloServerExpress.createGraphQLExpressMiddleware(schema, ~rootValue),
    )
    |>>> (
      "/graphiql",
      ApolloServerExpress.createGraphiQLExpressMiddleware("/graphql"),
    )
    |> Express.App.listen(
         ~port=3000,
         ~onListen=
           e =>
             switch (Js.toOption(e)) {
             | Some(e) => Js.log(e)
             | None => Js.log("Server start on port 3000")
             },
         _,
         (),
       )
  );
