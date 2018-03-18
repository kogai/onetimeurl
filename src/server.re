let connect =
  Async.(
    Pg.Pool.make({
      "user": "postgres",
      "password": "mysecretpassword",
      "host": "db",
      "database": "onetimeurl",
      "port": 5432,
    })
    |> return
    >>= Pg.Pool.connect
    >>= Pg.Pool.query(_, "select * from urls", [||])
    >>= (
      (
        x:
          Pg.result(
            {
              .
              "hash_val": string,
              "raw_url": string,
            },
          ),
      ) => {
        Js.log(x);
        return(x);
      }
    )
  );

let resolvers = {
  "Query": {
    "hello": () => "Hellow world!",
  },
};

let schema =
  GraphQLTools.makeExecutableSchema({
    "resolvers": resolvers,
    "typeDefs": Node.Fs.readFileSync("./src/schema.graphql", `utf8),
  });

let app =
  Utils.(
    Express.App.make()
    |>> BodyParser.json()
    |>> ServerStatic.default("./public", {"index": [|"index.html"|]})
    |>>> (
      "/graphql",
      ApolloServerExpress.createGraphQLExpressMiddleware(schema),
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
