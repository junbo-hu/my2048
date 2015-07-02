#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

#define NROWS 4
#define NCOLS NROWS

typedef unsigned int tile_t;

typedef struct game_t{

	int turns,score,max_tile;
	tile_t board[NROWS][NCOLS];
}game_t;


int place_tile(struct game_t *game)
{
	tile_t *lboard = (tile_t *)game->board;
	int i, num_zeros = 0;

	//Walk the board and count the number of empty tiles
	for(i = 0;i < NROWS * NCOLS; i++){
		num_zeros += lboard[i] ? 0 : 1;
	}

	if(!num_zeros){
		return -1;
	}

	//Choose the insertion point
	int loc = random() % num_zeros;

	//Find the insersion point and place the new tile
	for(i = 0;i < NROWS * NCOLS; i++){
		if(!lboard[i] && !(loc--)){
			lboard[i] = random()%10?1:2;
			return 0;
		}
	}


	return -1;

}

void print_tile(int tile)
{

}

void print_game(struct game_t *game)
{

}

int combine_left(struct game_t *game)
{
	return 1;
}

int deflate_left(tile_t row[NCOLS])
{
	return 1;

}

void rotate_clockwise(struct game_t *game)
{
	tile_t buf[NROWS][NCOLS];
	memcpy(buf,game->board,sizeof(game->board));

	int r, c;
	for(r = 0;r < NROWS;r++){
		
	}
}

void move_left(struct game_t *game)
{

}

int lose_game(struct game_t test_game)
{
	return 1;
}

void init_curses()
{
	int bg = 0;
	initscr(); //curses init
	start_color();
	cbreak(); //curses don't wait for enter key
	noecho(); //curses don't echo the pressed key
	keypad(stdscr,TRUE);
	clear();//curses clear screen and send cursor to (0,0)
	refresh();	
	curs_set(0);

	bg = use_default_colors() == OK ? -1:0;
	init_pair(1,COLOR_RED,bg);
	init_pair(2,COLOR_GREEN,bg);
	init_pair(3,COLOR_YELLOW,bg);
	init_pair(4,COLOR_BLUE, bg);
	init_pair(5,COLOR_MAGENTA,bg);
	init_pair(6,COLOR_CYAN,bg);
}

int max_tile(tile_t *lboard)
{
	int i , ret = 0;
	for(i = 0;i < NROWS * NCOLS; i++){
		ret = max(ret, lboard[i]);
	}
	return ret;
}

int main()
{
	init_curses();
	const char *exit_msg = "";
	srandom(time(NULL));

	struct game_t game = {0};
	int last_turn = game.turns;
	place_tile(&game);
	place_tile(&game);
	
	while(1){
		print_game(&game);
		if(lose_game(game)){
			exit_msg = "lost";
			goto lose;
		}

		last_turn = game.turns;
		
		switch(getch()){
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		case 'q':
			exit_msg = "quit";
			goto end;
		}

		if(last_turn != game.turns)
			place_tile(&game);
	}	

lose:
	move(7, 0);
	printw("You lose! Press q to quit.");
	while(getch() != 'q');
end:
	endwin();
	printf("You %s after scroing %d points in %d turns,with largest tile%d\n",exit_msg,game.score,game.turns,1 << max_tile((tile_t *)game.board));

	return 0;
}
