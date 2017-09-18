/* ============================================================
 *
 * This file is part of the rsb-spread project
 *
 * Copyright (C) 2010 Sebastian Wrede <swrede@techfak.uni-bielefeld.de>
 *
 * This file may be licensed under the terms of the
 * GNU Lesser General Public License Version 3 (the ``LGPL''),
 * or (at your option) any later version.
 *
 * Software distributed under the License is distributed
 * on an ``AS IS'' basis, WITHOUT WARRANTY OF ANY KIND, either
 * express or implied. See the LGPL for the specific language
 * governing rights and limitations.
 *
 * You should have received a copy of the LGPL along with this
 * program. If not, go to http://www.gnu.org/licenses/lgpl.html
 * or write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The development of this software was supported by:
 *   CoR-Lab, Research Institute for Cognition and Robotics
 *     Bielefeld University
 *
 * ============================================================ */

#pragma once

#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/condition.hpp>

#include <rsc/threading/RepetitiveTask.h>

#include <rsb/MetaData.h>
#include <rsb/EventId.h>
#include <rsb/Scope.h>
#include <rsb/Event.h>

#include <rsb/transport/OutConnector.h>

namespace rsb {
namespace test {

/**
 * @author swrede
 */
class InformerTask: public rsc::threading::RepetitiveTask {
public:
    InformerTask(rsb::transport::OutConnectorPtr p,
                 const Scope& scope,
                 const unsigned int& numEvents,
                 const unsigned int& dataSizeInBytes);
    virtual ~InformerTask();

    void execute();

    /**
     * Not thread-safe. Use this only after joining the task.
     *
     * @return all sent events
     */
    std::vector<EventPtr> getEvents();

private:
    Scope scope;
    unsigned int numEvents;
    unsigned int sentEvents;
    rsb::transport::OutConnectorPtr connector;
    std::vector<EventPtr> events;
    boost::shared_ptr<std::string> data;
    rsc::misc::UUID id;

};

/**
 * @author jwienke
 */
class WaitingObserver {
public:

    WaitingObserver(const Scope& scope,
                    const unsigned int& expectedEvents);

    void handler(EventPtr event);

    bool waitReceived(const unsigned int& timeoutMs = 0);

    std::vector<EventPtr> getEvents();

    const Scope& getScope() const;

private:
    Scope scope;

    unsigned int expectedEvents;
    unsigned int receivedEvents;

    std::vector<EventPtr> events;

    boost::recursive_mutex m;
    boost::condition condition;

};

}
}
