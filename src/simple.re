let resolvers = {
  "Query": {
    "hello": () => "Hellow world from GCR!",
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
      Js.log(params);
      Js.log(path);
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
