type tile = {
  id: string,
  content: string,
  completed: bool
};

let createNewTile content => {
  id: string_of_float (Js.Date.now ()),
  content: content,
  completed: false
};

let className tile => "tile" ^ (tile.completed ? " tile__completed" : "");

let component = ReasonReact.statelessComponent "Tile";
let make ::tile ::onClick _children => {
  ...component,
  render: fun _self => {
    <li className=(className tile) onClick=(fun _event => onClick tile)>
      (ReasonReact.stringToElement tile.content)
    </li>
  }
};
