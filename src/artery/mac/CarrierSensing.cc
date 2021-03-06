//
// Copyright (C) 2014 Raphael Riebl <raphael.riebl@thi.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "CarrierSensing.h"
#include <omnetpp/cexception.h>
#include <omnetpp/csimulation.h>
#include <cassert>

CarrierSensing::CarrierSensing() : mState(IDLE)
{
}

CarrierSensing::~CarrierSensing()
{
}

void CarrierSensing::setState(State state)
{
	if (state == mState) return;

	switch (state) {
		case IDLE:
		case BUSY_PHYSICAL:
		case BUSY_SELF:
			mSince = omnetpp::simTime();
			mState = state;
			break;
		default:
			throw omnetpp::cRuntimeError("Unknown carrier sensing state");
			break;
	}
}

boost::optional<omnetpp::SimTime> CarrierSensing::getIdleDuration() const
{
	boost::optional<omnetpp::SimTime> idleDuration;
	if (isIdle()) {
		idleDuration = omnetpp::simTime() - getStateSince();
		assert(idleDuration.get() >= 0);
	}
	return idleDuration;
}
