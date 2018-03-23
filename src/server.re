type url = {
  hashVal: string,
  rawUrl: string,
};

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
  >>= (
    conn => {
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
        |>>> (
          "/:path",
          Express.Middleware.from((_next, req, res) =>
            req
            |> Express.Request.params
            |> Js.Dict.unsafeGet(_, "path")
            |> Js.Json.classify
            |> Express.Response.(
                 fun
                 | Js.Json.JSONString(path) => {
                     Js.log(path);
                     Pg.Pool.query(
                       conn,
                       "SELECT * FROM urls WHERE hash_val == $1",
                       [|path|],
                     )
                     >>= (
                       (res: Pg.result(url)) => {
                         Js.log(res##rows);
                         return(Js.null);
                       }
                     );
                     sendStatus(StatusCode.Ok, res);
                   }
                 | _ => sendStatus(StatusCode.NotFound, res)
               )
          ),
          /* let result = Json.Encode.(object_([("status", int(200))]));
             Express.Response.sendStatus(Ex)
             Express.Response.sendJson(result, res); */
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
      return(conn);
    }
  )
);
