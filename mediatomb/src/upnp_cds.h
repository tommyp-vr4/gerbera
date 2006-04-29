/*  upnp_cds.h - this file is part of MediaTomb.
                                                                                
    Copyright (C) 2005 Gena Batyan <bgeradz@deadlock.dhs.org>,
                       Sergey Bostandzhyan <jin@deadlock.dhs.org>
                                                                                
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
                                                                                
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                                                                                
    You should have received a copy of the GNU General Public License
    along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/// \file upnp_cds.h
/// \brief Definition of the ContentDirectoryService class.
#ifndef __UPNP_CDS_H__
#define __UPNP_CDS_H__

#include "common.h"
#include "action_request.h"
#include "subscription_request.h"

/// \brief This class is responsible for the UPnP Content Directory Service operations.
///
/// Handles subscription and action invocation requests for the CDS.
class ContentDirectoryService : public zmm::Object
{
protected:
    /// \brief UPnP standard defined service type
    /// \todo Check if it makes sense to use it as it is done now...why not define constants here?
    zmm::String serviceType;
    /// \brief ID of the service.
    zmm::String serviceID;

    /// \brief The system update ID indicates changes in the content directory.
    ///
    /// Whenever something in the content directory changes, the value of
    /// systemUpdateID is increased and an event is sent out to all subscribed
    /// devices.
    /// Also, this variable is returned by the upnp_action_GetSystemUpdateID()
    /// action.
    int systemUpdateID;

    /// \brief UPnP standard defined action: Browse()
    /// \param request Incoming ActionRequest.
    ///
    /// Browse(string ObjectID, string BrowseFlag, string Filter, ui4 StartingIndex, 
    /// ui4 RequestedCount, string SortCriteria, string Result, ui4 NumberReturned, 
    /// ui4 TotalMatches, ui4 UpdateID)
    void upnp_action_Browse(zmm::Ref<ActionRequest> request);

    /// \brief UPnP standard defined action: GetSearchCapabilities()
    /// \param request Incoming ActionRequest.
    ///
    /// GetSearchCapabilities(string SearchCaps)
    void upnp_action_GetSearchCapabilities(zmm::Ref<ActionRequest> request);

    /// \brief UPnP standard defined action: GetSortCapabilities() 
    /// \param request Incoming ActionRequest.
    ///
    /// GetSortCapabilities(string SortCaps)
    void upnp_action_GetSortCapabilities(zmm::Ref<ActionRequest> request);

    /// \brief UPnP standard defined action: GetSystemUpdateID()
    /// \param request Incoming ActionRequest.
    ///
    /// GetSystemUpdateID(ui4 Id)
    void upnp_action_GetSystemUpdateID(zmm::Ref<ActionRequest> request);
    
public:
    /// \brief Constructor for the CDS, saves the service type and service id
    /// in internal variables.
    /// \todo Check if it makes sense to use it as it is done now...why not define them as constants?
    ContentDirectoryService(zmm::String serviceType, zmm::String serviceID);

    /// \todo what is that here?? only getIntsance should be available, creating a new instance if called for the 1st time.
    static zmm::Ref<ContentDirectoryService> createInstance(zmm::String serviceType, zmm::String serviceID);
    static zmm::Ref<ContentDirectoryService> getInstance();

    /// \brief Dispatches the ActionRequest between the available actions.
    /// \param request ActionRequest to be processed by the function.
    ///
    /// This function looks at the incoming ActionRequest and passes it on
    /// to the appropriate action for processing.
    void process_action_request(zmm::Ref<ActionRequest> request);

    /// \brief Processes an incoming SubscriptionRequest.
    /// \param request SubscriptionRequest to be processed by the function.
    ///
    /// Looks at the incoming SubscriptionRequest and accepts the subscription
    /// if everything is ok.
    void process_subscription_request(zmm::Ref<SubscriptionRequest> request);

    /// \brief Sends out an event to all subscribed devices.
    /// \param containerUpdateIDs_CSV Comma Separated Value list of container update ID's (as defined in the UPnP CDS specs)
    /// 
    /// When something in the content directory chagnes, we will send out
    /// an event to all subscribed devices. Container updates are supported,
    /// and of course the mimimum required - systemUpdateID.
    void subscription_update(zmm::String containerUpdateIDs_CSV);
};

#endif // __UPNP_CDS_H__
