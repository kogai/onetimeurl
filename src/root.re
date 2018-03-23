let make = _children => {
  ...ReasonReact.statelessComponent("Root"),
  /* ...ReasonReact.reducerComponent("Root"),
     initialState: () => {
       period: 10,
       size: 16,
       board:
         Utils.(
           16
           |> range
           |> List.rev
           |> List.map(y =>
                16
                |> range
                |> List.rev
                |> List.map(x => {Cell.x, y, status: Cell.Death})

         ),
     },
     reducer: (a, s) =>
       switch (a) {
       | Inc => ReasonReact.Update({...s, size: s.size + 1})
       | Dec => ReasonReact.Update({...s, size: s.size - 1})
       | Tick => ReasonReact.Update({...s, board: next(s.board)})
       | Play(n) =>
         ReasonReact.SideEffects((({reduce}) => tick(reduce, n, s.board)))
       | Spawn(mx, my) =>
         ReasonReact.Update({
           ...s,
           board:
             s.board
             |> List.map(
                  List.map(({Cell.x, y} as cell) =>
                    x == mx && y == my ? {...cell, status: Cell.Live} : cell
                  ),
                ),
         })
       }, */
  render: _self =>
    <div> (ReasonReact.stringToElement("Hello, world.")) </div>,
};
