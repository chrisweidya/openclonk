/*
 * OpenClonk, http://www.openclonk.org
 *
 * Copyright (c) 2013 David Dormagen
 *
 * Portions might be copyrighted by other authors who have contributed
 * to OpenClonk.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * See isc_license.txt for full license and disclaimer.
 *
 * "Clonk" is a registered trademark of Matthes Bender.
 * See clonk_trademark_license.txt for full license.
 */

 /* a flexisble ingame menu system that can be composed out of multiple windows */

#include <C4Include.h>
#include <C4GuiWindow.h>

#include <C4Application.h>
#include <C4DefList.h>
#include <C4GraphicsSystem.h>
#include <C4GraphicsResource.h>
#include <C4Game.h>
#include <C4Control.h>
#include <C4MouseControl.h>
#include <C4Object.h>
#include <C4Player.h>
#include <C4PlayerList.h>



const float standardVerticalBorder = 100.0f;
const float standardHorizontalBorder = 100.0f;

C4GuiWindow GuiWindowRoot = C4GuiWindow(standardVerticalBorder, standardHorizontalBorder);

C4GuiWindowAction::~C4GuiWindowAction()
{
	if (text)
		text->DecRef();
	if (nextAction)
		delete nextAction;
}

const C4Value C4GuiWindowAction::ToC4Value(bool first)
{
	C4ValueArray *array = new C4ValueArray();
	// TODO: save action ID with array
	switch (action)
	{
	case C4GuiWindowActionID::Call:
		array->SetSize(4);
		array->SetItem(0, C4Value(action));
		array->SetItem(1, C4Value(target));
		array->SetItem(2, C4Value(text));
		array->SetItem(3, value);
		break;

	case C4GuiWindowActionID::SetTag:
		array->SetSize(4);
		array->SetItem(0, C4Value(action));
		array->SetItem(1, C4Value(target));
		array->SetItem(2, C4Value(subwindowID));
		array->SetItem(3, C4Value(text));
		break;

	case 0: // can actually happen if the action is invalidated
		break;

	default:
		assert(false && "trying to save C4GuiWindowAction without valid action");
		break;
	}

	if (!first || !nextAction) return C4Value(array);

	// this action is the first in a chain of actions
	// all following actions (and this one) have to be put into another array
	C4ValueArray *container = new C4ValueArray();
	int32_t size = 1;
	container->SetSize(size);
	container->SetItem(0, C4Value(array));

	C4GuiWindowAction *next = nextAction;
	while (next)
	{
		C4Value val = next->ToC4Value(false);
		++size;
		container->SetSize(size);
		container->SetItem(size - 1, val);
		next = next->nextAction;
	}
	return C4Value(container);
}

void C4GuiWindowAction::ClearPointers(C4Object *pObj)
{
	C4Object *targetObj = target ? target->GetObject() : 0;

	if (targetObj == pObj)
	{
		// not only forget object, but completely invalidate action
		action = 0;
		target = 0;
	}
	if (nextAction)
		nextAction->ClearPointers(pObj);
}
bool C4GuiWindowAction::Init(C4ValueArray *array, int32_t index)
{
	if (array->GetSize() == 0) // safety
		return false;

	// an array of actions?
	if (array->GetItem(0).getArray())
	{
		//LogF("..initing multi-action event (index %d)", index);
		// add action to action chain?
		if (index+1 < array->GetSize())
		{
			nextAction = new C4GuiWindowAction();
			nextAction->Init(array, index + 1);
		}
		// continue with one sub array
		array = array->GetItem(index).getArray();
		if (!array) return false;
	}
	// retrieve type of action
	int newAction = array->GetItem(0).getInt();
	action = 0; // still invalid!

	switch (newAction)
	{
	case C4GuiWindowActionID::Call:
		if (array->GetSize() < 3) return false;
		target = array->GetItem(1).getPropList();
		text = array->GetItem(2).getStr();
		if (!target || !text) return false;
		if (array->GetSize() >= 4)
			value = C4Value(array->GetItem(3));
		text->IncRef();

		// important! needed to identify actions later!
		id = ::GuiWindowRoot.GenerateActionID();

		break;

	case C4GuiWindowActionID::SetTag:
		if (array->GetSize() < 4) return false;
		target = array->GetItem(1).getObj(); // getObj on purpose. Need to validate that.
		subwindowID = array->GetItem(2).getInt();
		text = array->GetItem(3).getStr();
		if (!text) return false;
		text->IncRef();
		break;

	default:
		return false;
	}

	action = newAction;
	return true;
}

void C4GuiWindowAction::Execute(C4GuiWindow *parent, int32_t player, int32_t actionType)
{
	assert(parent && "C4GuiWindow::Execute must always be called with parent");
	//LogF("Excuting action (nextAction: %x, subwID: %d, target: %x, text: %s, type: %d)", nextAction, subwindowID, target, text->GetCStr(), actionType);

	// invalid ID? can be set by removal of target object
	if (action)
	{
		// get menu main window
		C4GuiWindow *main = parent;
		C4GuiWindow *from = main;
		while (from->parent)
		{
			main = from;
			from = from->parent;
		}

		switch (action)
		{
		case C4GuiWindowActionID::Call:
		{
			if (!target) // ohject removed in the meantime?
				break;
			// the action needs to be synchronized! Assemble command and put it into control queue!
			Game.Input.Add(CID_MenuCommand, new C4ControlMenuCommand(id, player, main->GetID(), parent->GetID(), parent->target, actionType));
			break;
		}

		case C4GuiWindowActionID::SetTag:
		{
			C4GuiWindow *window = main;
			if (subwindowID == 0)
				window = parent;
			else if (subwindowID > 0)
			{
				C4Object *targetObj = dynamic_cast<C4Object*> (target);
				window = main->GetSubWindow(subwindowID, targetObj);
			}
			if (window)
				window->SetTag(text);
			break;
		}

		default:
			assert(false && "C4GuiWindowAction without valid or invalidated ID");
			break;
		}
	} // action

	if (nextAction)
	{
		nextAction->Execute(parent, player, actionType);
	}
}

bool C4GuiWindowAction::ExecuteCommand(int32_t actionID, C4GuiWindow *parent, int32_t player)
{
	// target has already been checked for validity
	if (id == actionID && action)
	{
		assert(action == C4GuiWindowActionID::Call && "C4ControlMenuCommand for invalid action!");

		// get menu main window
		C4GuiWindow *main = parent;
		C4GuiWindow *from = main;
		while (from->parent)
		{
			main = from;
			from = from->parent;
		}
		//LogF("command synced.. target: %x, targetObj: %x, func: %s", target, target->GetObject(), text->GetCStr());
		C4AulParSet Pars(C4VInt(player), C4VInt(main->GetID()), C4VInt(parent->GetID()), C4VObj(parent->target), value);
		target->Call(text->GetCStr(), &Pars);
		return true;
	}
	if (nextAction)
		return nextAction->ExecuteCommand(actionID, parent, player);
	return false;
}

C4GuiWindowScrollBar::C4GuiWindowScrollBar() : offset(0.5f), decoration(0), parent(0)
{

}

C4GuiWindowScrollBar::~C4GuiWindowScrollBar()
{

}

void C4GuiWindowScrollBar::Draw(C4TargetFacet &cgo, int32_t player, float parentLeft, float parentTop, float parentRight, float parentBottom)
{
	C4GUI::ScrollBarFacets &facets = decoration ? *decoration : ::GraphicsResource.sfctScroll;
	C4GUI::DynBarFacet bar = facets.barScroll;

	float offX = 25.0f;
	float offY = 0.0f;
	float x = cgo.X + parentRight - offX;
	float yOrigin = cgo.Y + parentTop + offY;
	float hgt = (parentBottom - parentTop) - offY;

	bar.fctBegin.Draw(cgo.Surface, x, yOrigin);
	float yOffset = bar.fctBegin.Hgt;

	float segmentHeight = bar.fctMiddle.Hgt;
	int32_t steps = (hgt-5 - yOffset) / segmentHeight;

	for (int32_t i = 0; i < steps; ++i)
	{
		float currentHeight = segmentHeight;
		float toBottom = hgt-5 - yOffset;
		if (currentHeight > toBottom) currentHeight = toBottom;

		bar.fctMiddle.Hgt = currentHeight;
		bar.fctMiddle.Draw(cgo.Surface, x, yOrigin + yOffset);
		yOffset += segmentHeight;
	}
	bar.fctMiddle.Hgt = segmentHeight;
	bar.fctEnd.Draw(cgo.Surface, x, yOrigin + yOffset /*- bar.fctEnd.Hgt*/);
}

bool C4GuiWindowScrollBar::MouseInput(int32_t button, int32_t mouseX, int32_t mouseY, DWORD dwKeyParam)
{
	if (::MouseControl.IsLeftDown())
	{
		// calculate new position
		float wdt = parent->lastDrawPosition.bottom - parent->lastDrawPosition.top;
		if (wdt != 0.0f)
			offset = (mouseY - parent->lastDrawPosition.top) / wdt;
		return true;
	}
	return false;
}

C4GuiWindowProperty::~C4GuiWindowProperty()
{
	// is cleaned up from destructor of C4GuiWindow
}

void C4GuiWindowProperty::SetInt(int32_t to)
{
	C4String* tag = &Strings.P[P_Std];
	taggedProperties[tag] = Prop();
	current = &taggedProperties[tag];
	current->d = to;
}
void C4GuiWindowProperty::SetFloat(float to)
{
	C4String* tag = &Strings.P[P_Std];
	taggedProperties[tag] = Prop();
	current = &taggedProperties[tag];
	current->f = to;
}
void C4GuiWindowProperty::SetNull()
{
	C4String* tag = &Strings.P[P_Std];
	taggedProperties[tag] = Prop();
	current = &taggedProperties[tag];
	current->data = 0;
}

void C4GuiWindowProperty::CleanUp(Prop &prop)
{
	switch (type)
	{
	case frameDecoration:
		if (prop.deco) delete prop.deco;
		break;
	case onClickAction:
	case onMouseInAction:
	case onMouseOutAction:
	case onCloseAction:
		if (prop.action) delete prop.action;
		break;
	case text:
		if (prop.strBuf) delete prop.strBuf;
		break;
	default:
		break;
	}
}

void C4GuiWindowProperty::CleanUpAll()
{
	for (std::map<C4String*, Prop>::iterator iter = taggedProperties.begin(); iter != taggedProperties.end(); ++iter)
	{
		CleanUp(iter->second);
		if (iter->first != &Strings.P[P_Std])
			iter->first->DecRef();
	}
}

const C4Value C4GuiWindowProperty::ToC4Value()
{
	C4PropList *proplist = C4PropList::New();

	for(std::map<C4String*, Prop>::iterator iter = taggedProperties.begin(); iter != taggedProperties.end(); ++iter)
	{
		C4String *tagString = iter->first;
		const Prop &prop = iter->second;

		C4Value val;

		// get value to save
		switch (type)
		{
		case C4GuiWindowPropertyName::left:
		case C4GuiWindowPropertyName::right:
		case C4GuiWindowPropertyName::top:
		case C4GuiWindowPropertyName::bottom:
		case C4GuiWindowPropertyName::backgroundColor:
		case C4GuiWindowPropertyName::style:
		case C4GuiWindowPropertyName::priority:
			val = C4Value(prop.d);
			break;

		case C4GuiWindowPropertyName::relLeft:
		case C4GuiWindowPropertyName::relRight:
		case C4GuiWindowPropertyName::relTop:
		case C4GuiWindowPropertyName::relBottom:
			val = C4Value(int32_t (prop.f * 1000.0f));
			break;

		case C4GuiWindowPropertyName::symbolObject:
			val = C4Value(prop.obj);
			break;

		case C4GuiWindowPropertyName::symbolDef:
			val = C4Value(prop.def);
			break;

		case C4GuiWindowPropertyName::frameDecoration:
			val = C4Value(prop.deco ? prop.deco->idSourceDef : C4ID::None);
			break;

		case C4GuiWindowPropertyName::text:
		{
			if (prop.strBuf)
			{
				// string existing?
				C4String *s = Strings.FindString(prop.strBuf->getData());
				if (!s) s = Strings.RegString(prop.strBuf->getData());
				val = C4Value(s);
			}
			break;
		}

		case C4GuiWindowPropertyName::onClickAction:
		case C4GuiWindowPropertyName::onMouseInAction:
		case C4GuiWindowPropertyName::onMouseOutAction:
		case C4GuiWindowPropertyName::onCloseAction:
			if (prop.action)
				val = prop.action->ToC4Value();
			break;

		default:
			assert(false && "C4GuiWindowAction should never have undefined type");
			break;
		} // switch

		proplist->SetPropertyByS(tagString, val);
	}

	return C4Value(proplist);
}

void C4GuiWindowProperty::Set(const C4Value &value, C4String *tag)
{
	C4PropList *proplist = value.getPropList();
	bool isTaggedPropList = false;
	if (proplist)
		isTaggedPropList = !(proplist->GetDef() || proplist->GetObject());

	if (isTaggedPropList)
	{
		C4ValueArray *properties = proplist->GetProperties();

		for (int32_t i = 0; i < properties->GetSize(); ++i)
		{
			const C4Value &entry = properties->GetItem(i);
			C4String *key = entry.getStr();
			assert(key && "Proplist returns non-string as key");

			C4Value property;
			proplist->GetPropertyByS(key, &property);
			Set(property, key);
		}
		return;
	}

	// special treatment for some that have to be deleted (due to owning string/frame deco/...)
	if (taggedProperties.count(tag))
		CleanUp(taggedProperties[tag]);
	else // new tag, retain the proplist if not standard
		if (tag != &Strings.P[P_Std])
			tag->IncRef();

	taggedProperties[tag] = Prop();
	// in order to make /current/ sane, always reset it - not relying about implementation of std::map
	// if the user wants a special tag selected, he should do that (standard selection will still be "Std")
	current = &taggedProperties[tag];
	currentTag = tag;

	switch (type)
	{
	case C4GuiWindowPropertyName::left:
	case C4GuiWindowPropertyName::right:
	case C4GuiWindowPropertyName::top:
	case C4GuiWindowPropertyName::bottom:
	case C4GuiWindowPropertyName::backgroundColor:
	case C4GuiWindowPropertyName::style:
	case C4GuiWindowPropertyName::priority:
		current->d = value.getInt();
		break;

	case C4GuiWindowPropertyName::relLeft:
	case C4GuiWindowPropertyName::relRight:
	case C4GuiWindowPropertyName::relTop:
	case C4GuiWindowPropertyName::relBottom:
		current->f = float(value.getInt()) / 1000.0f;
		break;
	case C4GuiWindowPropertyName::symbolObject:
	{
		C4PropList *symbol = value.getPropList();
		if (symbol)
			current->obj = symbol->GetObject();
		else current->obj = 0;
		break;
	}
	case C4GuiWindowPropertyName::symbolDef:
	{
		C4PropList *symbol = value.getPropList();
		if (symbol)
			current->def = symbol->GetDef();
		else current->def = 0;
		break;
	}
	case C4GuiWindowPropertyName::frameDecoration:
	{
		C4ID id = value.getC4ID();
		if (id != C4ID::None)
			if (C4Id2Def(id))
			{
				current->deco = new C4GUI::FrameDecoration();
				if (!current->deco->SetByDef(id))
				{
					delete current->deco;
					current->deco = 0;
				}
			}
		break;
	}
	case C4GuiWindowPropertyName::text:
	{
		C4String *string = value.getStr();
		StdCopyStrBuf *buf = new StdCopyStrBuf();
		if (string)
			buf->Copy(string->GetCStr());
		else buf->Copy("");
		current->strBuf = buf;
		break;
	}
	case C4GuiWindowPropertyName::onClickAction:
	case C4GuiWindowPropertyName::onMouseInAction:
	case C4GuiWindowPropertyName::onMouseOutAction:
	case C4GuiWindowPropertyName::onCloseAction:
	{
		C4ValueArray *array = value.getArray();
		if (array)
		{
			assert (!current->action && "Prop() contains action prior to assignment");
			current->action = new C4GuiWindowAction();
			current->action->Init(array);
		}
		break;
	}

	default:
		assert(false && "C4GuiWindowAction should never have undefined type");
		break;
	} // switch
}

void C4GuiWindowProperty::ClearPointers(C4Object *pObj)
{
	// assume that we actually contain an object
	for (std::map<C4String*, Prop>::iterator iter = taggedProperties.begin(); iter != taggedProperties.end(); ++iter)
	{
		switch (type)
		{
		case C4GuiWindowPropertyName::symbolObject:
			if (iter->second.obj == pObj)
				iter->second.obj = 0;
		break;

		case C4GuiWindowPropertyName::onClickAction:
		case C4GuiWindowPropertyName::onMouseInAction:
		case C4GuiWindowPropertyName::onMouseOutAction:
		case C4GuiWindowPropertyName::onCloseAction:
			if (iter->second.action)
				iter->second.action->ClearPointers(pObj);
		break;
		default:
			return;
		}
	}
}

bool C4GuiWindowProperty::SwitchTag(C4String *tag)
{
	if (!taggedProperties.count(tag)) return false; // tag not available
	if (current == &taggedProperties[tag]) return false; // tag already set?
	current = &taggedProperties[tag];
	currentTag = tag;
	return true;
}

std::list<C4GuiWindowAction*> C4GuiWindowProperty::GetAllActions()
{
	std::list<C4GuiWindowAction*> allActions;
	for (std::map<C4String*, Prop>::iterator iter = taggedProperties.begin(); iter != taggedProperties.end(); ++iter)
	{
		Prop &p = iter->second;
		if (p.action)
			allActions.push_back(p.action);
	}
	return allActions;
}


C4GuiWindow::C4GuiWindow()
{
	Init();
}

C4GuiWindow::C4GuiWindow(float stdBorderX, float stdBorderY)
{
	Init();

	// set border values for std tag
	// relative offsets are standard, only need to set exact offset
	props[C4GuiWindowPropertyName::left].SetInt(int32_t(stdBorderX));
	props[C4GuiWindowPropertyName::right].SetInt(int32_t(-stdBorderX));
	props[C4GuiWindowPropertyName::top].SetInt(int32_t(stdBorderY));
	props[C4GuiWindowPropertyName::bottom].SetInt(int32_t(-stdBorderY));
}

void C4GuiWindow::Init()
{
	id = 0;
	isMainWindow = false;

	// properties must know what they stand for
	for (int32_t i = 0; i < C4GuiWindowPropertyName::_lastProp; ++i)
		props[i].type = i;

	// standard values for all of the properties

	// exact offsets are standard 0
	props[C4GuiWindowPropertyName::left].SetNull();
	props[C4GuiWindowPropertyName::right].SetNull();
	props[C4GuiWindowPropertyName::top].SetNull();
	props[C4GuiWindowPropertyName::bottom].SetNull();
	// relative offsets are standard full screen 0,0 - 1,1
	props[C4GuiWindowPropertyName::relLeft].SetNull();
	props[C4GuiWindowPropertyName::relTop].SetNull();
	props[C4GuiWindowPropertyName::relBottom].SetFloat(1.0f);
	props[C4GuiWindowPropertyName::relRight].SetFloat(1.0f);
	// other properties are 0
	props[C4GuiWindowPropertyName::backgroundColor].SetNull();
	props[C4GuiWindowPropertyName::frameDecoration].SetNull();
	props[C4GuiWindowPropertyName::symbolObject].SetNull();
	props[C4GuiWindowPropertyName::symbolDef].SetNull();
	props[C4GuiWindowPropertyName::text].SetNull();
	props[C4GuiWindowPropertyName::onClickAction].SetNull();
	props[C4GuiWindowPropertyName::onMouseInAction].SetNull();
	props[C4GuiWindowPropertyName::onMouseOutAction].SetNull();
	props[C4GuiWindowPropertyName::onCloseAction].SetNull();
	props[C4GuiWindowPropertyName::style].SetNull();
	props[C4GuiWindowPropertyName::priority].SetNull();

	parent = 0;
	wasRemoved = false;
	closeActionWasExecuted = false;
	visible = true;
	hasMouseFocus = false;
	target = 0;
	scrollBar = 0;
}

C4GuiWindow::~C4GuiWindow()
{
	ClearChildren(false);

	// delete certain properties that contain allocated elements or referenced strings
	for (int32_t i = 0; i < C4GuiWindowPropertyName::_lastProp; ++i)
		props[i].CleanUpAll();

	if (scrollBar)
		delete scrollBar;
}

// helper function
void C4GuiWindow::SetArrayTupleProperty(const C4Value &property, C4GuiWindowPropertyName first, C4GuiWindowPropertyName second, C4String *tag)
{
	C4ValueArray *array;
	if ((array = property.getArray()))
	{
		if (array->GetSize() > 0)
			props[first].Set(array->GetItem(0), tag);
		if (array->GetSize() > 1)
			props[second].Set(array->GetItem(1), tag);
	}
	else props[first].Set(property, tag);
}

const C4Value C4GuiWindow::ToC4Value()
{
	C4PropList *proplist = C4PropList::New();

	// TODO: save IDs

	// save all properties
	int32_t toSave[] =
	{
		P_X,
		P_Y,
		P_Wdt,
		P_Hgt,
		P_BackgroundColor,
		P_Decoration,
		P_Symbol,
		P_Target,
		P_Text,
		P_ID,
		P_OnClick,
		P_OnMouseIn,
		P_OnMouseOut,
		P_OnClose,
		P_Style,
		P_Mode,
		P_Priority
	};

	for (size_t i = 0; i < sizeof(toSave); ++i)
	{
		int32_t prop = toSave[i];
		C4Value val;

		switch (prop)
		{
		case P_X:
		case P_Y:
		case P_Wdt:
		case P_Hgt:
		{
			C4Value first, second;
#define ARRAY_TUPLE(p, prop1, prop2) if (prop == p) { first = props[prop1].ToC4Value(); second = props[prop2].ToC4Value(); }
			ARRAY_TUPLE(P_X, C4GuiWindowPropertyName::relLeft, C4GuiWindowPropertyName::left);
			ARRAY_TUPLE(P_Y, C4GuiWindowPropertyName::relTop, C4GuiWindowPropertyName::top);
			ARRAY_TUPLE(P_Wdt, C4GuiWindowPropertyName::relRight, C4GuiWindowPropertyName::right);
			ARRAY_TUPLE(P_Hgt, C4GuiWindowPropertyName::relBottom, C4GuiWindowPropertyName::bottom);
#undef ARRAY_TUPLE
			C4ValueArray *array = new C4ValueArray();
			array->SetSize(2);
			array->SetItem(0, first);
			array->SetItem(1, second);
			val = C4Value(array);
			break;
		}
		case P_BackgroundColor: val = props[C4GuiWindowPropertyName::backgroundColor].ToC4Value(); break;
		case P_Decoration: val = props[C4GuiWindowPropertyName::frameDecoration].ToC4Value(); break;
		case P_Symbol:
			// either object or def
			val = props[C4GuiWindowPropertyName::symbolObject].ToC4Value();
			if (val == C4Value()) // is nil?
				val = props[C4GuiWindowPropertyName::symbolDef].ToC4Value();
			break;
		case P_Target: val = C4Value(target); break;
		case P_Text: val = props[C4GuiWindowPropertyName::text].ToC4Value(); break;
		case P_ID: val = C4Value(id); break;
		case P_OnClick: val = props[C4GuiWindowPropertyName::onClickAction].ToC4Value(); break;
		case P_OnMouseIn: val = props[C4GuiWindowPropertyName::onMouseInAction].ToC4Value(); break;
		case P_OnMouseOut: val = props[C4GuiWindowPropertyName::onMouseOutAction].ToC4Value(); break;
		case P_OnClose: val = props[C4GuiWindowPropertyName::onCloseAction].ToC4Value(); break;
		case P_Style: val = props[C4GuiWindowPropertyName::style].ToC4Value(); break;
		case P_Mode: val = C4Value(int32_t(hasMouseFocus)); break;

		default:
			assert(false);
			break;
		}

		proplist->SetProperty(C4PropertyName(prop), val);
	}

	// save children now, construct new names for them
	int32_t childIndex = 0;
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		C4Value val = child->ToC4Value();
		StdStrBuf childName;
		childName.Format("child_%03d", ++childIndex);
		C4String *s = Strings.RegString(childName);
		proplist->SetPropertyByS(s, val);
	}

	return C4Value(proplist);
}

bool C4GuiWindow::CreateFromPropList(C4PropList *proplist, bool resetStdTag, bool isUpdate)
{
	assert(parent && "GuiWindow created from proplist without parent (fails for ID tag)");

	bool layoutUpdateRequired = false; // needed for position changes etc
	// get properties from proplist
	// make sure to delete the array later, we took ownership
	C4ValueArray *properties = proplist->GetProperties();
	C4String *stdTag = &Strings.P[P_Std];
	for (int32_t i = 0; i < properties->GetSize(); ++i)
	{
		const C4Value &entry = properties->GetItem(i);
		C4String *key = entry.getStr();
		assert(key && "PropList returns non-string as key");

		C4Value property;
		proplist->GetPropertyByS(key, &property);

		C4Value value;

		if(&Strings.P[P_X] == key)
		{
			SetArrayTupleProperty(property, C4GuiWindowPropertyName::relLeft, C4GuiWindowPropertyName::left, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_Y] == key)
		{
			SetArrayTupleProperty(property, C4GuiWindowPropertyName::relTop, C4GuiWindowPropertyName::top, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_Wdt] == key)
		{
			SetArrayTupleProperty(property, C4GuiWindowPropertyName::relRight, C4GuiWindowPropertyName::right, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_Hgt] == key)
		{
			SetArrayTupleProperty(property, C4GuiWindowPropertyName::relBottom, C4GuiWindowPropertyName::bottom, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_BackgroundColor] == key)
			props[C4GuiWindowPropertyName::backgroundColor].Set(property, stdTag);
		else if(&Strings.P[P_Target] == key)
			target = property.getObj();
		else if(&Strings.P[P_Symbol] == key)
		{
			props[C4GuiWindowPropertyName::symbolDef].Set(property, stdTag);
			props[C4GuiWindowPropertyName::symbolObject].Set(property, stdTag);
		}
		else if(&Strings.P[P_Decoration] == key)
		{
			props[C4GuiWindowPropertyName::frameDecoration].Set(property, stdTag);
		}
		else if(&Strings.P[P_Text] == key)
		{
			props[C4GuiWindowPropertyName::text].Set(property, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_Prototype] == key)
			; // do nothing
		else if(&Strings.P[P_Mode] == key) // note that "Mode" is abused here for saving whether we have mouse focus
			hasMouseFocus = property.getBool();
		else if(&Strings.P[P_ID] == key)
		{
			// setting IDs is only valid for subwindows!
			if (!isMainWindow)
			{
				if (id) // already have an ID? remove from parent
					parent->ChildWithIDRemoved(this);
				id = property.getInt();
				if (id != 0)
					parent->ChildGotID(this);
			}
		}
		else if(&Strings.P[P_OnClick] == key)
			props[C4GuiWindowPropertyName::onClickAction].Set(property, stdTag);
		else if(&Strings.P[P_OnMouseIn] == key)
			props[C4GuiWindowPropertyName::onMouseInAction].Set(property, stdTag);
		else if(&Strings.P[P_OnMouseOut] == key)
			props[C4GuiWindowPropertyName::onMouseOutAction].Set(property, stdTag);
		else if(&Strings.P[P_OnClose] == key)
			props[C4GuiWindowPropertyName::onCloseAction].Set(property, stdTag);
		else if(&Strings.P[P_Style] == key)
		{
			props[C4GuiWindowPropertyName::style].Set(property, stdTag);
			layoutUpdateRequired = true;
		}
		else if(&Strings.P[P_Priority] == key)
		{
			props[C4GuiWindowPropertyName::priority].Set(property, stdTag);
			layoutUpdateRequired = true;
			// resort into parent's list
			parent->ChildChangedPriority(this);
		}
		else
		{
			// possibly sub-window?
			C4PropList *subwindow = property.getPropList();
			if (subwindow)
			{
				C4GuiWindow *child = new C4GuiWindow();
				AddChild(child);

				if (!child->CreateFromPropList(subwindow, isUpdate == true, false))
					RemoveChild(child, false);
				else
					layoutUpdateRequired = true;
			}
		}
	}

	if (layoutUpdateRequired)
		parent->lastDrawPosition.dirty = 2;

	if (resetStdTag)
		SetTag(stdTag);

	return true;
}

void C4GuiWindow::ClearPointers(C4Object *pObj)
{
	// not removing or clearing anything twice
	// if this flag is set, the object will not be used after this frame (callbacks?) anyway
	if (wasRemoved) return;

	if (target == pObj)
	{
		Close();
		return;
	}
	props[C4GuiWindowPropertyName::symbolObject].ClearPointers(pObj);
	props[C4GuiWindowPropertyName::onClickAction].ClearPointers(pObj);
	props[C4GuiWindowPropertyName::onMouseInAction].ClearPointers(pObj);
	props[C4GuiWindowPropertyName::onMouseOutAction].ClearPointers(pObj);
	props[C4GuiWindowPropertyName::onCloseAction].ClearPointers(pObj);

	// can't iterate directly over the children, since they might get deleted in the process
	std::vector<C4GuiWindow*> temp;
	temp.reserve(children.size());
	temp.assign(children.begin(), children.end());
	for (std::vector<C4GuiWindow*>::iterator iter = temp.begin(); iter != temp.end(); ++iter)
		(*iter)->ClearPointers(pObj);
}

C4GuiWindow *C4GuiWindow::AddChild(C4GuiWindow *child)
{
	child->parent = this;
	// are we the root menu? Is this a "main" submenu?
	if (!parent)
	{
		child->SetID(GenerateMenuID());
		child->isMainWindow = true;
		//LogF("adding main window: %d [I am %d, root: %d]", child->GetID(), id, int(this == &::GuiWindowRoot));
	}
	// child's priority is ususally 0 here, so just insert it in front of other windows with a priority below 0
	// when the child's priority updates, the update function will be called and the child will be sorted to the correct position
	bool inserted = false;
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *otherChild = *iter;
		if (otherChild->props[C4GuiWindowPropertyName::priority].GetInt() < 0) continue;
		children.insert(iter, child);
		inserted = true;
		break;
	}
	if (!inserted)
		children.push_back(child);

	return child;
}

void C4GuiWindow::ChildChangedPriority(C4GuiWindow *child)
{
	int prio = child->props[C4GuiWindowPropertyName::priority].GetInt();
	// remove child from list first
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		if (*iter != child) continue;
		children.erase(iter);
		break;
	}
	// now insert into list at correct position
	bool inserted = false;
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *otherChild = *iter;
		if (otherChild->props[C4GuiWindowPropertyName::priority].GetInt() < prio) continue;
		children.insert(iter, child);
		inserted = true;
		break;
	}
	if (!inserted)
		children.push_back(child);
}

void C4GuiWindow::ChildWithIDRemoved(C4GuiWindow *child)
{
	if (!parent) return;
	if (!isMainWindow)
		return parent->ChildWithIDRemoved(child);
	std::pair<std::multimap<int32_t, C4GuiWindow*>::iterator, std::multimap<int32_t, C4GuiWindow*>::iterator> range;
	range = childrenIDMap.equal_range(child->GetID());

	for (std::multimap<int32_t, C4GuiWindow*>::iterator iter = range.first; iter != range.second; ++iter)
	{
		if (iter->second != child) continue;
		childrenIDMap.erase(iter);
		//LogF("child-map-size: %d, remov %d [I am %d]", childrenIDMap.size(), child->GetID(), id);
		return;
	}
}

void C4GuiWindow::ChildGotID(C4GuiWindow *child)
{
	assert(parent && "ChildGotID called on window root, should not propagate over main windows!");
	if (!isMainWindow)
		return parent->ChildGotID(child);
	childrenIDMap.insert(std::make_pair(child->GetID(), child));
	//LogF("child+map+size: %d, added %d [I am %d]", childrenIDMap.size(), child->GetID(), id);
}

C4GuiWindow *C4GuiWindow::GetChildByID(int32_t child)
{
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		if ((*iter)->id != child) continue;
		return *iter;
	}
	return 0;
}

C4GuiWindow *C4GuiWindow::GetSubWindow(int32_t childID, C4Object *childTarget)
{
	std::pair<std::multimap<int32_t, C4GuiWindow*>::iterator, std::multimap<int32_t, C4GuiWindow*>::iterator> range;
	range = childrenIDMap.equal_range(childID);

	for (std::multimap<int32_t, C4GuiWindow*>::iterator iter = range.first; iter != range.second; ++iter)
	{
		C4GuiWindow *subwindow = iter->second;
		if (subwindow->GetTarget() != childTarget) continue;
		return subwindow;
	}
	return 0;
}

void C4GuiWindow::RemoveChild(C4GuiWindow *child, bool close, bool all)
{
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		if (child && (*iter != child)) continue;

		// prevent the child from calling the parent (this window) again
		(*iter)->wasRemoved = true;

		// close properly (calls etc.?)
		if (close)
			(*iter)->Close();

		// if the child had an quick-access entry, remove it
		if ((*iter)->GetID() != 0)
			ChildWithIDRemoved(*iter);

		delete *iter;
		if (!all)
		{
			children.erase(iter);
			return;
		}
	}
	if (all)
		children.clear();
}

void C4GuiWindow::ClearChildren(bool close)
{
	RemoveChild(0, close, true);
}

void C4GuiWindow::Close()
{
	// first, close all children and dispose of them properly
	ClearChildren(true);

	if (!closeActionWasExecuted)
	{
		closeActionWasExecuted = true;

		// make call to target object if applicable
		C4GuiWindowAction *action = props[C4GuiWindowPropertyName::onCloseAction].GetAction();
		// only calls are valid actions for OnClose
		if (action && action->action == C4GuiWindowActionID::Call)
		{
			// close is always syncronized (script call/object removal) and thus the action can be executed immediately
			// (otherwise the GUI&action would have been removed anyway..)
			action->ExecuteCommand(action->id, this, NO_OWNER);
		}
	}

	if (!wasRemoved)
	{
		assert(parent && "Close()ing GUIWindow without parent");
		parent->RemoveChild(this);
	}
}

void C4GuiWindow::EnableScrollBar(bool enable, float childrenHeight)
{
	const int32_t &style = props[C4GuiWindowPropertyName::style].GetInt();
	if (style & C4GuiWindowStyleFlag::FitChildren)
	{
		float height = lastDrawPosition.bottom - lastDrawPosition.top;
		props[C4GuiWindowPropertyName::bottom].current->d += (childrenHeight - height);
		return;
	}

	if (!enable && scrollBar)
	{
		delete scrollBar; scrollBar = 0;
	}
	else if (enable && !scrollBar)
	{
		scrollBar = new C4GuiWindowScrollBar();
		scrollBar->parent = this;
	}
}

void C4GuiWindow::UpdateLayout()
{
	//LogF("Updating Layout %p, root: %d, main: %d, style: %d", this, int(this == &::GuiWindowRoot), int(isMainWindow), props[C4GuiWindowPropertyName::style].GetInt());
	const int32_t &style = props[C4GuiWindowPropertyName::style].GetInt();

	// update scroll bar according to children
	bool first = true;
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		// offset is against rounding weirdnesses
		if (first || (child->lastDrawPosition.top < lastDrawPosition.topMostChild))
			lastDrawPosition.topMostChild = child->lastDrawPosition.top + 1.0f;
		if (first || (child->lastDrawPosition.bottom > lastDrawPosition.bottomMostChild))
			lastDrawPosition.bottomMostChild = child->lastDrawPosition.bottom - 1.0f;
		first = false;
	}
	if (first) // no children?
	{
		lastDrawPosition.topMostChild = 0.0f;
		lastDrawPosition.bottomMostChild = 0.0f;
	}

	// check whether we need a scroll-bar and then add it
	float height = lastDrawPosition.bottom - lastDrawPosition.top;
	float childHgt = lastDrawPosition.bottomMostChild - lastDrawPosition.topMostChild;

	EnableScrollBar(childHgt > height, childHgt);

	// special layout selected?
	if (style & C4GuiWindowStyleFlag::GridLayout)
		UpdateLayoutGrid();
	else if (style & C4GuiWindowStyleFlag::VerticalLayout)
		UpdateLayoutVertical();
}

void C4GuiWindow::UpdateLayoutGrid()
{
	const int32_t width = lastDrawPosition.right - lastDrawPosition.left;
	const int32_t height = lastDrawPosition.bottom - lastDrawPosition.top;

	int32_t borderX(0), borderY(0);
	int32_t currentX = borderX;
	int32_t currentY = borderY;
	int32_t maxChildHeight = 0;

	for(std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		const int32_t childWdt = child->lastDrawPosition.right - child->lastDrawPosition.left;
		const int32_t childHgt = child->lastDrawPosition.bottom - child->lastDrawPosition.top;
		// remember the heighest child
		if (!maxChildHeight || (childHgt > maxChildHeight))
			maxChildHeight = childHgt;

		child->props[C4GuiWindowPropertyName::left].SetInt(currentX);
		child->props[C4GuiWindowPropertyName::right].SetInt(currentX + childWdt);
		child->props[C4GuiWindowPropertyName::top].SetInt(currentY);
		child->props[C4GuiWindowPropertyName::bottom].SetInt(currentY + childHgt);

		currentX += childWdt + borderX;
		if (currentX + childWdt >= width)
		{
			currentX = borderX;
			currentY += maxChildHeight + borderY;
		}
	}

	lastDrawPosition.topMostChild = 0;
	lastDrawPosition.bottomMostChild = currentY;

	// do we need a scroll bar?
	EnableScrollBar(currentY >= height, currentY);
}

void C4GuiWindow::UpdateLayoutVertical()
{
	const int32_t height = lastDrawPosition.bottom - lastDrawPosition.top;

	int32_t borderY(0);
	int32_t currentY = borderY;

	for(std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		const int32_t childHgt = child->lastDrawPosition.bottom - child->lastDrawPosition.top;

		child->props[C4GuiWindowPropertyName::top].SetInt(currentY);
		child->props[C4GuiWindowPropertyName::bottom].SetInt(currentY + childHgt);

		currentY += childHgt + borderY;
	}

	lastDrawPosition.topMostChild = 0;
	lastDrawPosition.bottomMostChild = currentY;

	// do we need a scroll bar?
	EnableScrollBar(currentY >= height, currentY);
}

bool C4GuiWindow::DrawChildren(C4TargetFacet &cgo, int32_t player, float parentLeft, float parentTop, float parentRight, float parentBottom, int32_t withMultipleFlag)
{
	// note that withMultipleFlag only plays a roll for the root-menu
	bool oneDrawn = false; // was at least one child drawn?
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		if (lastDrawPosition.dirty == 1)
			child->lastDrawPosition.dirty = 2;
		if (withMultipleFlag != -1)
		{
			const int32_t &style = child->props[C4GuiWindowPropertyName::style].GetInt();
			if ((withMultipleFlag == 0) &&  (style & C4GuiWindowStyleFlag::Multiple)) continue;
			if ((withMultipleFlag == 1) && !(style & C4GuiWindowStyleFlag::Multiple)) continue;
		}

		if (child->Draw(cgo, player, parentLeft, parentTop, parentRight, parentBottom))
			oneDrawn = true;
		// draw only one window when drawing non-Multiple windows
		if (oneDrawn && (withMultipleFlag == 0)) return true;
	}
	return oneDrawn;
}

bool C4GuiWindow::Draw(C4TargetFacet &cgo, int32_t player)
{
	if (!IsVisible()) return false;
	// assume I am the root and use the whole viewport for drawing - minus some standard border
	const int32_t &left = props[C4GuiWindowPropertyName::left].GetInt();
	const int32_t &right = props[C4GuiWindowPropertyName::right].GetInt();
	const int32_t &top = props[C4GuiWindowPropertyName::top].GetInt();
	const int32_t &bottom = props[C4GuiWindowPropertyName::bottom].GetInt();

	float leftDrawX = cgo.X + left;
	float topDrawY = cgo.Y + top;
	float rightDrawX = cgo.X + cgo.Wdt * cgo.Zoom + right;
	float bottomDrawY = cgo.Y + cgo.Hgt * cgo.Zoom + bottom;

	float wdt = rightDrawX - leftDrawX;
	float hgt = bottomDrawY - topDrawY;

	// abuse properties, we are root, we are allowed to do that
	// rounding against small errors
	if ((int(wdt) != int(lastDrawPosition.right)) || (int(hgt) != int(lastDrawPosition.bottom)))
	{
		//LogF("Updating root lastDrawPosition %f|%f // %f|%f", cgo.X, cgo.Y, cgo.Wdt, cgo.Hgt);
		lastDrawPosition.right = wdt;
		lastDrawPosition.bottom = hgt;
		lastDrawPosition.dirty = 1;
	}
	else
		lastDrawPosition.dirty = 0;

	// step one: draw all non-multiple windows
	DrawChildren(cgo, player, leftDrawX - standardHorizontalBorder, topDrawY  - standardVerticalBorder, rightDrawX + standardHorizontalBorder, bottomDrawY + standardVerticalBorder, 1);
	// TODO: adjust rectangle for main menu if multiple windows exist
	// step two: draw one "main" menu
	DrawChildren(cgo, player, leftDrawX, topDrawY, rightDrawX, bottomDrawY, 0);
	return true;
}

bool C4GuiWindow::Draw(C4TargetFacet &cgo, int32_t player, float parentLeft, float parentTop, float parentRight, float parentBottom)
{
	// message hidden?
	if (!IsVisible()) return false;

	// player can see menu?
	if (target)
		if (!target->IsVisible(player, false))
			return false;
	// fetch style
	const int32_t &style = props[C4GuiWindowPropertyName::style].GetInt();
	// fetch current position as shortcut for overview
	const int32_t &left = props[C4GuiWindowPropertyName::left].GetInt();
	const int32_t &right = props[C4GuiWindowPropertyName::right].GetInt();
	const int32_t &top = props[C4GuiWindowPropertyName::top].GetInt();
	const int32_t &bottom = props[C4GuiWindowPropertyName::bottom].GetInt();

	const float &relLeft = props[C4GuiWindowPropertyName::relLeft].GetFloat();
	const float &relRight = props[C4GuiWindowPropertyName::relRight].GetFloat();
	const float &relTop = props[C4GuiWindowPropertyName::relTop].GetFloat();
	const float &relBottom = props[C4GuiWindowPropertyName::relBottom].GetFloat();

	// calculate drawing rectangle
	float parentWidth = parentRight - parentLeft;
	float parentHeight = parentBottom - parentTop;
	float leftDrawX = parentLeft + relLeft * parentWidth + float(left);
	float rightDrawX = parentLeft + relRight * parentWidth + float(right);
	float topDrawY = parentTop + relTop * parentHeight + float(top);
	float bottomDrawY = parentTop + relBottom * parentHeight + float(bottom);
	float width = rightDrawX - leftDrawX;
	float height = bottomDrawY - topDrawY;
	float childOffsetY = 0.0f; // for scrolling

	// always update drawing position, needed for mouse input etc.
	lastDrawPosition.left = leftDrawX;
	lastDrawPosition.right = rightDrawX;
	lastDrawPosition.top = topDrawY;
	lastDrawPosition.bottom = bottomDrawY;

	// do we need to update children positions etc.?
	bool updateLayout = lastDrawPosition.dirty == 1;
	if (lastDrawPosition.dirty > 0)
	{
		--lastDrawPosition.dirty;

		if (updateLayout)
			UpdateLayout();
	}
	// check whether we are scrolling
	float childHgt = lastDrawPosition.bottomMostChild - lastDrawPosition.topMostChild;

	if (scrollBar)
		childOffsetY = -1.0f * (scrollBar->offset * (childHgt - height));

	// if ANY PARENT has scroll bar, then adjust clipper
	float clipX1(0.0f), clipX2(0.0f), clipY1(0.0f), clipY2(0.0f);
	bool clipping = parent->GetClippingRect(clipX1, clipY1, clipX2, clipY2);
	if (clipping)
	{
		pDraw->StorePrimaryClipper();
		pDraw->SetPrimaryClipper(int32_t(clipX1), int32_t(clipY1), int32_t(clipX2), int32_t(clipY2));
	}

	// draw various properties
	C4Facet cgoOut(cgo.Surface, leftDrawX, topDrawY, width, height);

	const int32_t &backgroundColor = props[C4GuiWindowPropertyName::backgroundColor].GetInt();
	if (backgroundColor)
		pDraw->DrawBoxDw(cgo.Surface, leftDrawX, topDrawY, rightDrawX - 1.0f, bottomDrawY - 1.0f, backgroundColor);

	C4GUI::FrameDecoration *frameDecoration = props[C4GuiWindowPropertyName::frameDecoration].GetFrameDecoration();

	if (frameDecoration)
	{
		C4Rect rect(leftDrawX - cgo.TargetX - frameDecoration->iBorderLeft, topDrawY - cgo.TargetY - frameDecoration->iBorderTop, width + frameDecoration->iBorderRight, height + frameDecoration->iBorderBottom);
		frameDecoration->Draw(cgo, rect);
	}

	C4Object *symbolObject = props[C4GuiWindowPropertyName::symbolObject].GetObject();
	if (symbolObject)
	{
		symbolObject->DrawPicture(cgoOut, false, NULL);
	}
	else
	{
		C4Def *symbolDef = props[C4GuiWindowPropertyName::symbolDef].GetDef();
		if (symbolDef)
		{
			symbolDef->Draw(cgoOut);
		}
	}

	StdCopyStrBuf *strBuf = props[C4GuiWindowPropertyName::text].GetStrBuf();

	if (strBuf)
	{
		StdStrBuf sText;
		int alignment = ALeft;
		int32_t textHgt = ::GraphicsResource.FontRegular.BreakMessage(strBuf->getData(), int32_t(width), &sText, true);
		float textYOffset = 0.0f, textXOffset = 0.0f;
		if (style & C4GuiWindowStyleFlag::TextVCenter)
			textYOffset = height/2.0f - float(textHgt)/2.0f;
		else if (style & C4GuiWindowStyleFlag::TextBottom)
			textYOffset += height - float(textHgt);
		if (style & C4GuiWindowStyleFlag::TextHCenter)
		{
			int wdt, hgt;
			::GraphicsResource.FontRegular.GetTextExtent(sText.getData(), wdt, hgt, true);
			textXOffset = width/2.0f - float(wdt)/2.0f;
		}
		else if (style & C4GuiWindowStyleFlag::TextRight)
		{
			alignment = ARight;
			int wdt, hgt;
			::GraphicsResource.FontRegular.GetTextExtent(sText.getData(), wdt, hgt, true);
			textXOffset = width - float(wdt);
		}
		pDraw->TextOut(sText.getData(), ::GraphicsResource.FontRegular, 1.0, cgo.Surface, cgo.X + leftDrawX + textXOffset, cgo.Y + topDrawY + textYOffset, 0xffffffff, ALeft);
		// enable auto scroll
		float textBottom = lastDrawPosition.top + float(textHgt);
		if (textBottom > lastDrawPosition.bottom)
			lastDrawPosition.bottom = textBottom;
	}

	if (clipping)
	{
		pDraw->RestorePrimaryClipper();
	}

	if (GraphicsSystem.ShowMenuInfo) // print helpful debug info
	{
		pDraw->DrawFrameDw(cgo.Surface, leftDrawX, topDrawY, rightDrawX,bottomDrawY, clipping ? C4RGB(255, 255, 0) :C4RGB(0, 255, 0));
		StdStrBuf buf = FormatString("%s(%d)", target ? target->GetName() : "", id);
		pDraw->TextOut(buf.getData(), ::GraphicsResource.FontCaption, 1.0, cgo.Surface, cgo.X + leftDrawX, cgo.Y + topDrawY, 0xffff00ff, ALeft);
	}

	if (scrollBar)
	{
		scrollBar->Draw(cgo, player, leftDrawX, topDrawY, rightDrawX, bottomDrawY);
	}

	DrawChildren(cgo, player, leftDrawX, topDrawY + childOffsetY, rightDrawX, bottomDrawY + childOffsetY);
	return true;
}

bool C4GuiWindow::GetClippingRect(float &left, float &top, float &right, float &bottom)
{
	if (scrollBar)
	{
		left = lastDrawPosition.left;
		right = lastDrawPosition.right;
		top = lastDrawPosition.top;
		bottom = lastDrawPosition.bottom;
		return true;
	}
	if (parent)
		return parent->GetClippingRect(left, top, right, bottom);
	return false;
}

void C4GuiWindow::SetTag(C4String *tag)
{
	// set tag on all properties
	for (uint32_t i = 0; i < C4GuiWindowPropertyName::_lastProp; ++i)
		if (props[i].SwitchTag(tag))
		{
			// only if tag could have changed position etc.
			if (i <= C4GuiWindowPropertyName::relBottom || i == C4GuiWindowPropertyName::text || i == C4GuiWindowPropertyName::style || i == C4GuiWindowPropertyName::priority)
			if (parent)
			{
				parent->lastDrawPosition.dirty = 2;
			}

		}

	// .. and children
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
		(*iter)->SetTag(tag);
}

void C4GuiWindow::OnMouseIn(int32_t player)
{
	assert(!hasMouseFocus && "custom menu window properly loaded incorrectly!");
	hasMouseFocus = true;

	// no need to notify children, this is done in MouseInput

	// execute action
	int32_t actionType = C4GuiWindowPropertyName::onMouseInAction;
	C4GuiWindowAction *action = props[actionType].GetAction();
	if (!action) return;
	action->Execute(this, player, actionType);
}

void C4GuiWindow::OnMouseOut(int32_t player)
{
	assert(hasMouseFocus && "custom menu window properly loaded incorrectly!");
	hasMouseFocus = false;

	// needs to notify children
	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		if (child->hasMouseFocus)
			child->OnMouseOut(player);
	}

	// execute action
	int32_t actionType = C4GuiWindowPropertyName::onMouseOutAction;
	C4GuiWindowAction *action = props[actionType].GetAction();
	if (!action) return;
	action->Execute(this, player, actionType);
}

bool C4GuiWindow::MouseInput(int32_t player, int32_t button, int32_t mouseX, int32_t mouseY, DWORD dwKeyParam)
{
	// special handling for root
	if (!parent)
	{
		// non-multiple-windows have a higher priority
		// this is important since they are also drawn on top
		for (int withMultipleFlag = 0; withMultipleFlag <= 1; ++withMultipleFlag)
		{
			for (std::list<C4GuiWindow*>::reverse_iterator iter = children.rbegin(); iter != children.rend(); ++iter)
			{
				C4GuiWindow *child = *iter;

				const int32_t &style = child->props[C4GuiWindowPropertyName::style].GetInt();
				if ((withMultipleFlag == 0) &&  (style & C4GuiWindowStyleFlag::Multiple)) continue;
				if ((withMultipleFlag == 1) && !(style & C4GuiWindowStyleFlag::Multiple)) continue;

				int32_t childLeft = static_cast<int32_t>(child->lastDrawPosition.left);
				int32_t childRight = static_cast<int32_t>(child->lastDrawPosition.right);
				int32_t childTop = static_cast<int32_t>(child->lastDrawPosition.top);
				int32_t childBottom = static_cast<int32_t>(child->lastDrawPosition.bottom);
				//LogF("%d|%d in %d|%d // %d|%d", mouseX, mouseY, childLeft, childTop, childRight, childBottom);
				bool inArea = true;
				if ((mouseX < childLeft) || (mouseX > childRight)) inArea = false;
				else if ((mouseY < childTop) || (mouseY > childBottom)) inArea = false;

				if (!inArea) // notify child if it had mouse focus before
				{
					if (child->hasMouseFocus)
						child->OnMouseOut(player);
					continue;
				}

				if (child->MouseInput(player, button, mouseX, mouseY, dwKeyParam))
					return true;
			}
		}
		return false;
	}

	// completely ignore mouse if the appropriate flag is set
	const int32_t &style = props[C4GuiWindowPropertyName::style].GetInt();
	if (style & C4GuiWindowStyleFlag::IgnoreMouse)
		return false;

	if (!visible) return false;

	if (target)
		if (!target->IsVisible(player, false))
			return false;

	// we have mouse focus! Is this new?
	if (!hasMouseFocus)
		OnMouseIn(player);

	/*if (parent && mouse.IsLDown())
		LogF("%f|%f - %d|%d", lastDrawPosition.left, lastDrawPosition.top, mouseX, mouseY);
	else LogF("called on root %d|%d", mouseX, mouseY);*/

	// children actually have a higher priority
	bool overChild = false; // remember for later, catch all actions that are in theory over children, even if not reaction (if main window)
	// use reverse iterator since children with higher Priority appear later in the list
	for (std::list<C4GuiWindow*>::reverse_iterator iter = children.rbegin(); iter != children.rend(); ++iter)
	{
		C4GuiWindow *child = *iter;
		int32_t childLeft = static_cast<int32_t>(child->lastDrawPosition.left);
		int32_t childRight = static_cast<int32_t>(child->lastDrawPosition.right);
		int32_t childTop = static_cast<int32_t>(child->lastDrawPosition.top);
		int32_t childBottom = static_cast<int32_t>(child->lastDrawPosition.bottom);
		//LogF("%d|%d in %d|%d // %d|%d", mouseX, mouseY, childLeft, childTop, childRight, childBottom);
		bool inArea = true;
		if ((mouseX < childLeft) || (mouseX > childRight)) inArea = false;
		else if ((mouseY < childTop) || (mouseY > childBottom)) inArea = false;

		if (!inArea) // notify child if it had mouse focus before
		{
			if (child->hasMouseFocus)
				child->OnMouseOut(player);
			continue;
		}

		overChild = true;
		if (child->MouseInput(player, button, mouseX, mouseY, dwKeyParam))
			return true;
	}

	if (button == C4MC_Button_LeftDown)
	{
		C4GuiWindowAction *action = props[C4GuiWindowPropertyName::onClickAction].GetAction();
		if (action)
		{
			action->Execute(this, player, C4GuiWindowPropertyName::onClickAction);
			return true;
		}
	}

	// for scroll-enabled windows, scroll contents with wheel
	if (scrollBar && (button == C4MC_Button_Wheel))
	{
		short delta = (short)(dwKeyParam >> 16);
		float fac = (lastDrawPosition.bottomMostChild - lastDrawPosition.topMostChild);
		if (fac == 0.0f) fac = 1.0f;
		scrollBar->ScrollBy(-float(delta) / fac);
		return true;
	}

	// forward to scroll-bar if in area
	if (scrollBar)
	{
		if (mouseX >= lastDrawPosition.right - 50.0f)
			return scrollBar->MouseInput(button, mouseX, mouseY, dwKeyParam);
	}

	// if the user still clicked on a menu - even if it didn't do anything, catch it
	// but do that only on the top-level to not stop traversin other branches
	if (isMainWindow)
		return overChild;
	return false;
}

bool C4GuiWindow::ExecuteCommand(int32_t actionID, int32_t player, int32_t subwindowID, int32_t actionType, C4Object *target)
{
	if (isMainWindow && subwindowID) // we are a main window! try a shortcut through the ID?
	{
		//LogF("passing command... %d, %d, %d, %d, %d [I am %d, MW]", actionID, player, subwindowID, actionType, tag, id);
		// the reasoning for that shortcut is that I assume that usually windows with actions will also have an ID assigned
		// this obviously doesn't have to be the case, but I believe it's worth the try
		std::pair<std::multimap<int32_t, C4GuiWindow*>::iterator, std::multimap<int32_t, C4GuiWindow*>::iterator> range;
		range = childrenIDMap.equal_range(subwindowID);

		for (std::multimap<int32_t, C4GuiWindow*>::iterator iter = range.first; iter != range.second; ++iter)
		{
			if (iter->second->ExecuteCommand(actionID, player, subwindowID, actionType, target))
				return true;
		}
		// it is not possible that another window would match the criteria. Abort later after self-check
	}

	// are we elligible?
	if ((id == subwindowID) && (this->target == target))
	{

		std::list<C4GuiWindowAction*> allActions = props[actionType].GetAllActions();
		for (std::list<C4GuiWindowAction*>::iterator iter = allActions.begin(); iter != allActions.end(); ++iter)
		{
			C4GuiWindowAction *action = *iter;
			assert(action && "C4GuiWindowProperty::GetAllActions returned list with null-pointer");

			if (action->ExecuteCommand(actionID, this, player))
				return true;
		}

		// note that we should not simply return false here
		// there is no guarantee that only one window with that target&ID existss
	}

	// not caught, forward to children!
	// abort if main window, though. See above
	if (isMainWindow && subwindowID) return false;

	for (std::list<C4GuiWindow*>::iterator iter = children.begin(); iter != children.end(); ++iter)
	{
		C4GuiWindow *child = *iter;
		if (child->ExecuteCommand(actionID, player, subwindowID, actionType, target))
			return true;
	}
	return false;
}