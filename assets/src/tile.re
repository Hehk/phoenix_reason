type tile = {
  id: string,
  content: string,
  completed: bool
};

let component = ReasonReact.statelessComponent "Tile";
let make ::tile _children => {
  ...component,
  render: fun _self => {
    <li>
      (ReasonReact.stringToElement tile.content)
    </li>
  }
};
