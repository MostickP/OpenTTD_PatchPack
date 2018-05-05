/* $Id: subsidy_base.h 23704 2012-01-01 17:22:32Z alberth $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file subsidy_base.h %Subsidy base class. */

#ifndef SUBSIDY_BASE_H
#define SUBSIDY_BASE_H

#include "cargo_type.h"
#include "company_type.h"
#include "subsidy_type.h"
#include "core/pool_type.hpp"

typedef Pool<Subsidy, SubsidyID, 1, 256> SubsidyPool;
extern SubsidyPool _subsidy_pool;

/** Struct about subsidies, offered and awarded */
struct Subsidy : SubsidyPool::PoolItem<&_subsidy_pool> {
	CargoID cargo_type;      ///< Cargo type involved in this subsidy, CT_INVALID for invalid subsidy
	byte remaining;          ///< Remaining months when this subsidy is valid
	CompanyByte awarded;     ///< Subsidy is awarded to this company; INVALID_COMPANY if it's not awarded to anyone
	SourceTypeByte src_type; ///< Source of subsidised path (ST_INDUSTRY or ST_TOWN)
	SourceTypeByte dst_type; ///< Destination of subsidised path (ST_INDUSTRY or ST_TOWN)
	SourceID src;            ///< Index of source. Either TownID or IndustryID
	SourceID dst;            ///< Index of destination. Either TownID or IndustryID

	/**
	 * We need an (empty) constructor so struct isn't zeroed (as C++ standard states)
	 */
	inline Subsidy() { }

	/**
	 * (Empty) destructor has to be defined else operator delete might be called with nullptr parameter
	 */
	inline ~Subsidy() { }

	/**
	 * Tests whether this subsidy has been awarded to someone
	 * @return is this subsidy awarded?
	 */
	inline bool IsAwarded() const
	{
		return this->awarded != INVALID_COMPANY;
	}

	void AwardTo(CompanyID company);
};

/** Constants related to subsidies */
static const uint SUBSIDY_OFFER_MONTHS         =  12; ///< Duration of subsidy offer
static const uint SUBSIDY_CONTRACT_MONTHS      =  12; ///< Duration of subsidy after awarding
static const uint SUBSIDY_PAX_MIN_POPULATION   = 400; ///< Min. population of towns for subsidised pax route
static const uint SUBSIDY_CARGO_MIN_POPULATION = 900; ///< Min. population of destination town for cargo route
static const uint SUBSIDY_MAX_PCT_TRANSPORTED  =  42; ///< Subsidy will be created only for towns/industries with less % transported
static const uint SUBSIDY_MAX_DISTANCE         =  70; ///< Max. length of subsidised route (DistanceManhattan)

#define FOR_ALL_SUBSIDIES_FROM(var, start) FOR_ALL_ITEMS_FROM(Subsidy, subsidy_index, var, start)
#define FOR_ALL_SUBSIDIES(var) FOR_ALL_SUBSIDIES_FROM(var, 0)

#endif /* SUBSIDY_BASE_H */
