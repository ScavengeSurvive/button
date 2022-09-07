#define RUN_TESTS
#include "button.inc"

#include <YSI_Core\y_testing>
#include <YSI_Coding\y_hooks>


Test:ButtonCreate() {
	new Button:buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	ASSERT(IsValidButton(buttonid));
	ASSERT(IsValidDynamicArea(GetButtonArea(buttonid)) == 1);
	ASSERT(DestroyButton(buttonid) == 0);
}

Test:ButtonSetArea() {
	new Button:buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	new tmp = CreateDynamicCircle(20.0, 20.0, 4.0);
	ASSERT(SetButtonArea(buttonid, tmp) == 0);
	ASSERT(GetButtonArea(buttonid) == tmp);
	ASSERT(DestroyButton(buttonid) == 0);
}

Test:ButtonSetLabelText() {
	new Button:buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	ASSERT(SetButtonLabel(buttonid, "New text", -1, 42.0) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 2);
	ASSERT(DestroyButton(buttonid) == 0);
	ASSERT(DestroyButtonLabel(buttonid) == 1);
}

Test:ButtonText() {
	new Button:buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);

	new string[128];
	ASSERT(GetButtonText(buttonid, string) == 0);
	ASSERT(!strcmp(string, "Button"));
	ASSERT(SetButtonText(buttonid, "New Button Text Long String") == 0);
	ASSERT(GetButtonText(buttonid, string) == 0);
	ASSERT(!strcmp(string, "New Button Text Long String"));

	ASSERT(DestroyButton(buttonid) == 0);
	ASSERT(GetButtonText(buttonid, string) == 1);
}

Test:ButtonData() {
	new Button:buttonid = CreateButton(1.0, 2.0, 3.0, "Button", 4, 8, 2.5, 1, "Label", 0x1C1C1CFF, 12.5);
	new data;
	ASSERT(SetButtonExtraData(buttonid, 50) == 0);
	ASSERT(GetButtonExtraData(buttonid, data) == 0);
	ASSERT(data == 50);
}
