/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:14:34 by geonwule          #+#    #+#             */
/*   Updated: 2023/07/17 12:27:09 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MINI_WIDTH (WIN_WIDTH / 4)
# define MINI_HEIGHT (WIN_HEIGHT / 4)
# define TEX_WIDTH 400	
# define TEX_HEIGHT 400
# define MAP_HEIGHT 15
# define MAP_WIDTH 34
# define BUFFER_SIZE 1
# define ZEN_RATE 2

# define M_PLAYER "texture/minimap/player_10.xpm"
# define M_EMPTY "texture/minimap/empty_10.xpm"
# define M_WALL "texture/minimap/wall_10.xpm"
# define M_MONSTER "texture/minimap/monster_10.xpm"
# define M_DOOR "texture/minimap/door_10.xpm"
# define M_POTION "texture/minimap/potion_10.xpm"
# define M_DIR "texture/minimap/dir_10.xpm"
# define M_NPC "texture/minimap/npc.xpm"

# define N_QUEST1 "texture/npc/quest_start.xpm"
# define N_QUEST2 "texture/npc/quest_ing.xpm"
# define N_QUEST3 "texture/npc/quest_end.xpm"

# define E_DEAD "texture/etc/dead.xpm"
# define E_DAMAGE "texture/etc/damage.xpm"
# define E_AIM "texture/etc/aim.xpm"
# define E_WARNING "texture/etc/warning.xpm"
# define E_HAND1 "texture/etc/hand1.xpm"
# define E_HAND2 "texture/etc/hand2.xpm"

# define U_HP1 "texture/underbar/hp1.xpm"
# define U_HP2 "texture/underbar/hp2.xpm"
# define U_HP3 "texture/underbar/hp3.xpm"
# define U_EXP1 "texture/underbar/exp1.xpm"
# define U_EXP2 "texture/underbar/exp2.xpm"
# define U_LEVEL "texture/underbar/level.xpm"

# define R_DOOR "texture/ray/door.xpm"
# define R_MONSTER "texture/ray/monster.xpm"
# define R_POTION "texture/ray/potion.xpm"
# define R_NPC "texture/ray/npc.xpm"

enum	e_pos
{
	X = 0,
	Y = 1,
}	;

enum	e_return_value
{
	RETURN_SUCCESS = 0,
	RETURN_FAILURE,
}	;

enum	e_texture
{
	TEX_NUM = 8,
	TEX_NO = 0,
	TEX_SO,
	TEX_EA,
	TEX_WE,
	TEX_DOOR,
	TEX_MONSTER,
	TEX_POTION,
	TEX_NPC,
}	;

enum	e_key
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	B = 11,
	R = 15,
	Q = 12,
	E = 14,
	P = 35,
	N = 45,
	M = 46,
	ESC = 53,
	DEAD = 3,
	LEFT = 124,
	RIGHT = 123,
	SPACE = 49,
	TAB = 48,
}	;

enum	e_hook_event
{
	KEY_PRESS = 2,
	PRESS_MASK = 1L<<0,
	KEY_RELEASE = 3,
	RELEASE_MASK = 1L<<1,
	MOUSE_BUTTON = 4,
	BUTTON_MASK = 1L<<2,
	MOUSE_MOVE = 6,
	MOVE_MASK = 1L<<6,
	WINDOW_DESTROY = 17,
	DESTROY_MASK = 0,
}	;

#endif