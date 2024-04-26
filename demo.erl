%This function will load and run a file in Erlang.

-module(demo).
-export([hello/0]).

hello() -> io:format("Hello world!~n").
