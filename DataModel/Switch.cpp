/*
RailControl - Model Railway Control Software

Copyright (c) 2017-2021 Dominik (Teddy) Mahrer - www.railcontrol.org

RailControl is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

RailControl is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RailControl; see the file LICENCE. If not see
<http://www.gnu.org/licenses/>.
*/

#include <map>

#include "DataModel/Switch.h"
#include "Utils/Utils.h"

using std::map;
using std::stringstream;
using std::string;

namespace DataModel
{
	std::string Switch::Serialize() const
	{
		string str = "objectType=Switch;";
		str += ";";
		str += AccessoryBase::Serialize();
		str += ";";
		str += LayoutItem::Serialize();
		str += LockableItem::Serialize();
		return str;
	}

	bool Switch::Deserialize(const std::string& serialized)
	{
		map<string,string> arguments;
		ParseArguments(serialized, arguments);
		string objectType = Utils::Utils::GetStringMapEntry(arguments, "objectType");
		if (objectType.compare("Switch") != 0)
		{
			return false;
		}

		AccessoryBase::Deserialize(arguments);
		LayoutItem::Deserialize(arguments);
		LockableItem::Deserialize(arguments);
		SetWidth(Width1);
		SetHeight(Height1);
		SetVisible(VisibleYes);
		return true;
	}

	void Switch::SetAccessoryState(const AccessoryState state)
	{
		AccessoryState checkedState = state;
		if (accessoryType != SwitchTypeThreeWay && state == SwitchStateThird)
		{
			checkedState = SwitchStateTurnout;
		}
		AccessoryBase::SetAccessoryState(checkedState);
	}

	std::map<DataModel::AccessoryState, Languages::TextSelector> Switch::GetStateOptions() const
	{
		std::map<DataModel::AccessoryState,Languages::TextSelector> out;
		out[DataModel::SwitchStateStraight] = Languages::TextStraight;
		switch(accessoryType)
		{
			case DataModel::SwitchTypeThreeWay:
				out[DataModel::SwitchStateTurnout] = Languages::TextLeft;
				out[DataModel::SwitchStateThird] = Languages::TextRight;
				break;

			default:
				out[DataModel::SwitchStateTurnout] = Languages::TextTurnout;
				break;
		}
		return out;
	}
} // namespace DataModel

