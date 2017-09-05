[%bs.raw {| require("css/app.css") |}];

module Root = {
  let component = ReasonReact.statelessComponent "Hello!";
  let make ::name _children => {
    ...component,
    render: fun _self => <div> (ReasonReact.stringToElement ("Hello " ^ name ^
    "!!")) </div>
  };
};

ReactDOMRe.renderToElementWithId <Root name="Kyle" /> "react-app";
