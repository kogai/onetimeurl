Express.App.make()
|> Express.App.listen(~port=3000, ~onListen=(_) =>
     Js.log2("Server start at", 3000)
   , _, ());
