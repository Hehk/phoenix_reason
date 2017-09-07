[%bs.raw {| require("css/app.css") |}];

type tiles = list Tile.tile;

type action = 
  | CreateTile
  | DeleteTile Tile.tile
  | ChangeTiles tiles
  | ChangeNewTodo string;

type state = {
  tiles: list Tile.tile,
  newTodo: string
};


module Root = {
  let component = ReasonReact.reducerComponent "RootComponent";
  let channel = Socket.channel;

  let handleSubmit event => {
    ReactEventRe.Synthetic.preventDefault event;
    CreateTile;
  };

  let handleChange event => ChangeNewTodo
    (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;

  let loadInitialTiles resp => {
    Js.log resp;
    ChangeTiles [];
  };

  let deleteTodo tile => DeleteTile tile;

  let make ::name _children => {
    ...component,

    initialState: fun () => {
      tiles: [],
      newTodo: ""
    },

    reducer: fun action state => 
      switch action {
      | CreateTile => ReasonReact.Update {
        ...state,
        tiles: [Tile.createNewTile state.newTodo, ...state.tiles],
        newTodo: ""
      }

      | DeleteTile tile => ReasonReact.Update {
        ...state,
        tiles: List.filter (fun candidate => tile != candidate) state.tiles
      }

      | ChangeNewTodo text => ReasonReact.Update {...state, newTodo: text}
      | ChangeTiles tiles => ReasonReact.Update {...state, tiles: tiles}
      },

    didMount: fun {reduce} => {
      channel
      |> Phx.joinChannel
      |> Phx.putReceive "ok" (reduce loadInitialTiles)
      |> Phx.putReceive "error" (fun resp => Js.log resp);

      ReasonReact.NoUpdate
    },

    render: fun {state, reduce} => {
      let todoItems = 
        state.tiles
        |> List.map (fun tile => <Tile tile=tile key=Tile.(tile.id) onClick=(reduce deleteTodo) />)
        |> Array.of_list;

      <div className="reason-root">
        <form 
          className="todo-input"
          onSubmit=(reduce handleSubmit)
        >
          <input
            _type="text"
            className="todo-input__text"
            value=state.newTodo
            onChange=(reduce handleChange)
          />
          <input className="todo-input__submit" _type="submit" />
        </form>
        <ol className="todo-list">
          (ReasonReact.arrayToElement todoItems)
        </ol>
      </div>
    }
  };
};

ReactDOMRe.renderToElementWithId <Root name="Kyle" /> "react-app";
