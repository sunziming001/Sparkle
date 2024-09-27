#ifndef _SKEYBOARD_EVENT_H
#define _SKEYBOARD_EVENT_H

#include "SConfig.h"
#include "SEvent.h"
#include "SFlags.h"

enum class SKeyboardStatus
{
	None,
	Press,
	Release,
};

enum class SKeyboardModifier
{
	None = 0,
	Shift = 0x01,
	Ctrl = 0x02,
	Alt	= 0x04,
};

enum class SKeyboardKey
{
	None,

	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,

	Key_0,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	
	Key_Numpad_0,
	Key_Numpad_1,
	Key_Numpad_2,
	Key_Numpad_3,
	Key_Numpad_4,
	Key_Numpad_5,
	Key_Numpad_6,
	Key_Numpad_7,
	Key_Numpad_8,
	Key_Numpad_9,
	
	Key_Up,
	Key_Down,
	Key_Left,
	Key_Right,

	Key_F1,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,

	Key_Shift,
	Key_Ctrl,
	Key_Alt,

};


class SPARKLE_API SKeyboardEvent :public SEvent
{
public:
	SKeyboardEvent(SKeyboardKey key,
		SKeyboardStatus status,
		SFlags<SKeyboardModifier> modifiers);
	virtual ~SKeyboardEvent();
	SKeyboardKey getKey()const;
	SFlags<SKeyboardModifier> getModifiers()const;
	SKeyboardStatus getStatus()const;

	SStringPtr toLogString()const override;
private:
	DECLARE_INNER_DATA(d_);

};


#endif