/* @@@LICENSE
*
*      Copyright (c) 2009-2013 LG Electronics, Inc.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* LICENSE@@@ */

#ifndef __ACTIVITYMANAGER_DEFAULTREQUIREMENTMANAGER_H__
#define __ACTIVITYMANAGER_DEFAULTREQUIREMENTMANAGER_H__

#include "RequirementManager.h"

class Requirement;

class DefaultRequirementManager : public RequirementManager
{
public:
	DefaultRequirementManager();
	virtual ~DefaultRequirementManager();

	virtual const std::string& GetName() const;

	virtual boost::shared_ptr<Requirement> InstantiateRequirement(
		boost::shared_ptr<Activity> activity, const std::string& name,
		const MojObject& value);

	virtual void RegisterRequirements(
		boost::shared_ptr<MasterRequirementManager> master);
	virtual void UnregisterRequirements(
		boost::shared_ptr<MasterRequirementManager> master);

protected:
	boost::shared_ptr<RequirementCore>	m_neverRequirementCore;

	/* Track who for debugging purposes */
	RequirementList		m_neverRequirements;

	static MojLogger	s_log;
};

#endif /* __ACTIVITYMANAGER_DEFAULTREQUIREMENTMANAGER_H__ */
