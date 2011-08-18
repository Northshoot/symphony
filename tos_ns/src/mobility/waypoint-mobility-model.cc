/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Phillip Sitbon
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Phillip Sitbon <phillip@sitbon.net>
 */
#include <limits>
#include "ns3/abort.h"
#include "ns3/simulator.h"
#include "ns3/uinteger.h"
#include "ns3/log.h"
#include "ns3/boolean.h"
#include "waypoint-mobility-model.h"
#include "ns3/config.h"
#include "ns3/test.h"

NS_LOG_COMPONENT_DEFINE ("WaypointMobilityModel");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (WaypointMobilityModel);


TypeId
WaypointMobilityModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WaypointMobilityModel")
    .SetParent<MobilityModel> ()
    .SetGroupName ("Mobility")
    .AddConstructor<WaypointMobilityModel> ()
    .AddAttribute ("NextWaypoint", "The next waypoint used to determine position.",
                   TypeId::ATTR_GET,
                   WaypointValue (),
                   MakeWaypointAccessor (&WaypointMobilityModel::GetNextWaypoint),
                   MakeWaypointChecker ())
    .AddAttribute ("WaypointsLeft", "The number of waypoints remaining.",
                   TypeId::ATTR_GET,
                   UintegerValue (0),
                   MakeUintegerAccessor (&WaypointMobilityModel::WaypointsLeft),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("LazyNotify", "Only call NotifyCourseChange when position is calculated.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WaypointMobilityModel::m_lazyNotify),
                   MakeBooleanChecker ())
    .AddAttribute ("InitialPositionIsWaypoint", "Calling SetPosition with no waypoints creates a waypoint.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WaypointMobilityModel::m_initialPositionIsWaypoint),
                   MakeBooleanChecker ())
  ;
  return tid;
}


WaypointMobilityModel::WaypointMobilityModel ()
  : m_first (true),
    m_lazyNotify (false),
    m_initialPositionIsWaypoint (false)
{
}
WaypointMobilityModel::~WaypointMobilityModel ()
{
}
void
WaypointMobilityModel::DoDispose (void)
{
  MobilityModel::DoDispose ();
}
void
WaypointMobilityModel::AddWaypoint (const Waypoint &waypoint)
{
  if ( m_first )
    {
      m_first = false;
      m_current = m_next = waypoint;
    }
  else
    {
      NS_ABORT_MSG_IF ( !m_waypoints.empty () && (m_waypoints.back ().time >= waypoint.time),
                        "Waypoints must be added in ascending time order");
      m_waypoints.push_back (waypoint);
    }

  if ( !m_lazyNotify )
    {
      Simulator::Schedule (waypoint.time, &WaypointMobilityModel::Update, this);
    }
}
Waypoint
WaypointMobilityModel::GetNextWaypoint (void) const
{
  Update ();
  return m_next;
}
uint32_t
WaypointMobilityModel::WaypointsLeft (void) const
{
  Update ();
  return m_waypoints.size ();
}
void
WaypointMobilityModel::Update (void) const
{
  const Time now = Simulator::Now ();
  bool newWaypoint = false;

  if ( now < m_current.time )
    {
      return;
    }

  while ( now >= m_next.time  )
    {
      if ( m_waypoints.empty () )
        {
          if ( m_current.time <= m_next.time )
            {
              /*
                Set m_next.time = -1 to make sure this doesn't happen more than once.
                The comparison here still needs to be '<=' in the case of mobility with one waypoint.
              */
              m_next.time = Seconds (-1.0);
              m_current.position = m_next.position;
              m_current.time = now;
              m_velocity = Vector (0,0,0);
              NotifyCourseChange ();
            }
          else
            {
              m_current.time = now;
            }

          return;
        }

      m_current = m_next;
      m_next = m_waypoints.front ();
      m_waypoints.pop_front ();
      newWaypoint = true;

      const double t_span = (m_next.time - m_current.time).GetSeconds ();
      NS_ASSERT (t_span > 0);
      m_velocity.x = (m_next.position.x - m_current.position.x) / t_span;
      m_velocity.y = (m_next.position.y - m_current.position.y) / t_span;
      m_velocity.z = (m_next.position.z - m_current.position.z) / t_span;
    }

  if ( now > m_current.time ) // Won't ever be less, but may be equal
    {
      const double t_diff = (now - m_current.time).GetSeconds ();
      m_current.position.x += m_velocity.x * t_diff;
      m_current.position.y += m_velocity.y * t_diff;
      m_current.position.z += m_velocity.z * t_diff;
      m_current.time = now;
    }

  if ( newWaypoint )
    {
      NotifyCourseChange ();
    }
}
Vector
WaypointMobilityModel::DoGetPosition (void) const
{
  Update ();
  return m_current.position;
}
void
WaypointMobilityModel::DoSetPosition (const Vector &position)
{
  const Time now = Simulator::Now ();

  if ( m_first && m_initialPositionIsWaypoint )
    {
      AddWaypoint (Waypoint (now, position));
      return;
    }

  Update ();
  m_current.time = std::max (now, m_next.time);
  m_current.position = position;
  m_velocity = Vector (0,0,0);

  if ( !m_first && (now >= m_current.time) )
    {
      // This is only a course change if the node is actually moving
      NotifyCourseChange ();
    }
}
void
WaypointMobilityModel::EndMobility (void)
{
  m_waypoints.clear ();
  m_current.time = Seconds (std::numeric_limits<double>::infinity ());
  m_next.time = m_current.time;
  m_first = true;
}
Vector
WaypointMobilityModel::DoGetVelocity (void) const
{
  return m_velocity;
}

class WaypointMobilityModelNotifyTest : public TestCase
{
public:
  WaypointMobilityModelNotifyTest (bool lazy)
    : TestCase (lazy ? "Check Waypoint Mobility Model LAZY notification accuracy"
                  : "Check Waypoint Mobility Model NON-LAZY notification accuracy"),
      lazyNotify (lazy)
  {
  }
  virtual ~WaypointMobilityModelNotifyTest ()
  {
  }

private:
  std::vector<Ptr<MobilityModel> > mobilityStack;
  uint32_t mobilityCount;
  uint32_t waypointCount;
  std::deque<Waypoint> waypoints;
  bool lazyNotify;
private:
  virtual void DoRun (void);
  void ForceUpdates (void);
  void CourseChangeCallback (std::string path, Ptr<const MobilityModel> model);
};
void
WaypointMobilityModelNotifyTest::DoRun (void)
{
  mobilityCount = 1;
  waypointCount = 100;

  ObjectFactory mobilityFactory;
  mobilityFactory.SetTypeId ("ns3::WaypointMobilityModel");
  mobilityFactory.Set ("LazyNotify", BooleanValue (lazyNotify));

  // Populate the vector of mobility models.
  for (uint32_t i = 0; i < mobilityCount; i++)
    {
      // Create a new mobility model.
      Ptr<MobilityModel> model = mobilityFactory.Create ()->GetObject<MobilityModel> ();

      // Add this mobility model to the stack.
      mobilityStack.push_back (model);
      Simulator::Schedule (Seconds (0.0), &Object::Start, model);
    } 

  Waypoint wpt (Seconds (0.0), Vector (0.0, 0.0, 0.0));

  // Create waypoints
  for ( uint32_t iw = 0; iw < waypointCount; ++iw )
    {
      wpt.time += Seconds (1.0);
      waypoints.push_back (wpt);
    }

  // Add the same waypoints to each node
  std::vector<Ptr<MobilityModel> >::iterator i;
  for (i = mobilityStack.begin (); i != mobilityStack.end (); ++i)
    {
      Ptr<WaypointMobilityModel> mob = (*i)->GetObject<WaypointMobilityModel> ();

      for ( std::deque<Waypoint>::iterator w = waypoints.begin (); w != waypoints.end (); ++w )
        {
          mob->AddWaypoint (*w);
        }
    }

  // Schedule updates at non-waypoint times to make sure lazy notifications don't happen
  for ( double updateTime = 0.5; updateTime <= ((double)waypointCount + 1.5); updateTime += 1.0 )
    {
      Simulator::Schedule (Seconds (updateTime), &WaypointMobilityModelNotifyTest::ForceUpdates, this);
    }

  Config::Connect ("/NodeList/*/$ns3::WaypointMobilityModel/CourseChange",
                   MakeCallback (&WaypointMobilityModelNotifyTest::CourseChangeCallback, this));

  Simulator::Stop (Seconds ((double)waypointCount + 2.0));
  Simulator::Run ();
  Simulator::Destroy ();
}
void
WaypointMobilityModelNotifyTest::ForceUpdates (void)
{
  std::vector<Ptr<MobilityModel> >::iterator i;
  for (i = mobilityStack.begin (); i != mobilityStack.end (); ++i)
    {
      Ptr<WaypointMobilityModel> mob = (*i)->GetObject<WaypointMobilityModel> ();
      mob->Update ();
    }
}
void
WaypointMobilityModelNotifyTest::CourseChangeCallback (std::string path, Ptr<const MobilityModel> model)
{
  const Time now = Simulator::Now ();
  const double sec = now.GetSeconds ();
  Ptr<const WaypointMobilityModel> mob = model->GetObject<WaypointMobilityModel> ();

  NS_TEST_EXPECT_MSG_EQ (now, mob->m_current.time, "Waypoint time not properly updated");

  if ( !lazyNotify )
    {
      // All waypoints are on second boundaries only
      NS_TEST_EXPECT_MSG_EQ (sec - ((double)((int)sec)) + sec, sec,
                             "Course didn't change on one second time boundary with NON-LAZY notifcations");
    }
  else
    {
      // Updates should happen at the times they are forced, in between waypoints.
      NS_TEST_EXPECT_MSG_EQ (sec - ((double)((int)sec)), 0.5,
                             "Course didn't change between waypoints with LAZY notifications");
    }
}

static struct WaypointMobilityModelTestSuite : public TestSuite
{
  WaypointMobilityModelTestSuite () : TestSuite ("waypoint-mobility-model", UNIT)
  {
    AddTestCase (new WaypointMobilityModelNotifyTest (true));
    AddTestCase (new WaypointMobilityModelNotifyTest (false));
  }
} g_waypointMobilityModelTestSuite;


} // namespace ns3
