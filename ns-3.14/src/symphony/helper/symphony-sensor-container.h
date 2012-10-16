/*
 * symphony-sensor-container.h
 *
 *  Created on: Oct 10, 2012
 *      Author: lauril
 */

#ifndef SYMPHONY_SENSOR_CONTAINER_H_
#define SYMPHONY_SENSOR_CONTAINER_H_
#include "ns3/names.h"
#include "ns3/raw-sensor.h"
#include "ns3/tos-node-container.h"
#include "ns3/string.h"

namespace ns3
{

  class SymphonySensorContainer
  {
  public:
  typedef std::vector<Ptr<RawSensor> >::const_iterator Iterator;

  /**
   * Create an empty SymphonySensorContainer.
   */
  SymphonySensorContainer ();

  /**
   * \param dev a sensor to add to the container
   *
   * Create a SymphonySensorContainer with exactly one net sensor that has previously
   * been instantiated
   */
  SymphonySensorContainer (Ptr<RawSensor> dev);

  /**
   * Create a SymphonySensorContainer with exactly one sensor which has been
   * previously instantiated and assigned a name using the Object name
   * service.  This RawSensor is specified by its assigned name.
   *
   * \param devName The name of the sensor to add to the container
   *
   * Create a SymphonySensorContainer with exactly one sensor
   */
  SymphonySensorContainer (std::string devName);

  /**
   * \param a a sensor container
   * \param b another sensor container
   *
   * Create a sensor container which is a concatenation of the two input
   * NetDeviceContainers.
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<RawSensor>.  When used, two
   * Ptr<RawSensor> will be passed to this constructor instead of SymphonySensorContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * SymphonySensorContainer (Ptr<RawSensor> dev) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<RawSensor> to these
   * constructors.
   */
  SymphonySensorContainer (const SymphonySensorContainer &a, const SymphonySensorContainer &b);

  /**
   * \brief Get an iterator which refers to the first RawSensor in the
   * container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the NetDevices
   *
   * \code
   *   SymphonySensorContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some RawSensor method
   *     }
   * \endcode
   *
   * \returns an iterator which refers to the first RawSensor in the container.
   */
  Iterator Begin (void) const;

  /**
   * \brief Get an iterator which indicates past-the-last RawSensor in the
   * container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the NetDevices
   *
   * \code
   *   SymphonySensorContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some RawSensor method
   *     }
   * \endcode
   *
   * \returns an iterator which indicates an ending condition for a loop.
   */
  Iterator End (void) const;

  /**
   * \brief Get the number of Ptr<RawSensor> stored in this container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is typically used to
   * define an ending condition in a for-loop that runs through the stored
   * NetDevices
   *
   * \code
   *   uint32_t nSensors = container.GetN ();
   *   for (uint32_t i = 0 i < nSensors; ++i)
   *     {
   *       Ptr<RawSensor> p = container.Get (i)
   *       i->method ();  // some RawSensor method
   *     }
   * \endcode
   *
   * \returns the number of Ptr<RawSensor> stored in this container.
   */
  uint32_t GetN (void) const;

  /**
   * \brief Get the Ptr<RawSensor> stored in this container at a given
   * index.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is used to retrieve the
   * indexed Ptr<RawSensor>.
   *
   * \code
   *   uint32_t nSensors = container.GetN ();
   *   for (uint32_t i = 0 i < nSensors; ++i)
   *     {
   *       Ptr<RawSensor> p = container.Get (i)
   *       i->method ();  // some RawSensor method
   *     }
   * \endcode
   *
   * \param i the index of the requested sensor pointer.
   * \returns the requested sensor pointer.
   */
  Ptr<RawSensor> Get (uint32_t i) const;

  /**
   * \brief Append the contents of another SymphonySensorContainer to the end of
   * this container.
   *
   * \param other The SymphonySensorContainer to append.
   */
  void Add (SymphonySensorContainer other);

  /**
   * \brief Append a single Ptr<RawSensor> to this container.
   *
   * \param sensor The Ptr<RawSensor> to append.
   */
  void Add (Ptr<RawSensor> sensor);

  /**
   * \brief Append to this container the single Ptr<RawSensor> referred to
   * via its object name service registered name.
   *
   * \param deviceName The name of the RawSensor Object to add to the container.
   */
  void Add (std::string deviceName);



private:
  std::vector<Ptr<RawSensor> > m_sensors;
  };

} /* namespace ns3 */
#endif /* SYMPHONY_SENSOR_CONTAINER_H_ */
