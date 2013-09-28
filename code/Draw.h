#ifndef DRAW_H
#define DRAW_H

#include "DrawLine.h"
#include "DrawPoly.h"
#include "DrawRect.h"
#include "DrawRoundRect.h"
#include "DrawEllipse.h"
#include "DrawSelect.h"
#include "DrawCurve.h"
#include "DrawFilling.h"

#define DRAW_SELECT				1
#define DRAW_ERASER				2
#define DRAW_FILLING			3
#define DRAW_SAMPLING			4
#define DRAW_PEN				5
#define DRAW_BRUSH				6
#define DRAW_LINE				7
#define DRAW_CURVE				8
#define DRAW_RECTANGLE			9
#define DRAW_POLYGON			10
#define DRAW_ELLIPSE			11
#define DRAW_ROUNDRECT			12

#define COLOR_BLACK				0x00000000
#define COLOR_WHITE             0x00ffffff
#define COLOR_GREEN				0x0000ff00
#define COLOR_BLUE              0x00ff0000
#define COLOR_DARKGREEN         0x00008000
#define COLOR_YELLOW            0x0000ffff
#define COLOR_PINK              0x00ff00ff
#define COLOR_DARKRED           0x00000080
#define COLOR_GRAY              0x00c0c0c0
#define COLOR_PURPLE            0x00800080
#define COLOR_DARKYELLOW        0x00008080
#define COLOR_CYAN				0x00ffff00
#define COLOR_DARKCYAN			0x00808000
#define COLOR_DARKBLUE          0x00800000
#define COLOR_DARKGRAY			0x00808080
#define COLOR_RED               0x000000ff

#define STD_WIDTH				500
#define STD_HEIGHT				280
#define STD_SCROLLED_WIDTH		600
#define STD_SCROLLED_HEIGHT		430

#endif	// DRAW_H