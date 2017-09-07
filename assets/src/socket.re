let socket = Phx.initSocket "/socket"
  |> Phx.connectSocket;

let channel = socket
  |> Phx.initChannel "todo";
