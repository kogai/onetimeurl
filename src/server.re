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
          Express.Middleware.from((_next, req, res) => {
            let result = Json.Encode.(object_([("status", int(200))]));
            let params = Express.Request.params(req);
            let path = Js.Dict.get(params, "path");
            /* Js.Option.default */
            Js.log(params);
            Js.log(path);
            /* V            switch (getDictString(Request.params(req), "id")) {
                           | Some("123") => Response.sendJson(makeSuccessJson(), res)
               | _ => next(Next.route, res) */
            /* >>= Pg.Pool.query(_, "select * from urls", [||]) */
            /* >>= (
                    (x: Pg.result(url)) => {
                      Js.log(x);
                      ret
               urn( x);
                 }
                  ) */
            Express.Response.sendJson(result, res);
          }),
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
