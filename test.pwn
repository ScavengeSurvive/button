#define RUN_TESTS
#include "button.inc"

#include <YSI\y_testing>
#include <YSI\y_hooks>


Test:ButtonCreate() {
	new buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	ASSERT(IsValidButton(buttonid));
	ASSERT(IsValidDynamicArea(GetButtonArea(buttonid)) == 1);
	ASSERT(DestroyButton(buttonid) == 0);
}

Test:ButtonSetArea() {
	new buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	new tmp = CreateDynamicCircle(20.0, 20.0, 4.0);
	ASSERT(SetButtonArea(buttonid, tmp) == 0);
	ASSERT(GetButtonArea(buttonid) == tmp);
	ASSERT(DestroyButton(buttonid) == 0);
}

Test:ButtonSetLabelText() {
	new buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	ASSERT(SetButtonLabel(buttonid, "New text", -1, 42.0) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 2);
	ASSERT(DestroyButton(buttonid) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 1);
}

#endinput



	new Float:x, Float:y, Float:z;
	ASSERT(bool:GetButtonPos(buttonid, x, y, z));
	ASSERT(x == 1.0 && y == 2.0 && z == 3.0);
	ASSERT(bool:SetButtonPos(buttonid, 3.0, 5.0, 1.0));
	ASSERT(bool:GetButtonPos(buttonid, x, y, z));
	ASSERT(x == 3.0 && y == 5.0 && z == 1.0);

	ASSERT(GetButtonSize(buttonid) == 2.5);
	ASSERT(bool:SetButtonSize(buttonid, 4.4));
	ASSERT(GetButtonSize(buttonid) == 4.4);

	ASSERT(GetButtonWorld(buttonid) == 4);
	ASSERT(bool:SetButtonWorld(buttonid, 6));
	ASSERT(GetButtonWorld(buttonid) == 6);

	ASSERT(GetButtonInterior(buttonid) == 8);
	ASSERT(bool:SetButtonInterior(buttonid, 10));
	ASSERT(GetButtonInterior(buttonid) == 10);

	tmp = CreateButton(10.0, 0.0, 0.0, "Linked");
	ASSERT(bool:LinkTP(buttonid, tmp));
	ASSERT(GetButtonLinkedID(buttonid) == tmp);
	ASSERT(GetButtonLinkedID(tmp) == buttonid);
	ASSERT(bool:UnLinkTP(buttonid, tmp));
	ASSERT(GetButtonLinkedID(buttonid) == INVALID_BUTTON_ID);
	ASSERT(GetButtonLinkedID(tmp) == INVALID_BUTTON_ID);

	new string[128];
	ASSERT(bool:GetButtonText(buttonid, string));
	ASSERT(!strcmp(string, "Button"));
	ASSERT(bool:SetButtonText(buttonid, "New Button Text Long String"));
	ASSERT(bool:GetButtonText(buttonid, string));
	ASSERT(!strcmp(string, "New Button Text Long String"));

	ASSERT(bool:SetButtonExtraData(buttonid, 50));
	ASSERT(GetButtonExtraData(buttonid) == 50);
}

TestClose:Button() {
	DestroyButton(buttonid);

	// Button should be invalid now that it's deleted
	ASSERT(!IsValidButton(buttonid));
}
