defmodule PhoenixReasonWeb.TodoChannel do
  use Phoenix.Channel

  @default_todos []
  def join("todo", _params, socket) do
    {:ok, @default_todos, socket}
  end
end
