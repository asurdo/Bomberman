#include "BomberMan.h"
#include<iostream>
using namespace std;

void Init(void)
{
	api_set_group_name("Asudo");
}

void AI(const Game *game, Operator op[PLAYER_NUM])
{
	int id = game->grpid;
	Coord po;
	if (!id)
	{
		po.x = 15;
	}
	else
	{
		po.x = 1;
	}
	po.y = 8;
	int bommmm[17][17];
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			bommmm[i][j] = 0;
		}
	}
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			if (game->map[i][j].type == BOMB)
			{
				bommmm[i][j] = 2;
				if (game->map[i + 1][j].type == BLANK&&bommmm[i + 1][j] != 2 && (i + 1 < 17))
				{
					bommmm[i + 1][j] = 1;
					if (bommmm[i + 2][j] != 2 && game->map[i + 2][j].type == BLANK && (i + 2 < 17))
					{
						bommmm[i + 2][j] = 1;
					}
				}
				if (game->map[i - 1][j].type == BLANK&&bommmm[i - 1][j] != 2 && i - 1 > 0)
				{
					bommmm[i - 1][j] = 1;
					if (bommmm[i - 2][j] != 2 && game->map[i - 2][j].type == BLANK && i - 2 > 0)
					{
						bommmm[i - 2][j] = 1;
					}
				}
				if (game->map[i][j + 1].type == BLANK&&bommmm[i][j + 1] != 2 && (j + 1 < 17))
				{
					bommmm[i][j + 1] = 1;
					if (bommmm[i][j + 2] != 2 && game->map[i][j + 2].type == BLANK && (j + 2 < 17))
					{
						bommmm[i][j + 2] = 1;
					}
				}
				if (game->map[i][j - 1].type == BLANK&&bommmm[i][j - 1] != 2 && (j - 1 > 0))
				{
					bommmm[i][j - 1] = 1;
					if (bommmm[i][j - 2] != 2 && game->map[i][j - 2].type == BLANK && (j - 2 > 0))
					{
						bommmm[i][j - 2] = 1;
					}
				}
			}
		}
	}
	int yx = 0;
	for (int m = 0; m < 3; m++)
	{
		if (game->group[id].player[m].pos.y < 8)
		{
			++yx;
		}
	}
	int xy = 0;
	for (int m = 0; m < 3; m++)
	{
		if (game->group[id==0].player[m].pos.y < 8)
		{
			++xy;
		}
	}
	int a3=0;
	for (int i = 0; i < 3; i++)
	{
		Player pi = game->group[id].player[i];
		if (!pi.life_value) continue;
		if (pi.pos.x > po.x)
		{
			if (i == 2 && game->group[id].player[2].life_value&&game->group[id].player[1].pos.x<11)
			{
				a3 = 1;
				continue;
			}
			if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
			{
				op[i] = LEFT;
			}
			else if (pi.pos.y > po.y)
			{
				if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK)
				{
					op[i] = UP;
				}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK)
				{
					op[i] = DOWN;
				}
				//else if (pi.pos.y - 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[i] = UP;
				}
				else
				{
					op[i] = PUT;
				}
			}
			else if (pi.pos.y < po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK)
				{
					op[i] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK)
				{
					op[i] = UP;
				}
				//else if (pi.pos.y + 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
				{
					op[i] = DOWN;
				}
				else
				{
					op[i] = PUT;
				}
			}
			else if (pi.pos.y == po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&yx)
				{
					op[i] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[i] = UP;
				}
				else
				{
					op[i] = PUT;
				}
			}
		}
		else if (pi.pos.x < po.x)
		{
			if (i == 2 && game->group[id].player[2].life_value&&game->group[id].player[1].pos.x>5)
			{
				a3 = 1;
				continue;
			}
			if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
			{
				op[i] = RIGHT;
			}
			else if (pi.pos.y > po.y)
			{
				if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK)
				{
					op[i] = UP;
				}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x + 1].type == BLANK)
				{
					op[i] = DOWN;
				}
				//else if (pi.pos.y - 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[i] = UP;
				}
				else
				{
					op[i] = PUT;
				}
			}
			else if (pi.pos.y < po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x + 1].type == BLANK)
				{
					op[i] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK)
				{
					op[i] = UP;
				}
				//else if (pi.pos.y + 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
				{
					op[i] = DOWN;
				}
				else
				{
					op[i] = PUT;
				}
			}
			else if (pi.pos.y == po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&yx)
				{
					op[i] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[i] = UP;
				}
				else
				{
					op[i] = PUT;
				}
			}
		}
		else if (pi.pos.x == po.x)
		{
			if (pi.pos.y == 7 || pi.pos.y == 9)
			{
				op[i] = PUT;
			}
			else if (pi.pos.y < 8 && game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
			{
				op[i] = DOWN;
			}
			else if (pi.pos.y > 8 && game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
			{
				op[i] = UP;
			}
			else if (pi.pos.y > 8 && game->map[pi.pos.y - 1][pi.pos.x].type == WOOD)
			{
				op[i] = PUT;
			}
			else if (pi.pos.y < 8 && game->map[pi.pos.y + 1][pi.pos.x].type == WOOD)
			{
				op[i] = PUT;
			}
		}
		/*for (int mm = 0; mm < 3; mm++)
		{
			if (!game->group[id == 0].player[mm].life_value) continue;
			if (((game->group[id == 0].player[mm].pos.x == pi.pos.x&&game->group[id == 0].player[mm].pos.y == pi.pos.y) ||
				(game->group[id == 0].player[mm].pos.x - 1 == pi.pos.x&&game->group[id == 0].player[mm].pos.y == pi.pos.y) ||
				(game->group[id == 0].player[mm].pos.x + 1 == pi.pos.x&&game->group[id == 0].player[mm].pos.y == pi.pos.y) ||
				(game->group[id == 0].player[mm].pos.x == pi.pos.x&&game->group[id == 0].player[mm].pos.y - 1 == pi.pos.y) ||
				(game->group[id == 0].player[mm].pos.x == pi.pos.x&&game->group[id == 0].player[mm].pos.y + 1 == pi.pos.y)) &&
				pi.bomb_num)
			{
				op[i] = PUT;
			}
		}*/
	}
	/*int va[3] = {0};
	for (int i = 0; i < 3; i++)
	{
		Player pi = game->group[id].player[i];
		if (!pi.life_value||!va[i]) continue;
		if (i == 3 && game->group[id].player[2].life_value)continue;
		for (int j = 0; j < 3; j++)
		{
			Player pi1 = game->group[id].player[i];
			if (!pi1.life_value||va[j]||i==j) continue;
			if (pi1.pos.x == pi.pos.x&&pi1.pos.y == pi.pos.y)
			{
				op[j] = NOP;
				va[i] = va[j] = 1;
			}
		}
	}*/
	for (int i = 0; i < 3; i++)
	{
		Player pi = game->group[id].player[i];
		if (!pi.life_value) continue;
		if (bommmm[pi.pos.y][pi.pos.x])
		{
			if (pi.pos.x > po.x)
			{
				if (pi.pos.y >= po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
				}
				if (bommmm[pi.pos.y][pi.pos.x] == 2)
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK && (game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK || game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK))
					{
						op[i] = LEFT;
					}
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 3].type == BLANK)
					{
						op[i] = LEFT;
					}
				}
				if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 2])
				{
					op[i] = LEFT;
				}
				else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x - 1])
				{
					op[i] = LEFT;
				}
				else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x - 1])
				{
					op[i] = LEFT;
				}
				if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
				{
					op[i] = LEFT;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
				{
					op[i] = UP;
				}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
				{
					op[i] = DOWN;
				}
				else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
				{
					op[i] = RIGHT;
				}
				if (pi.pos.y > po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
				}
			}
			else if (pi.pos.x < po.x)
			{
				if (pi.pos.y >= po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
				}
				if (bommmm[pi.pos.y][pi.pos.x] == 2)
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK && (game->map[pi.pos.y + 1][pi.pos.x + 1].type == BLANK || game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK))
					{
						op[i] = RIGHT;
					}
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 3].type == BLANK)
					{
						op[i] = RIGHT;
					}
				}
				if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 2])
				{
					op[i] = RIGHT;
				}
				else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x + 1])
				{
					op[i] = RIGHT;
				}
				else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x + 1])
				{
					op[i] = RIGHT;
				}
				else if (game->map[pi.pos.y][pi.pos.x+1].type == BLANK&&game->map[pi.pos.y][pi.pos.x+2].type == BLANK&&game->map[pi.pos.y][pi.pos.x+3].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x+3])
				{
					op[i] = RIGHT;
				}
				else if (pi.pos.y > po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
				}
			}
			else if (pi.pos.x == po.x)
			{
				if (pi.pos.y >= po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
					{
						op[i] = DOWN;
					}
				}
				if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 2])
				{
					op[i] = RIGHT;
				}
				else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x + 1])
				{
					op[i] = RIGHT;
				}
				else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x + 1])
				{
					op[i] = RIGHT;
				}
				if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 2])
				{
					op[i] = LEFT;
				}
				else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x + 1])
				{
					op[i] = LEFT;
				}
				else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x + 1])
				{
					op[i] = LEFT;
				}
				if (pi.pos.y > po.y)
				{
					if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
				}
				else
				{
					if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x + 1])
					{
						op[i] = RIGHT;
					}
					else if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&!bommmm[pi.pos.y][pi.pos.x - 1])
					{
						op[i] = LEFT;
					}
					else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y - 1][pi.pos.x])
					{
						op[i] = UP;
					}
					else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&!bommmm[pi.pos.y + 1][pi.pos.x])
					{
						op[i] = DOWN;
					}
				}
			}
		}
		if (op[i] == LEFT&&bommmm[pi.pos.y][pi.pos.x - 1] && !bommmm[pi.pos.y][pi.pos.x])
		{
			op[i] = NOP;
			if (pi.pos.x > po.x&&game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x - 2] == 0)
			{
				op[i] = LEFT;
			}
			else if (pi.pos.x < po.x&&game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x + 2] == 0)
			{
				op[i] = RIGHT;
			}
		}
		else if (op[i] == RIGHT&&bommmm[pi.pos.y][pi.pos.x + 1] && !bommmm[pi.pos.y][pi.pos.x])
		{
			op[i] = NOP;
			if (pi.pos.x > po.x&&game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x - 2] == 0)
			{
				op[i] = LEFT;
			}
			else if (pi.pos.x < po.x&&game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x + 2] == 0)
			{
				op[i] = RIGHT;
			}
		}
		else if (op[i] == UP&&bommmm[pi.pos.y - 1][pi.pos.x] && !bommmm[pi.pos.y][pi.pos.x])
		{
			op[i] = NOP;
			if (pi.pos.x > po.x&&game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x - 2] == 0)
			{
				op[i] = LEFT;
			}
			else if (pi.pos.x < po.x&&game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x + 2] == 0)
			{
				op[i] = RIGHT;
			}
		}
		else if (op[i] == DOWN&&bommmm[pi.pos.y + 1][pi.pos.x] && !bommmm[pi.pos.y][pi.pos.x])
		{
			op[i] = NOP;
			if (pi.pos.x > po.x&&game->map[pi.pos.y][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x - 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x - 2] == 0)
			{
				op[i] = LEFT;
			}
			else if (pi.pos.x < po.x&&game->map[pi.pos.y][pi.pos.x + 1].type == BLANK&&game->map[pi.pos.y][pi.pos.x + 2].type == BLANK&&bommmm[pi.pos.y][pi.pos.x + 2] == 0)
			{
				op[i] = RIGHT;
			}
		}	
	}
	if (a3)
	{
		Player pi = game->group[id].player[2];
		Coord poss = po;
		poss.x = 16 - po.x;
		if (pi.pos.x > poss.x)
		{
			if (game->map[pi.pos.y][pi.pos.x - 1].type == BLANK)
			{
				op[2] = LEFT;
			}
			else if (pi.pos.y > po.y)
			{
				if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK|| game->map[pi.pos.y - 1][pi.pos.x - 1].type == HOME))
				{
					op[2] = UP;
				}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK|| game->map[pi.pos.y + 1][pi.pos.x - 1].type == HOME))
				{
					op[2] = DOWN;
				}
				//else if (pi.pos.y - 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[2] = UP;
				}
				else
				{
					op[2] = NOP;
				}
			}
			else if (pi.pos.y < po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK&&game->map[pi.pos.y + 1][pi.pos.x - 1].type == HOME))
				{
					op[2] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK||game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK))
				{
					op[2] = UP;
				}
				//else if (pi.pos.y + 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
				{
					op[2] = DOWN;
				}
				else
				{
					op[2] = NOP;
				}
			}
			else if (pi.pos.y == po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&xy<2)
				{
					op[2] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[2] = UP;
				}
				else
				{
					op[2] = NOP;
				}
			}
		}
		else if (pi.pos.x < po.x)
		{
			if (game->map[pi.pos.y][pi.pos.x + 1].type == BLANK)
			{
				op[2] = RIGHT;
			}
			else if (pi.pos.y > po.y)
			{
				if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK && (game->map[pi.pos.y - 1][pi.pos.x + 1].type == BLANK || game->map[pi.pos.y - 1][pi.pos.x + 1].type == HOME))
				{
					op[2] = UP;
				}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK|| game->map[pi.pos.y + 1][pi.pos.x - 1].type == HOME))
				{
					op[2] = DOWN;
				}
				//else if (pi.pos.y - 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[2] = UP;
				}
				else
				{
					op[2] = NOP;
				}
			}
			else if (pi.pos.y < po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK||game->map[pi.pos.y + 1][pi.pos.x - 1].type == BLANK))
				{
					op[2] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK&&(game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK|| game->map[pi.pos.y - 1][pi.pos.x - 1].type == BLANK))
				{
					op[2] = UP;
				}
				//else if (pi.pos.y + 1 == 8)
				//{
				//	op[i] = PUT;
				//}
				else if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
				{
					op[2] = DOWN;
				}
				else
				{
					op[2] = NOP;
				}
			}
			else if (pi.pos.y == po.y)
			{
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK&&xy<2)
				{
					op[2] = DOWN;
				}
				else if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[2] = UP;
				}
				else
				{
					op[2] = NOP;
				}
			}
		}
		else if (pi.pos.x == po.x)
		{
			if (pi.pos.y > 8)
			{
				if (game->map[pi.pos.y - 1][pi.pos.x].type == BLANK)
				{
					op[2] = UP;
				}
				else
				{
					op[2] = NOP;
				}
				if (game->map[pi.pos.y + 1][pi.pos.x].type == BLANK)
				{
					op[2] = DOWN;
				}
				else
				{
					op[2] = NOP;
				}
			}
		}
	}
}