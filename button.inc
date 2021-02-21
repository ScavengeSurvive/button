// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_button
	#undef _inc_button
#endif
// custom include-guard to ensure we don't duplicate
#if defined _button_included
	#endinput
#endif
#define _button_included

#include <a_samp>
#include <logger>
#include <errors>
#include <YSI_Coding\y_iterate>
#include <YSI_Coding\y_timers>
#include <streamer>
#include <action-text>
#include <mathutil>

#include <YSI_Coding\y_hooks>


/*==============================================================================

	Constant Definitions, Function Declarations and Documentation

==============================================================================*/


// Maximum amount of buttons that can be created.
#if !defined BTN_MAX
	#define BTN_MAX (Button:8192)
#endif

// Maximum string length for labels and action-text strings.
#if !defined BTN_MAX_TEXT
	#define BTN_MAX_TEXT (128)
#endif

// Default maximum stream range for button label text.
#if !defined BTN_DEFAULT_STREAMDIST
	#define BTN_DEFAULT_STREAMDIST (4.0)
#endif

// Maximum amount of buttons to record the player being near to.
#if !defined BTN_MAX_INRANGE
	#define BTN_MAX_INRANGE (8)
#endif

// A value to identify streamer object EXTRA_ID data array type.
#if !defined BTN_STREAMER_AREA_IDENTIFIER
	#define BTN_STREAMER_AREA_IDENTIFIER (100)
#endif

// Validity check constant
#define INVALID_BUTTON_ID (Button:-1)


DEFINE_HOOK_REPLACEMENT(Button , Btn);


// Functions


forward Button:CreateButton(Float:x, Float:y, Float:z, const text[], world = 0, interior = 0, Float:areasize = 1.0, label = 0, const labeltext[] = "", labelcolour = 0xFFFF00FF, Float:streamdist = BTN_DEFAULT_STREAMDIST, testlos = true);
/*
# Description
Creates an interactive button players can activate by pressing F.

# Parameters
- x, y, z: World position.
- text: Message box text for when the player approaches the button.
- world: The virtual world to show the button in.
- interior: The interior world to show the button in.
- areasize: Size of the button's detection area.
- label: Determines whether a 3D Text Label should be at the button.
- labeltext: The text that the label should show.
- labelcolour: The colour of the label.
- streamdist: Stream distance of the label.
- testlos: test line of sight for the label.

# Returns
Button ID handle of the newly created button or INVALID_BUTTON_ID if another
button cannot be created due to BTN_MAX limit.
*/

forward DestroyButton(Button:id);
/*
# Description
Destroys a button.

# Returns
Boolean to indicate success or failure.
*/

forward bool:IsValidButton(Button:id);
/*
# Description
Checks if id is a valid button ID handle.
*/

forward GetButtonArea(Button:id);
/*
# Description
Returns the streamer area ID used by a button.
*/

forward SetButtonArea(Button:id, areaid);
/*
# Description
Updates a button's streamer area ID. Note that this does not remove the existing
area from memory.

# Returns
Boolean to indicate success or failure.
*/

forward SetButtonLabel(Button:id, const text[], colour = 0xFFFF00FF, Float:range = BTN_DEFAULT_STREAMDIST, testlos = true);
/*
# Description
Creates a 3D Text Label at the specified button ID handle, if a label already
exists it updates the text, colour and range.
*/

forward DestroyButtonLabel(Button:id);
/*
# Description
Removes the label from a button.

# Returns
Boolean to indicate success or failure. 2 if the button did not have a label.
*/

forward GetButtonPos(Button:id, &Float:x, &Float:y, &Float:z);
/*
# Description
Stores the button's X, Y and Z into parameters.

# Returns
Boolean to indicate success or failure.
*/

forward SetButtonPos(Button:id, Float:x, Float:y, Float:z);
/*
# Description
Changes the button position (area, label, etc).

# Returns
Boolean to indicate success or failure.
*/

forward GetButtonSize(Button:id, &Float:size);
/*
# Description
Returns the size of the specified button's dynamic area.

# Returns
Boolean to indicate success or failure.
*/

forward SetButtonSize(Button:id, Float:size);
/*
# Description
Sets a button's detection area size.

# Returns
Boolean to indicate success or failure.
*/

forward GetButtonWorld(Button:id);
/*
# Description
Returns the virtual world that a button exists in or -1 if the button is invalid.
*/

forward SetButtonWorld(Button:id, world);
/*
# Description
Updates a button's virtual world. Moves all streamer entities to the world too.

# Returns
Boolean to indicate success or failure.
*/

forward GetButtonInterior(Button:id);
/*
# Description
Returns the interior that a button exists in or -1 if the button is invalid.
*/

forward SetButtonInterior(Button:id, interior);
/*
# Description
Updates a button's interior. Moves all streamer entities to the interior too.

# Returns
Boolean to indicate success or failure.
*/

forward GetButtonText(Button:id, text[]);
/*
# Description
Returns the text assigned to a button that appears on-screen when a player walks near it.
*/

forward SetButtonText(Button:id, const text[]);
/*
# Description
Updates the text that appears on-screen when a player walks near the button.

# Returns
Boolean to indicate success or failure.
*/

forward SetButtonExtraData(Button:id, data);
/*
# Description
Sets the button's extra data field, this is one cell of blank space allocated for each button.

# Returns
Boolean to indicate success or failure.
*/

forward GetButtonExtraData(Button:id, &data);
/*
# Description
Retrieves the integer assigned to the button set with SetButtonExtraData.
*/

forward GetPlayerPressingButton(playerid);
/*
# Description
Returns the ID of the button that the player is currently pressing. This will
only return a value while playerid is holding down the interact key at a button.
*/

forward GetPlayerButtonID(playerid, &Button:id);
/*
# Description
Returns the closest button that a player is standing within the area of.
*/

forward GetPlayerButtonList(playerid, Button:list[], &size, bool:validate = false);
/*
# Description
Returns a list of buttons that a player is standing in the areas of.

# Parameters
- playerid: Player to get a list of buttons from.

- list: Array to store the buttons in (Must be BTN_MAX_INRANGE size)

- size: Stores the amount of buttons in the list.

- validate: If true, the function will check if the player is actually in each
  button in the list. This is a small workaround for a larger problem that is
  currently unknown that results in a button not being removed from a player's
  list when they leave the area for it.

# Returns
Boolean to indicate success or failure.
*/

forward GetPlayerAngleToButton(playerid, Button:id, &Float:angle);
/*
# Description
Returns the angle in degrees from a player to a button.
*/

forward GetButtonAngleToPlayer(playerid, Button:id, &Float:angle);
/*
# Description
Returns the angle in degrees from a button to a player.
*/


// Events


forward OnButtonPress(playerid, Button:id);
/*
# Called
When a player presses the F/Enter key while at a button.

# Returns
If the player is within the trigger zone of multiple buttons, return 1 to
cancel calling OnButtonPress for any other buttons.
*/

forward OnButtonRelease(playerid, Button:id);
/*
# Called
When a player releases the F/Enter key after pressing it while at a button.
*/

forward OnPlayerEnterButtonArea(playerid, Button:id);
/*
# Called
When a player enters the dynamic streamed area of a button.
*/

forward OnPlayerLeaveButtonArea(playerid, Button:id);
/*
# Called
When a player leaves the dynamic streamed area of a button.
*/


/*==============================================================================

	Setup

==============================================================================*/


enum E_BTN_DATA {
	btn_area,
	Text3D:btn_label,
	Float:btn_posX,
	Float:btn_posY,
	Float:btn_posZ,
	Float:btn_size,
	btn_world,
	btn_interior,
	btn_text[BTN_MAX_TEXT],
	btn_exData
}

enum e_button_range_data {
	Button:btn_buttonId,
	Float:btn_distance
}


static
	btn_Data[BTN_MAX][E_BTN_DATA],
	Button:btn_Near[MAX_PLAYERS][BTN_MAX_INRANGE],
	Iterator:btn_NearIndex[MAX_PLAYERS]<BTN_MAX_INRANGE>,
	Button:btn_Pressing[MAX_PLAYERS];

const BTN_ITER_SIZE = _:BTN_MAX;
new Iterator:btn_Index<BTN_ITER_SIZE>;


/*==============================================================================

	Zeroing

==============================================================================*/


hook OnScriptInit() {
	Iter_Init(btn_NearIndex);

	for(new i; i < MAX_PLAYERS; i++) {
		btn_Pressing[i] = INVALID_BUTTON_ID;
	}

	return Y_HOOKS_CONTINUE_RETURN_0;
}

hook OnPlayerConnect(playerid) {
	Iter_Clear(btn_NearIndex[playerid]);

	btn_Pressing[playerid] = INVALID_BUTTON_ID;

	return Y_HOOKS_CONTINUE_RETURN_0;
}


/*==============================================================================

	Core Functions

==============================================================================*/


stock Button:CreateButton(
	Float:x, Float:y, Float:z, const text[],
	world = 0, interior = 0, Float:areasize = 1.0, label = 0,
	const labeltext[] = "", labelcolour = 0xFFFF00FF, Float:streamdist = BTN_DEFAULT_STREAMDIST, testlos = true
) {
	new Button:id = Button:Iter_Free(btn_Index);

	if(_:id == ITER_NONE) {
		err("BTN_MAX limit reached");
		return INVALID_BUTTON_ID;
	}

	btn_Data[id][btn_area] = CreateDynamicSphere(x, y, z, areasize, world, interior);
	strcpy(btn_Data[id][btn_text], text, BTN_MAX_TEXT);
	btn_Data[id][btn_posX] = x;
	btn_Data[id][btn_posY] = y;
	btn_Data[id][btn_posZ] = z;
	btn_Data[id][btn_size] = areasize;
	btn_Data[id][btn_world] = world;
	btn_Data[id][btn_interior] = interior;

	if (label) {
		btn_Data[id][btn_label] = CreateDynamic3DTextLabel(labeltext, labelcolour, x, y, z, streamdist, .testlos = testlos, .worldid = world, .interiorid = interior, .streamdistance = streamdist);
	} else {
		btn_Data[id][btn_label] = Text3D:INVALID_3DTEXT_ID;
	}

	new data[2];

	data[0] = BTN_STREAMER_AREA_IDENTIFIER;
	data[1] = _:id;

	Streamer_SetArrayData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_EXTRA_ID, data, 2);

	Iter_Add(btn_Index, _:id);

	return id;
}

stock DestroyButton(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	foreach(new i : Player) {
		if(IsPlayerInDynamicArea(i, btn_Data[id][btn_area])) {
			process_LeaveDynamicArea(i, btn_Data[id][btn_area]);
		}
	}

	DestroyDynamicArea(btn_Data[id][btn_area]);

	if(IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
		DestroyDynamic3DTextLabel(btn_Data[id][btn_label]);
	}

	btn_Data[id][btn_area] = -1;
	btn_Data[id][btn_label] = Text3D:INVALID_3DTEXT_ID;
	btn_Data[id][btn_posX] = 0.0;
	btn_Data[id][btn_posY] = 0.0;
	btn_Data[id][btn_posZ] = 0.0;
	btn_Data[id][btn_size] = 0.0;
	btn_Data[id][btn_world] = 0;
	btn_Data[id][btn_interior] = 0;
	btn_Data[id][btn_text][0] = EOS;

	Iter_Remove(btn_Index, _:id);

	return 0;
}

stock bool:IsValidButton(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return false;
	}

	return true;
}


// btn_area
stock GetButtonArea(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return -1;
	}

	return btn_Data[id][btn_area];
}

stock SetButtonArea(Button:id, areaid) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	btn_Data[id][btn_area] = areaid;

	return 0;
}


// btn_label
stock SetButtonLabel(Button:id, const text[], colour = 0xFFFF00FF, Float:range = BTN_DEFAULT_STREAMDIST, testlos = true) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
		UpdateDynamic3DTextLabelText(btn_Data[id][btn_label], colour, text);
		return 0;
	}

	btn_Data[id][btn_label] = CreateDynamic3DTextLabel(
		text,
		colour,
		btn_Data[id][btn_posX],
		btn_Data[id][btn_posY],
		btn_Data[id][btn_posZ],
		range,
		_,
		_,
		testlos,
		btn_Data[id][btn_world],
		btn_Data[id][btn_interior],
		_,
		range
	);

	return 0;
}

stock DestroyButtonLabel(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(!IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
		return 2;
	}

	DestroyDynamic3DTextLabel(btn_Data[id][btn_label]);
	btn_Data[id][btn_label] = Text3D:INVALID_3DTEXT_ID;

	return 0;
}

// btn_posX
// btn_posY
// btn_posZ
stock GetButtonPos(Button:id, &Float:x, &Float:y, &Float:z) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	x = btn_Data[id][btn_posX];
	y = btn_Data[id][btn_posY];
	z = btn_Data[id][btn_posZ];

	return 0;
}

stock SetButtonPos(Button:id, Float:x, Float:y, Float:z) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 0;
	}

	Streamer_SetFloatData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_X, x);
	Streamer_SetFloatData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_Y, y);
	Streamer_SetFloatData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_Z, z);

	if(IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, btn_Data[id][btn_label], E_STREAMER_X, x);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, btn_Data[id][btn_label], E_STREAMER_Y, y);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, btn_Data[id][btn_label], E_STREAMER_Z, z);
	}

	btn_Data[id][btn_posX] = x;
	btn_Data[id][btn_posY] = y;
	btn_Data[id][btn_posZ] = z;

	return 1;
}

// btn_size
stock GetButtonSize(Button:id, &Float:size) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	size = btn_Data[id][btn_size];
	return 0;
}

stock SetButtonSize(Button:id, Float:size) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	Streamer_SetFloatData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_SIZE, size);
	btn_Data[id][btn_size] = size;

	return 0;
}

// btn_world
stock GetButtonWorld(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return -1;
	}

	return btn_Data[id][btn_world];
}

stock SetButtonWorld(Button:id, world) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(btn_Data[id][btn_world] != world) {
		Streamer_SetIntData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_WORLD_ID, world);

		if(IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, btn_Data[id][btn_label], E_STREAMER_WORLD_ID, world);
		}

		btn_Data[id][btn_world] = world;
	}

	return 0;
}

// btn_interior
stock GetButtonInterior(Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return -1;
	}

	return btn_Data[id][btn_interior];
}

stock SetButtonInterior(Button:id, interior) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(btn_Data[id][btn_interior] != interior) {
		Streamer_SetIntData(STREAMER_TYPE_AREA, btn_Data[id][btn_area], E_STREAMER_INTERIOR_ID, interior);

		if(IsValidDynamic3DTextLabel(btn_Data[id][btn_label])) {
			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, btn_Data[id][btn_label], E_STREAMER_INTERIOR_ID, interior);
		}

		btn_Data[id][btn_interior] = interior;
	}

	return 0;
}

// btn_text
stock GetButtonText(Button:id, text[]) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	text[0] = EOS;
	strcat(text, btn_Data[id][btn_text], BTN_MAX_TEXT);

	return 0;
}

stock SetButtonText(Button:id, const text[]) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	btn_Data[id][btn_text][0] = EOS;
	strcat(btn_Data[id][btn_text], text, BTN_MAX_TEXT);

	return 0;
}

// btn_exData
stock SetButtonExtraData(Button:id, data) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	btn_Data[id][btn_exData] = data;

	return 0;
}

stock GetButtonExtraData(Button:id, &data) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	data = btn_Data[id][btn_exData];

	return 0;
}

// btn_Pressing
stock GetPlayerPressingButton(playerid) {
	if(!(0 <= playerid < MAX_PLAYERS)) {
		return -1;
	}

	return btn_Pressing[playerid];
}

stock GetPlayerButtonID(playerid, &Button:id) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(Iter_Count(btn_NearIndex[playerid]) == 0) {
		return 2;
	}

	new
		Float:x,
		Float:y,
		Float:z,
		Button:curid,
		Float:curdistance,
		Float:closetsdistance = 99999.9;

	GetPlayerPos(playerid, x, y, z);

	foreach(new i : btn_NearIndex[playerid]) {
		curid = btn_Near[playerid][i];

		curdistance = GetDistance3D(x, y, z, btn_Data[curid][btn_posX], btn_Data[curid][btn_posY], btn_Data[curid][btn_posZ]);

		if(curdistance < closetsdistance) {
			closetsdistance = curdistance;
			id = curid;
		}
	}

	if(Iter_Contains(btn_Index, _:id)) {
		return 0;
	}

	return 3;
}

stock GetPlayerButtonList(playerid, Button:list[], &size, bool:validate = false) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(Iter_Count(btn_NearIndex[playerid]) == 0) {
		return 0;
	}

	// Validate whether or not the player is actually inside the areas.
	// Caused by a bug that hasn't been found yet, this is the quick workaround.
	if(validate) {
		foreach(new i : btn_NearIndex[playerid]) {
			if(!IsPlayerInDynamicArea(playerid, btn_Data[btn_Near[playerid][i]][btn_area])) {
				Logger_Err("player incorrectly flagged as inside button area",
					Logger_I("playerid", playerid),
					Logger_I("id", _:btn_Near[playerid][i]));

				Iter_SafeRemove(btn_NearIndex[playerid], i, i);
				continue;
			}

			list[size++] = btn_Near[playerid][i];
		}
	} else {
		foreach(new i : btn_NearIndex[playerid]) {
			list[size++] = btn_Near[playerid][i];
		}
	}

	return 0;
}

stock GetPlayerAngleToButton(playerid, Button:id, &Float:angle) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(!IsPlayerConnected(playerid)) {
		return 2;
	}

	new
		Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	angle = GetAngleToPoint(x, y, btn_Data[id][btn_posX], btn_Data[id][btn_posY]);

	return 0;
}

stock GetButtonAngleToPlayer(playerid, Button:id, &Float:angle) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 1;
	}

	if(!IsPlayerConnected(playerid)) {
		return 2;
	}

	new
		Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(playerid, x, y, z);

	angle = GetAngleToPoint(btn_Data[id][btn_posX], btn_Data[id][btn_posY], x, y);

	return 0;
}


/*==============================================================================

	Internal Functions and Hooks

==============================================================================*/


hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(newkeys & 16) {
		if(!IsPlayerInAnyVehicle(playerid) && Iter_Count(btn_NearIndex[playerid]) > 0) {
			if(!IsPlayerInAnyDynamicArea(playerid)) {
				Logger_Err("player is not in areas but list isn't empty", Logger_I("playerid", playerid));
				Iter_Clear(btn_NearIndex[playerid]);
			}

			new
				Button:id,
				Float:x,
				Float:y,
				Float:z,
				Float:distance,
				list[BTN_MAX_INRANGE][e_button_range_data],
				index;

			GetPlayerPos(playerid, x, y, z);

			foreach(new i : btn_NearIndex[playerid]) {
				if(index >= BTN_MAX_INRANGE - 1) {
					break;
				}

				id = Button:btn_Near[playerid][i];
				distance = GetDistance3D(x, y, z, btn_Data[id][btn_posX], btn_Data[id][btn_posY], btn_Data[id][btn_posZ]);

				if(distance > btn_Data[id][btn_size]) {
					continue;
				}

				if(!(btn_Data[id][btn_posZ] - btn_Data[id][btn_size] <= z <= btn_Data[id][btn_posZ] + btn_Data[id][btn_size])) {
					continue;
				}


				list[index][btn_buttonId] = id;
				list[index][btn_distance] = distance;

				index++;
			}

			_btn_SortButtons(list, 0, index);

			for(new i = index - 1; i >= 0; i--) {
				if(Internal_OnButtonPress(playerid, list[i][btn_buttonId])) {
					break;
				}
			}
		}

		if(oldkeys & 16) {
			if(btn_Pressing[playerid] != INVALID_BUTTON_ID) {
				CallLocalFunction("OnButtonRelease", "dd", playerid, _:btn_Pressing[playerid]);
				btn_Pressing[playerid] = INVALID_BUTTON_ID;
			}
		}
	}

	return Y_HOOKS_CONTINUE_RETURN_1;
}

_btn_SortButtons(array[][e_button_range_data], left, right) {
	new
		tmp_left = left,
		tmp_right = right,
		Float:pivot = array[(left + right) / 2][btn_distance],
		Button:id,
		Float:distance;

	while(tmp_left <= tmp_right) {
		while(array[tmp_left][btn_distance] > pivot) {
			tmp_left++;
		}
		while(array[tmp_right][btn_distance] < pivot) {
			tmp_right--;
		}
		if(tmp_left <= tmp_right) {
			id = array[tmp_left][btn_buttonId];
			array[tmp_left][btn_buttonId] = array[tmp_right][btn_buttonId];
			array[tmp_right][btn_buttonId] = id;

			distance = array[tmp_left][btn_distance];
			array[tmp_left][btn_distance] = array[tmp_right][btn_distance];
			array[tmp_right][btn_distance] = distance;

			tmp_left++;
			tmp_right--;
		}
	}

	if(left < tmp_right) {
		_btn_SortButtons(array, left, tmp_right);
	}

	if(tmp_left < right) {
		_btn_SortButtons(array, tmp_left, right);
	}
}

Internal_OnButtonPress(playerid, Button:id) {
	if(!Iter_Contains(btn_Index, _:id)) {
		return 0;
	}

	btn_Pressing[playerid] = id;

	if(CallLocalFunction("OnButtonPress", "dd", playerid, _:id)) {
		return 1;
	}

	return 0;
}

timer btn_Unfreeze[BTN_TELEPORT_FREEZE_TIME](playerid) {
	TogglePlayerControllable(playerid, true);
}

hook OnPlayerEnterDynArea(playerid, areaid) {
	if(!IsPlayerInAnyVehicle(playerid) && Iter_Count(btn_NearIndex[playerid]) < BTN_MAX_INRANGE) {
		new data[2];

		Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

		if(data[0] == BTN_STREAMER_AREA_IDENTIFIER) {
			if(Iter_Contains(btn_Index, data[1])) {
				new cell = Iter_Free(btn_NearIndex[playerid]);

				btn_Near[playerid][cell] = Button:data[1];
				Iter_Add(btn_NearIndex[playerid], cell);

				ShowActionText(playerid, btn_Data[Button:data[1]][btn_text]);
				CallLocalFunction("OnPlayerEnterButtonArea", "dd", playerid, data[1]);
			}
		}
	}
}

hook OnPlayerLeaveDynArea(playerid, areaid) {
	process_LeaveDynamicArea(playerid, areaid);
}

process_LeaveDynamicArea(playerid, areaid) {
	if(!IsValidDynamicArea(areaid)) {
		return 1;
	}

	if(IsPlayerInAnyVehicle(playerid)) {
		return 1;
	}

	if(Iter_Count(btn_NearIndex[playerid]) == 0) {
		return 2;
	}

	new data[2];

	Streamer_GetArrayData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID, data, 2);

	if(data[0] != BTN_STREAMER_AREA_IDENTIFIER) {
		return 3;
	}

	if(!Iter_Contains(btn_Index, data[1])) {
		return 4;
	}

	HideActionText(playerid);
	CallLocalFunction("OnPlayerLeaveButtonArea", "dd", playerid, data[1]);

	foreach(new i : btn_NearIndex[playerid]) {
		if(btn_Near[playerid][i] == Button:data[1]) {
			Iter_Remove(btn_NearIndex[playerid], i);
			break;
		}
	}

	return 0;
}
