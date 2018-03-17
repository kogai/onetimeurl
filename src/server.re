let connect =
  Async.(
    Pg.client({
      "user": "postgres",
      "password": "mysecretpassword",
      "host": "db",
      /* "database": "onetimeurl", */
      "port": 5432,
    })
    |> return
    >>= Pg.connect
    >>= Pg.query(_, "select * from urls", [||])
  );

/* >>= (x => Js.log(x)) */
Js.log(connect);

/* >>= Pg.end_ */
let schema =
  GraphQL.Utilities.buildSchema(
    Node.Fs.readFileSync("./src/schema.graphql", `utf8),
  );

let rootValue = {"hello": () => "world!!!"};

let app =
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
     );
