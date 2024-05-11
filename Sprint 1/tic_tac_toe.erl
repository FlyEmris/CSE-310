-module(tic_tac_toe).
-export([start/0]).


-define(empty, empty).
% Function to start the game
start() ->
    Board = [[?empty, ?empty, ?empty],
             [?empty, ?empty, ?empty],
             [?empty, ?empty, ?empty]],
    % Start the game loop (begins with x)
    game_loop(Board, x).

% Game loop function
game_loop(Board, Player) ->
    % Display the current board
    display_board(Board),
    % Ask the current player to enter their move
    io:format("~n~p's turn. Enter a row (1-3) and column (1-3): ", [Player]),
    % Read the row and column input from the player
    {ok, [Row, Column]} = io:fread(">", "~d ~d"),
    % Make the move on the board
    case make_move(Board, Player, Row, Column) of
        % If the move is valid, check for a win or draw
        {ok, NewBoard} ->
            case check_win(NewBoard, Player) of
                % If the current player wins, display the winner and end the game
                true ->
                    display_board(NewBoard),
                    io:format("~n~p wins!~n", [Player]);
                % If the game is a draw, display the draw message and end the game
                false ->
                    case is_draw(NewBoard) of
                        true ->
                            display_board(NewBoard),
                            io:format("~nThe game is a draw.~n", []);
                        % If the game is not a draw, continue the game loop with the next player
                        false ->
                            game_loop(NewBoard, next_player(Player))
                    end
            end;
        % If the move is invalid, display an error message and repeat the current player's turn
        {error, Reason} ->
            io:format("~nInvalid move: ~s~n", [Reason]),
            game_loop(Board, Player)
    end.

% Function to display the current board
display_board(Board) ->
    % Print the column numbers
    io:format("~n   1 2 3~n", []),
    % Call display_rows to print each row
    display_rows(Board, 1).

% Function to display each row of the board
display_rows([], _) ->
    io:format("~n", []);
display_rows([Row | Rest], N) ->
    % Print the row number and the cells in the row
    io:format("~p |~p~p~p~n", [N, display_cell(Row, 1), display_cell(Row, 2), display_cell(Row, 3)]),
    % Recursive call to print the next row
    display_rows(Rest, N+1).

% Function to display a single cell of the board
display_cell(Row, Column) ->
    % Check the value of the cell and return a string representation
    case lists:nth(Column, Row) of
        empty -> " ";
        x -> "X";
        o -> "O"
    end.

make_move(Board, Player, Row, Column) when Row >= 1, Row =< 3, Column >= 1, Column =< 3 ->
    % Check if the cell is empty
    case lists:nth(Row, Board) of
        RowList when length(RowList) == 3 ->
            case lists:nth(Column, RowList) of
                empty ->
                    % Update the board with the player's move
                    NewRow = lists:sublist(lists:nth(Row, Board), Column - 1) ++ [Player] ++ lists:nthtail(Column, lists:nth(Row, Board)),
                    NewBoard = lists:sublist(Board, Row - 1) ++ [NewRow] ++ lists:nthtail(Row, Board),
                    {ok, NewBoard};
                _ ->
                    {error, "Cell is already taken."}
            end;
        _ ->
            {error, "Row is out of bounds."}
    end;
make_move(_, _, _, _) ->
    {error, "Column is out of bounds."}.


% Function to check if a player has won the game
check_win(Board, Player) ->
    % Check rows for a win
    check_rows(Board, Player) orelse
    % Check columns for a win
    check_columns(Board, Player) orelse
    % Check diagonals for a win
    check_diagonals(Board, Player).

% Function to check rows for a win
check_rows(Board, Player) ->
    % Check each row for a win
    lists:any(fun(Row) -> Row == [Player, Player, Player] end, Board).

% Function to check columns for a win
check_columns(Board, Player) ->
    check_columns(Board, Player, 1).

check_columns(Board, Player, N) when N =< 3 ->
    case lists:nth(N, Board) of
        [Cell1, Cell2, Cell3] when Cell1 == Player, Cell2 == Player, Cell3 == Player ->
            true;
        _ ->
            check_columns(Board, Player, N+1)
    end;
check_columns(_, _, _) ->
    false.


% Function to check diagonals for a win
check_diagonals(Board, Player) ->
    % Check the main diagonal
    Diagonal1 = [lists:nth(1, lists:nth(1, Board)), lists:nth(2, lists:nth(2, Board)), lists:nth(3, lists:nth(3, Board))],
    % Check the other diagonal
    Diagonal2 = [lists:nth(3, lists:nth(1, Board)), lists:nth(2, lists:nth(2, Board)), lists:nth(1, lists:nth(3, Board))],
    % Check if either diagonal is a win
    Diagonal1 == [Player, Player, Player] orelse
    Diagonal2 == [Player, Player, Player].

% Function to check if the game is a draw
is_draw(Board) ->
    % Check if there are any empty cells left
    not lists:any(fun(Row) -> lists:any(fun(Cell) -> Cell == empty end, Row) end, Board).

% Function to switch players
next_player(x) -> o;
next_player(o) -> x.