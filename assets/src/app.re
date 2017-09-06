[%bs.raw {| require("css/app.css") |}];

let testDatabase:Tile.tile = {
  id: "1",
  content: "testing",
  completed: false
};

type action = 
  | CreateTile
  | DeleteTile;

type state = {
  tiles: list Tile.tile
};

module Root = {
  let component = ReasonReact.reducerComponent "RootComponent";
  let make ::name _children => {
    ...component,

    initialState: fun () => {tiles: [testDatabase, testDatabase]},

    reducer: fun action state => 
      switch action {
      | CreateTile => ReasonReact.Update state
      | DeleteTile => ReasonReact.Update state
      },

    render: fun self => {
      let todoItems = 
        self.state.tiles
        |> List.map (fun tile => <Tile tile=tile />)
        |> Array.of_list;

      <div>
        <input />
        <ol>
          (ReasonReact.arrayToElement todoItems)
        </ol>
      </div>
    }
  };
};

ReactDOMRe.renderToElementWithId <Root name="Kyle" /> "react-app";
