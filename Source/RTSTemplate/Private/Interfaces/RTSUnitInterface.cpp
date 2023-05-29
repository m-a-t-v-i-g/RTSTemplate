// Real Time Strategy C++ template by matvig.

#include "Interfaces/RTSUnitInterface.h"

int IRTSUnitInterface::GetUnitPlayerID()
{
	return 0;
}

bool IRTSUnitInterface::SetUnitIsFound(bool SetFound)
{
	return SetFound;
}

bool IRTSUnitInterface::SetUnitIsSelected(bool SetSelected)
{
	return SetSelected;
}

bool IRTSUnitInterface::CanBeFound()
{
	return !bIsSelected;
}

bool IRTSUnitInterface::CanBeSelected()
{
	return !bIsSelected;
}

void IRTSUnitInterface::MoveToDestination()
{

}

